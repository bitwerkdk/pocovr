#include "gfx.h"

#include <Arduino.h>
#include <SPI.h>
#include <TFT_eSPI.h>
#include "../math/math.h"
#include "../objects/mesh.h"
#include "../state/state.h"
#include "../vector/Vector.h"

#define MAX_MESHES 5
#define MAX_TRIS 1000

namespace gfx {
    TFT_eSPI tft = TFT_eSPI();

    const unsigned int TFT_CS1 = 15;
    const unsigned int TFT_CS2 = 5;

    unsigned long startTime;
    unsigned long counter;
    
    Vector<objects::mesh*> meshes;
    Vector<objects::tri> tris;

    void calculateTriangles(const Vector<objects::mesh*>& meshes, Vector<objects::tri>& outTris) {
        outTris.clear();
        math::mat4x4 viewMat = math::mat4x4::inverseTransformation(math::vector3F(FX_FROM_F(0), FX_FROM_F(0), FX_FROM_F(0)), math::vector3F(FX_FROM_F(0), FX_FROM_F(0), FX_FROM_F(1)), math::vector3F(FX_FROM_F(0), FX_FROM_F(1), FX_FROM_F(0)));
        math::mat4x4 projMat = math::mat4x4::projection(FX_FROM_F(90), FX_FROM_F(1), FX_FROM_F(10), FX_FROM_I(TFT_WIDTH), FX_FROM_I(TFT_HEIGHT));
        for (const objects::mesh* mesh : meshes)
        {
            math::mat4x4 transformMat = math::mat4x4::transformation(mesh->pos, mesh->forward, mesh->up);
            for (objects::tri tri : mesh->tris)
            {
                math::vector4F p0 = math::vector4F(tri.p[0].x, tri.p[0].y, tri.p[0].z, FX_FROM_I(1));
                math::vector4F p1 = math::vector4F(tri.p[1].x, tri.p[1].y, tri.p[1].z, FX_FROM_I(1));
                math::vector4F p2 = math::vector4F(tri.p[2].x, tri.p[2].y, tri.p[2].z, FX_FROM_I(1));

                p0 = transformMat * p0;
                p1 = transformMat * p1;
                p2 = transformMat * p2;

                p0 = viewMat * p0;
                p1 = viewMat * p1;
                p2 = viewMat * p2;

                p0 = projMat * p0;
                p0 /= p0.w != 0 ? p0.w : 1;
                p1 = projMat * p1;
                p1 /= p1.w != 0 ? p1.w : 1;
                p2 = projMat * p2;
                p2 /= p2.w != 0 ? p2.w : 1;

                outTris.push_back(objects::tri(math::vector3F(p0.x, p0.y, p0.z), math::vector3F(p1.x, p1.y, p1.z), math::vector3F(p2.x, p2.y, p2.z)));
            }
        }
    }

    void drawTriangles(const Vector<objects::tri>& triangles) {
        for (const objects::tri& t : triangles)
        {
            tft.drawTriangle(FX_TO_F(t.p[0].x) * TFT_WIDTH + (TFT_WIDTH >> 1), FX_TO_F(t.p[0].y) * -TFT_HEIGHT + (TFT_HEIGHT >> 1), FX_TO_F(t.p[1].x) * TFT_WIDTH + (TFT_WIDTH >> 1), FX_TO_F(t.p[1].y) * -TFT_HEIGHT + (TFT_HEIGHT >> 1), FX_TO_F(t.p[2].x) * TFT_WIDTH + (TFT_WIDTH >> 1), FX_TO_F(t.p[2].y) * -TFT_HEIGHT + (TFT_HEIGHT >> 1), TFT_WHITE);
        }
    }

    void drawFps() {
        tft.setTextColor(TFT_WHITE,TFT_BLACK);
        tft.setTextDatum(TC_DATUM);
        tft.drawNumber(counter * 1000 / (millis() - startTime), 120, 305, 2);
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

        startTime = millis();

        // Set meshes
        objects::mesh** meshStorageArray;
        meshStorageArray = (objects::mesh**)malloc(sizeof(objects::mesh*) * MAX_MESHES);
        meshes.setStorage(meshStorageArray, MAX_MESHES, 0);

        objects::mesh* pyramid = new objects::mesh();
        objects::tri* pyramidTriStorageArray;
        pyramidTriStorageArray = (objects::tri*)malloc(sizeof(objects::tri) * 10);
        pyramid->tris.setStorage(pyramidTriStorageArray, 10, 0);
        pyramid->tris.push_back(objects::tri(math::vector3F(FX_FROM_F(-1), FX_FROM_F(-1), FX_FROM_F(-1)), math::vector3F(FX_FROM_F(1), FX_FROM_F(-1), FX_FROM_F(1)), math::vector3F(FX_FROM_F(-1), FX_FROM_F(-1), FX_FROM_F(1))));
        pyramid->tris.push_back(objects::tri(math::vector3F(FX_FROM_F(-1), FX_FROM_F(-1), FX_FROM_F(-1)), math::vector3F(FX_FROM_F(1), FX_FROM_F(-1), FX_FROM_F(-1)), math::vector3F(FX_FROM_F(1), FX_FROM_F(-1), FX_FROM_F(1))));
        pyramid->tris.push_back(objects::tri(math::vector3F(FX_FROM_F(1), FX_FROM_F(-1), FX_FROM_F(1)), math::vector3F(FX_FROM_F(0), FX_FROM_F(1), FX_FROM_F(0)), math::vector3F(FX_FROM_F(-1), FX_FROM_F(-1), FX_FROM_F(1))));
        pyramid->tris.push_back(objects::tri(math::vector3F(FX_FROM_F(1), FX_FROM_F(-1), FX_FROM_F(-1)), math::vector3F(FX_FROM_F(0), FX_FROM_F(1), FX_FROM_F(0)), math::vector3F(FX_FROM_F(1), FX_FROM_F(-1), FX_FROM_F(1))));
        pyramid->tris.push_back(objects::tri(math::vector3F(FX_FROM_F(-1), FX_FROM_F(-1), FX_FROM_F(-1)), math::vector3F(FX_FROM_F(0), FX_FROM_F(1), FX_FROM_F(0)), math::vector3F(FX_FROM_F(1), FX_FROM_F(-1), FX_FROM_F(-1))));
        pyramid->tris.push_back(objects::tri(math::vector3F(FX_FROM_F(-1), FX_FROM_F(-1), FX_FROM_F(1)), math::vector3F(FX_FROM_F(0), FX_FROM_F(1), FX_FROM_F(0)), math::vector3F(FX_FROM_F(-1), FX_FROM_F(-1), FX_FROM_F(-1))));
        //pyramid->tris.push_back(objects::tri(math::vector3F(FX_FROM_F(-1), FX_FROM_F(-1), FX_FROM_F(-1)), math::vector3F(FX_FROM_F(-1), FX_FROM_F(-1), FX_FROM_F(1)), math::vector3F(FX_FROM_F(1), FX_FROM_F(-1), FX_FROM_F(1))));
        //pyramid->tris.push_back(objects::tri(math::vector3F(FX_FROM_F(-1), FX_FROM_F(-1), FX_FROM_F(-1)), math::vector3F(FX_FROM_F(1), FX_FROM_F(-1), FX_FROM_F(1)), math::vector3F(FX_FROM_F(1), FX_FROM_F(-1), FX_FROM_F(-1))));
        void* pyramidPointer = pyramid;
        meshes.push_back((objects::mesh*)pyramidPointer);
        
        // Set tris
        objects::tri* triStorageArray;
        triStorageArray = (objects::tri*)malloc(sizeof(objects::tri) * MAX_TRIS);
        tris.setStorage(triStorageArray, MAX_TRIS, 0);
        
        /*tris.push_back({ math::vector3F(FX_FROM_F(0), FX_FROM_F(0), FX_FROM_F(0)), math::vector3F(FX_FROM_F(0), FX_FROM_F(0.5), FX_FROM_F(0)), math::vector3F(FX_FROM_F(0.1), FX_FROM_F(0), FX_FROM_F(0)) });
        tris.push_back({ math::vector3F(FX_FROM_F(0.1), FX_FROM_F(0.1), FX_FROM_F(0)), math::vector3F(FX_FROM_F(0.5), FX_FROM_F(0.5), FX_FROM_F(0)), math::vector3F(FX_FROM_F(0.4), FX_FROM_F(0.2), FX_FROM_F(0)) });
        tris.push_back({ math::vector3F(FX_FROM_F(1), FX_FROM_F(0.9), FX_FROM_F(0)), math::vector3F(FX_FROM_F(0.7), FX_FROM_F(1), FX_FROM_F(0)), math::vector3F(FX_FROM_F(0.6), FX_FROM_F(0.6), FX_FROM_F(0)) });
        tris.push_back({ math::vector3F(FX_FROM_F(0), FX_FROM_F(1), FX_FROM_F(0)), math::vector3F(FX_FROM_F(0), FX_FROM_F(0.9), FX_FROM_F(0)), math::vector3F(FX_FROM_F(0.1), FX_FROM_F(1), FX_FROM_F(0)) });*/
    }

    void loop() {
        randomSeed(millis());
        counter++;

        calculateTriangles(meshes, tris);

        // Clear both displays
        digitalWrite(TFT_CS1, LOW);
        digitalWrite(TFT_CS2, LOW);
        tft.fillScreen(TFT_BLACK);

        // Write to display 1
        setActiveScreen(TFT_CS1, TFT_CS2);
        drawTriangles(tris);
        drawFps();
        
        // Write to display 2
        setActiveScreen(TFT_CS2, TFT_CS1);
        drawTriangles(tris);
        drawFps();
    }
}