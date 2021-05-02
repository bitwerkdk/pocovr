#include "gfx.h"

#include <Arduino.h>
#include <SPI.h>
#include <TFT_eSPI.h>
#include "../math/math.h"
#include "../objects/camera.h"
#include "../objects/mesh.h"
#include "../objects/scene.h"
#include "../objects/transform.h"
#include "../physics/time.h"
#include "../state/state.h"
#include "../utils/utils.h"
#include "../vector/vector.h"

#define TFT_CS1 15
#define TFT_CS2 5

#define MAX_TRIS 1000

namespace gfx {
    TFT_eSPI tft = TFT_eSPI();

    unsigned long startTime;
    unsigned long counter;
    
    unsigned int bufferDivisions = 1; // How many times the frame buffer is halved
    TFT_eSprite frameBuffer(&tft);

    vector<objects::screenTri> screenTris;

    math::fixed screenOffset = 0;

    objects::transform headsetTransform;
    math::fixed ipd = FX_FROM_F(0.063);
    objects::camera leftCamera;
    objects::camera rightCamera;

    int clipTriangle2D(const objects::tri& tri, const math::vector2F& point, const math::vector2F& normal, objects::tri& outTri1, objects::tri& outTri2) {
        math::vector2F insidePoints[3];
        math::vector2F outsidePoints[3];
        int numInsidePoints = 0;
        int numOutsidePoints = 0;
        
        // Calculate a second point on the clipping line
        math::vector2F lineDir = math::vector3F::cross(normal, math::vector3F(0, 0, FX_FROM_I(1)));
        math::vector2F secondPoint = point + lineDir;

        // Check if the vertices are inside or outside points
        for(math::vector3F vert : tri.p) {
            if(math::vector3F::dot(vert - point, normal) >= 0) {
                insidePoints[numInsidePoints] = vert;
                numInsidePoints++;
            }
            else {
                outsidePoints[numOutsidePoints] = vert;
                numOutsidePoints++;
            }
        }

        // Clip the triangle
        switch (numInsidePoints)
        {
        case 0: // Completely outside
            return 0;
            break;
        case 3: // Completely inside
            outTri1 = tri;
            return 1;
            break;
        case 1: // Make smaller triangle
            outTri1.p[0] = insidePoints[0];
            outTri1.p[1] = math::lineLineIntersection(point, secondPoint, insidePoints[0], outsidePoints[0]);
            outTri1.p[2] = math::lineLineIntersection(point, secondPoint, insidePoints[0], outsidePoints[1]);
            return 1;
            break;
        case 2: // Make quad
            outTri1.p[0] = insidePoints[0];
            outTri1.p[1] = insidePoints[1];
            outTri1.p[2] = math::lineLineIntersection(point, secondPoint, insidePoints[0], outsidePoints[0]);
            outTri2.p[0] = insidePoints[1];
            outTri2.p[1] = math::lineLineIntersection(point, secondPoint, insidePoints[1], outsidePoints[0]);
            outTri2.p[2] = outTri1.p[2];
            return 2;
            break;
        }

        // Should never reach this point
        return 0;
    }

    void calculateTriangles(const objects::scene& scene, vector<objects::screenTri>& outTris, const objects::camera camera) {
        // Clear triangle vector
        outTris.clear();

        // Make view matrix from camera transform
        math::mat4x4 viewMat = math::mat4x4::inverseTransformation(camera.objTransform.pos, camera.objTransform.getForward(), camera.objTransform.getUp());
        for (const objects::mesh* mesh : scene.meshes)
        {
            // Make transformation matrix from mesh transform
            math::mat4x4 transformMat = math::mat4x4::transformation(mesh->objTransform.pos, mesh->objTransform.getForward(), mesh->objTransform.getUp());
            for (objects::tri tri : mesh->tris)
            {
                // Convert each vertex to a vector4F
                math::vector4F p0 = math::vector4F(tri.p[0].x, tri.p[0].y, tri.p[0].z, FX_FROM_I(1));
                math::vector4F p1 = math::vector4F(tri.p[1].x, tri.p[1].y, tri.p[1].z, FX_FROM_I(1));
                math::vector4F p2 = math::vector4F(tri.p[2].x, tri.p[2].y, tri.p[2].z, FX_FROM_I(1));

                // Move vertices to their world position
                p0 = transformMat * p0;
                p1 = transformMat * p1;
                p2 = transformMat * p2;

                // Backface culling
                tri.p[0] = math::vector3F(p0.x, p0.y, p0.z);
                tri.p[1] = math::vector3F(p1.x, p1.y, p1.z);
                tri.p[2] = math::vector3F(p2.x, p2.y, p2.z);
                math::vector3F dirToCamera = (camera.objTransform.pos - tri.p[0]);
                math::vector3F normal = math::vector3F::cross(tri.p[1] - tri.p[0], tri.p[2] - tri.p[0]).normalized();
                if(math::vector3F::dot(dirToCamera, normal) < 0) {
                    continue;
                }

                // Lighting
                math::fixed brightness = 0;
                for (objects::light l : scene.lights)
                {
                    brightness = math::fxLerp(brightness, FX_FROM_I(1), FX_MUL(FX_ADD(math::vector3F::dot(l.dir, normal), FX_FROM_I(1)) >> 1, l.intensity));
                }
                unsigned short color = RGB565((unsigned short)(31 * FX_TO_F(brightness)), (unsigned short)(63 * FX_TO_F(brightness)), (unsigned short)(31 * FX_TO_F(brightness)));

                // Move vertices into view space
                p0 = viewMat * p0;
                p1 = viewMat * p1;
                p2 = viewMat * p2;

                // Project vertices
                p0 = camera.projMat * p0;
                p0 /= p0.w != 0 ? p0.w : 1;
                p1 = camera.projMat * p1;
                p1 /= p1.w != 0 ? p1.w : 1;
                p2 = camera.projMat * p2;
                p2 /= p2.w != 0 ? p2.w : 1;

                // Edge clipping
                math::vector2F edges[4] = { math::vector2F(0, FX_FROM_I(1)), math::vector2F(FX_FROM_I(1), 0), math::vector2F(0, FX_FROM_I(-1)), math::vector2F(FX_FROM_I(-1), 0) };
                // Make finalClippedTris
                objects::tri finalClippedTris[1 << 4];
                int numFinalClippedTris = 0;
                finalClippedTris[numFinalClippedTris++] = objects::tri(p0, p1, p2);
                // Make tempClippedTris
                objects::tri tempClippedTris[1 << 4];
                int numTempClippedTris = 0;
                for (math::vector2F edge : edges) {
                    for (int i = 0; i < numFinalClippedTris; i++) {
                        objects::tri outTri1, outTri2;
                        char numOutTris = clipTriangle2D(finalClippedTris[i], edge, math::vector2F(-edge.x, -edge.y), outTri1, outTri2);
                        switch (numOutTris) {
                        case 1:
                            tempClippedTris[numTempClippedTris++] = outTri1;
                            break;
                        case 2:
                            tempClippedTris[numTempClippedTris++] = outTri1;
                            tempClippedTris[numTempClippedTris++] = outTri2;
                            break;
                        }
                    }

                    // Set finalClippedTris to tempClippedTris
                    numFinalClippedTris = numTempClippedTris;
                    for(int i = 0; i < numTempClippedTris; i++) {
                        finalClippedTris[i] = tempClippedTris[i];
                    }
                    numTempClippedTris = 0;
                }

                // Add projected and clipped triangle to triangle vector
                for (int i = 0; i < numFinalClippedTris; i++) {
                    outTris.push_back(objects::screenTri(finalClippedTris[i].p[0], finalClippedTris[i].p[1], finalClippedTris[i].p[2], color));
                }
            }
        }
    }

    void setActiveScreen(const unsigned int& enabledScreen, const unsigned int&  disabledScreen) {
        digitalWrite(enabledScreen, LOW);
        digitalWrite(disabledScreen, HIGH);
    }

    void drawTriangles(const vector<objects::screenTri>& triangles, const bool& rightEye) {
        setActiveScreen(rightEye ? TFT_CS1 : TFT_CS2, rightEye ? TFT_CS2 : TFT_CS1);
        for (int i = 0; i < 1 << bufferDivisions; i++)
        {
            // Clear buffer
            frameBuffer.fillSprite(0x0000);

            // Calculate offsets
            math::fixed xOffset = rightEye ? screenOffset : -screenOffset;
            math::fixed yOffset = i * (TFT_HEIGHT >> bufferDivisions);

            // Draw triangles to buffer
            for (const objects::screenTri& t : triangles)
            {
                // Convert vertices to pixel space
                math::vector2I a = math::vector2I(FX_TO_F(t.p[0].x) * (TFT_WIDTH >> 1) + (TFT_WIDTH >> 1) + xOffset, // a.x
                                                FX_TO_F(t.p[0].y) * (-TFT_HEIGHT >> 1) + (TFT_HEIGHT >> 1) - yOffset); // a.y
                math::vector2I b = math::vector2I(FX_TO_F(t.p[1].x) * (TFT_WIDTH >> 1) + (TFT_WIDTH >> 1) + xOffset, // b.x
                                                FX_TO_F(t.p[1].y) * (-TFT_HEIGHT >> 1) + (TFT_HEIGHT >> 1) - yOffset); // b.y
                math::vector2I c = math::vector2I(FX_TO_F(t.p[2].x) * (TFT_WIDTH >> 1) + (TFT_WIDTH >> 1) + xOffset, // c.x
                                                FX_TO_F(t.p[2].y) * (-TFT_HEIGHT >> 1) + (TFT_HEIGHT >> 1) - yOffset); // c.y

                // Draw triangle
                frameBuffer.fillTriangle(a.x, a.y, b.x, b.y, c.x, c.y, t.color); // Solid
                //frameBuffer.drawTriangle(a.x, a.y, b.x, b.y, c.x, c.y, TFT_RED); // Wireframe
            }

            // Draw buffer to screen
            frameBuffer.pushSprite(0, yOffset);
        }
    }

    void drawFps() {
        tft.setTextColor(TFT_WHITE,TFT_BLACK);
        tft.setTextDatum(TC_DATUM);
        tft.drawNumber(1000 / FX_TO_F(physics::deltaTime), 120, 305, 2);
    }

    void drawMillis() {
        tft.setTextColor(TFT_WHITE,TFT_BLACK);
        tft.setTextDatum(TC_DATUM);
        tft.drawNumber(FX_TO_F(physics::deltaTime), 120, 305, 2);
    }

    void initialize() {
        // Pin setup
        pinMode(TFT_CS1, OUTPUT);
        pinMode(TFT_CS2, OUTPUT);
        digitalWrite(TFT_CS1, LOW);
        digitalWrite(TFT_CS2, LOW);

        // Setup the LCD
        tft.init();
        tft.setRotation(2);
        tft.fillScreen(0xFFFF);

        // Disable screens
        digitalWrite(TFT_CS1, HIGH);
        digitalWrite(TFT_CS2, HIGH);

        //Initialize frame buffer
        frameBuffer.createSprite(TFT_WIDTH, TFT_HEIGHT >> bufferDivisions);
        
        // Set tris
        screenTris = utils::makeVector<objects::screenTri>(MAX_TRIS);
    }

    void renderScene(const objects::scene& scene) {
        counter++;

        // Calculate camera transforms
        leftCamera.objTransform = objects::transform(math::vector3F(-ipd >> 1, 0, 0), headsetTransform.getForward(), headsetTransform.getUp());
        rightCamera.objTransform = objects::transform(math::vector3F(ipd >> 1, 0, 0), headsetTransform.getForward(), headsetTransform.getUp());
        math::mat4x4 headsetMatrix = math::mat4x4::transformation(headsetTransform.pos, headsetTransform.getForward(), headsetTransform.getUp());
        math::vector4F leftCamPosV4 = math::vector4F(leftCamera.objTransform.pos.x, leftCamera.objTransform.pos.y, leftCamera.objTransform.pos.z, FX_FROM_I(1));
        math::vector4F rightCamPosV4 = math::vector4F(rightCamera.objTransform.pos.x, rightCamera.objTransform.pos.y, rightCamera.objTransform.pos.z,  FX_FROM_I(1));
        leftCamPosV4 = headsetMatrix * leftCamPosV4;
        rightCamPosV4 = headsetMatrix * rightCamPosV4;
        leftCamera.objTransform.pos = math::vector3F(leftCamPosV4.x, leftCamPosV4.y, leftCamPosV4.z);
        rightCamera.objTransform.pos = math::vector3F(rightCamPosV4.x, rightCamPosV4.y, rightCamPosV4.z);

        // Write to display 1
        calculateTriangles(scene, screenTris, rightCamera);
        drawTriangles(screenTris, true);
        drawMillis();
        
        // Write to display 2
        calculateTriangles(scene, screenTris, leftCamera);
        drawTriangles(screenTris, false);
        drawMillis();
    }
}