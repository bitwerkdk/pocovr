#include "gfx.h"

#include <Arduino.h>
#include <SPI.h>
#include <TFT_eSPI.h>
#include "../math/math.h"
#include "../objects/camera.h"
#include "../objects/mesh.h"
#include "../objects/transform.h"
#include "../state/state.h"
#include "../utils/utils.h"
#include "../vector/vector.h"

#define MAX_MESHES 5
#define MAX_TRIS 1000
#define MAX_LIGHTS 5

namespace gfx {
    TFT_eSPI tft = TFT_eSPI();

    const unsigned int TFT_CS1 = 15;
    const unsigned int TFT_CS2 = 5;

    unsigned long startTime;
    unsigned long counter;
    
    TFT_eSprite halfFrameBuffer(&tft);

    vector<objects::mesh*> meshes;
    vector<objects::screenTri> tris;

    objects::camera leftCamera(math::vector3F(FX_FROM_F(-0.0315), 0, 0));
    objects::camera rightCamera(math::vector3F(FX_FROM_F(0.0315), 0, 0));

    struct light
    {
        math::vector3F dir = math::vector3F(0, FX_FROM_F(-1), 0);
        math::fixed intensity = 1;

        light() { }
        light(const math::vector3F& dir, const math::fixed& intensity) : dir(dir.normalized()), intensity(intensity) { }
    };
    
    vector<light> lights;

    void calculateTriangles(const vector<objects::mesh*>& meshes, vector<objects::screenTri>& outTris, const vector<light>& lights, const objects::camera camera) {
        // Clear triangle vector
        outTris.clear();

        // Make view matrix from camera transform
        math::mat4x4 viewMat = math::mat4x4::inverseTransformation(camera.objTransform.pos, camera.objTransform.getForward(), camera.objTransform.getUp());
        for (const objects::mesh* mesh : meshes)
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
                for (light l : lights)
                {
                    brightness = math::fxLerp(brightness, FX_FROM_I(1), FX_MUL(FX_SUB(math::vector3F::dot(l.dir, normal), FX_FROM_I(1)) >> 1, l.intensity));
                }

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

                // Add projected triangle to triangle vector
                outTris.push_back(objects::screenTri(math::vector2F(p0.x, p0.y), math::vector2F(p1.x, p1.y), math::vector2F(p2.x, p2.y), brightness));
            }
        }
    }

    void drawTriangles(const vector<objects::screenTri>& triangles) {
        halfFrameBuffer.fillSprite(0x0000);
        for (const objects::screenTri& t : triangles)
        {
            unsigned short color = RGB565((unsigned short)(31 * FX_TO_F(t.brightness)), (unsigned short)(63 * FX_TO_F(t.brightness)), (unsigned short)(31 * FX_TO_F(t.brightness)));
            halfFrameBuffer.fillTriangle(FX_TO_F(t.p[0].x) * TFT_WIDTH + (TFT_WIDTH >> 1), FX_TO_F(t.p[0].y) * -TFT_HEIGHT + (TFT_HEIGHT >> 1), FX_TO_F(t.p[1].x) * TFT_WIDTH + (TFT_WIDTH >> 1), FX_TO_F(t.p[1].y) * -TFT_HEIGHT + (TFT_HEIGHT >> 1), FX_TO_F(t.p[2].x) * TFT_WIDTH + (TFT_WIDTH >> 1), FX_TO_F(t.p[2].y) * -TFT_HEIGHT + (TFT_HEIGHT >> 1), color);
        }
        halfFrameBuffer.pushSprite(0, 0);
        halfFrameBuffer.fillSprite(0x0000);
        for (const objects::screenTri& t : triangles)
        {
            unsigned short color = RGB565((unsigned short)(31 * FX_TO_F(t.brightness)), (unsigned short)(63 * FX_TO_F(t.brightness)), (unsigned short)(31 * FX_TO_F(t.brightness)));
            halfFrameBuffer.fillTriangle(FX_TO_F(t.p[0].x) * TFT_WIDTH + (TFT_WIDTH >> 1), FX_TO_F(t.p[0].y) * -TFT_HEIGHT, FX_TO_F(t.p[1].x) * TFT_WIDTH + (TFT_WIDTH >> 1), FX_TO_F(t.p[1].y) * -TFT_HEIGHT, FX_TO_F(t.p[2].x) * TFT_WIDTH + (TFT_WIDTH >> 1), FX_TO_F(t.p[2].y) * -TFT_HEIGHT, color);
        }
        halfFrameBuffer.pushSprite(0, TFT_HEIGHT >> 1);
    }

    void drawAvgFps() {
        tft.setTextColor(TFT_WHITE,TFT_BLACK);
        tft.setTextDatum(TC_DATUM);
        tft.drawNumber(counter * 1000 / (millis() - startTime), 120, 305, 2);
    }

    void drawAvgMillis() {
        tft.setTextColor(TFT_WHITE,TFT_BLACK);
        tft.setTextDatum(TC_DATUM);
        tft.drawNumber((millis() - startTime) / counter, 120, 305, 2);
    }

    void setActiveScreen(const unsigned int& enabledScreen, const unsigned int&  disabledScreen) {
        digitalWrite(enabledScreen, LOW);
        digitalWrite(disabledScreen, HIGH);
    }

    void setup() {
        pinMode(TFT_CS1, OUTPUT);
        pinMode(TFT_CS2, OUTPUT);
        digitalWrite(TFT_CS1, LOW);
        digitalWrite(TFT_CS2, LOW);

        Serial.begin(115200);

        // Setup the LCD
        tft.init();
        tft.setRotation(2);
        tft.fillScreen(0xFFFF);

        // Disable screens
        digitalWrite(TFT_CS1, HIGH);
        digitalWrite(TFT_CS2, HIGH);

        //Initialize frame buffer
        halfFrameBuffer.createSprite(TFT_WIDTH, TFT_HEIGHT >> 1);

        startTime = millis();

        // Set meshes
        meshes = utils::makeVector<objects::mesh*>(MAX_MESHES);

        // Make pyramid
        objects::mesh* pyramid = new objects::mesh(math::vector3F(0, 0, FX_FROM_F(3)));
        pyramid->tris.push_back(objects::tri(math::vector3F(FX_FROM_F(-1), FX_FROM_F(-1), FX_FROM_F(-1)), math::vector3F(FX_FROM_F(1), FX_FROM_F(-1), FX_FROM_F(1)), math::vector3F(FX_FROM_F(-1), FX_FROM_F(-1), FX_FROM_F(1))));
        pyramid->tris.push_back(objects::tri(math::vector3F(FX_FROM_F(-1), FX_FROM_F(-1), FX_FROM_F(-1)), math::vector3F(FX_FROM_F(1), FX_FROM_F(-1), FX_FROM_F(-1)), math::vector3F(FX_FROM_F(1), FX_FROM_F(-1), FX_FROM_F(1))));
        pyramid->tris.push_back(objects::tri(math::vector3F(FX_FROM_F(1), FX_FROM_F(-1), FX_FROM_F(1)), math::vector3F(FX_FROM_F(0), FX_FROM_F(1), FX_FROM_F(0)), math::vector3F(FX_FROM_F(-1), FX_FROM_F(-1), FX_FROM_F(1))));
        pyramid->tris.push_back(objects::tri(math::vector3F(FX_FROM_F(1), FX_FROM_F(-1), FX_FROM_F(-1)), math::vector3F(FX_FROM_F(0), FX_FROM_F(1), FX_FROM_F(0)), math::vector3F(FX_FROM_F(1), FX_FROM_F(-1), FX_FROM_F(1))));
        pyramid->tris.push_back(objects::tri(math::vector3F(FX_FROM_F(-1), FX_FROM_F(-1), FX_FROM_F(-1)), math::vector3F(FX_FROM_F(0), FX_FROM_F(1), FX_FROM_F(0)), math::vector3F(FX_FROM_F(1), FX_FROM_F(-1), FX_FROM_F(-1))));
        pyramid->tris.push_back(objects::tri(math::vector3F(FX_FROM_F(-1), FX_FROM_F(-1), FX_FROM_F(1)), math::vector3F(FX_FROM_F(0), FX_FROM_F(1), FX_FROM_F(0)), math::vector3F(FX_FROM_F(-1), FX_FROM_F(-1), FX_FROM_F(-1))));
        meshes.push_back(pyramid);
        
        // Set tris
        tris = utils::makeVector<objects::screenTri>(MAX_TRIS);

        // Set lights
        lights = utils::makeVector<light>(MAX_LIGHTS);
        lights.push_back(light(math::vector3F(FX_FROM_F(2), FX_FROM_F(1), FX_FROM_F(-1)), FX_FROM_F(1)));
        lights.push_back(light(math::vector3F(FX_FROM_F(-2), FX_FROM_F(1), FX_FROM_F(-1)), FX_FROM_F(0.5)));

        Serial.println((int)halfFrameBuffer.getPointer() - (int)&halfFrameBuffer);
    }

    void loop() {
        meshes[0]->objTransform.rotateY(FX_FROM_F(4));
        
        randomSeed(millis());
        counter++;

        // Clear both displays
        /*digitalWrite(TFT_CS1, LOW);
        digitalWrite(TFT_CS2, LOW);
        //if(millis() < 1000) {
            tft.fillScreen(TFT_BLACK);
        //}*/

        //halfFrameBuffer.fillSprite(0x0000);

        //memset(pixelsDrawn, 0x00, sizeof(pixelsDrawn));

        // Write to display 1
        setActiveScreen(TFT_CS1, TFT_CS2);
        calculateTriangles(meshes, tris, lights, rightCamera);
        drawTriangles(tris);
        drawAvgMillis();

        //memset(pixelsDrawn, 0x00, sizeof(pixelsDrawn));
        
        // Write to display 2
        setActiveScreen(TFT_CS2, TFT_CS1);
        calculateTriangles(meshes, tris, lights, leftCamera);
        drawTriangles(tris);
        drawAvgMillis();
    }
}