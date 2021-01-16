#include "gfx.h"

#include <Arduino.h>
#include <SPI.h>
#include <TFT_eSPI.h>
#include "../math/math.h"
#include "../objects/mesh.h"
#include "../state/state.h"
#include "../vector/Vector.h"

namespace gfx {
    TFT_eSPI tft = TFT_eSPI();

    const unsigned int TFT_CS1 = 15;
    const unsigned int TFT_CS2 = 5;

    unsigned long startTime;
    unsigned long counter;
    
    objects::tri storageArray[3000];
    Vector<objects::tri> tris;

    void drawTriangles(const Vector<objects::tri>& triangles) {
        for (const objects::tri& t : triangles)
        {
            tft.drawTriangle(FX_TO_F(t.p[0].x) * TFT_WIDTH, FX_TO_F(t.p[0].y) * TFT_HEIGHT, FX_TO_F(t.p[1].x) * TFT_WIDTH, FX_TO_F(t.p[1].y) * TFT_HEIGHT, FX_TO_F(t.p[2].x) * TFT_WIDTH, FX_TO_F(t.p[2].y) * TFT_HEIGHT, TFT_WHITE);
        }
    }

    void drawFps() {
        tft.setTextColor(TFT_WHITE,TFT_BLACK);
        //tft.drawCentreString("FPS: ", 160, 210, 2);
        tft.setTextDatum(TC_DATUM);
        //tft.drawNumber(counter * 1000 / (millis() - startTime), 160, 225, 2);
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

        // Setup the LCD
        tft.init();
        tft.setRotation(2);
        tft.fillScreen(0xFFFF);

        // Disable screens
        digitalWrite(TFT_CS1, HIGH);
        digitalWrite(TFT_CS2, HIGH);

        startTime = millis();
        
        tris.setStorage(storageArray);
        
        tris.push_back({ math::vector3F(FX_FROM_F(0), FX_FROM_F(0), FX_FROM_F(0)), math::vector3F(FX_FROM_F(0), FX_FROM_F(0.5), FX_FROM_F(0)), math::vector3F(FX_FROM_F(0.1), FX_FROM_F(0), FX_FROM_F(0)) });
        tris.push_back({ math::vector3F(FX_FROM_F(0.1), FX_FROM_F(0.1), FX_FROM_F(0)), math::vector3F(FX_FROM_F(0.5), FX_FROM_F(0.5), FX_FROM_F(0)), math::vector3F(FX_FROM_F(0.4), FX_FROM_F(0.2), FX_FROM_F(0)) });
        tris.push_back({ math::vector3F(FX_FROM_F(1), FX_FROM_F(0.9), FX_FROM_F(0)), math::vector3F(FX_FROM_F(0.7), FX_FROM_F(1), FX_FROM_F(0)), math::vector3F(FX_FROM_F(0.6), FX_FROM_F(0.6), FX_FROM_F(0)) });
        tris.push_back({ math::vector3F(FX_FROM_F(0), FX_FROM_F(1), FX_FROM_F(0)), math::vector3F(FX_FROM_F(0), FX_FROM_F(0.9), FX_FROM_F(0)), math::vector3F(FX_FROM_F(0.1), FX_FROM_F(1), FX_FROM_F(0)) });
    }

    void loop() {
        randomSeed(millis());
        counter++;

        // Write to display 1
        setActiveScreen(TFT_CS1, TFT_CS2);
        tft.fillScreen(TFT_BLACK);
        drawTriangles(tris);
        tft.drawTriangle(0, 0, 0, 0.5 * TFT_HEIGHT, 0.1 * TFT_WIDTH, 0, TFT_WHITE);
        
        // Write to display 2
        setActiveScreen(TFT_CS2, TFT_CS1);
        tft.fillScreen(TFT_BLACK);
        drawTriangles(tris);

        // Write to both displays
        digitalWrite(TFT_CS1, LOW);
        digitalWrite(TFT_CS2, LOW);
        drawFps();
    }
}