#include <Arduino.h>
#include <SPI.h>
#include <TFT_eSPI.h>

namespace gfx {
    TFT_eSPI tft = TFT_eSPI();

    const unsigned int TFT_CS1 = 15;
    const unsigned int TFT_CS2 = 5;

    unsigned long startTime;
    unsigned long counter;

    void draw(unsigned int enabledScreen, unsigned int disabledScreen) {
        digitalWrite(enabledScreen, LOW);
        digitalWrite(disabledScreen, HIGH);

        tft.fillScreen(counter);

        // Write FPS
        tft.setTextColor(TFT_BLUE+TFT_GREEN,0xF800);
        tft.drawCentreString("FPS: ", 160, 210, 2);
        tft.setTextDatum(TC_DATUM);
        tft.drawNumber(counter * 1000 / (millis() - startTime), 160, 225, 2);
    }

    void setup() {
        pinMode(TFT_CS1, OUTPUT);
        pinMode(TFT_CS2, OUTPUT);
        digitalWrite(TFT_CS1, LOW);
        digitalWrite(TFT_CS2, LOW);

        // Setup the LCD
        tft.init();
        tft.setRotation(3);
        tft.fillScreen(0xFFFF);

        // Disable screens
        digitalWrite(TFT_CS1, HIGH);
        digitalWrite(TFT_CS2, HIGH);

        startTime = millis();
    }

    void loop() {
        randomSeed(millis());
        counter++;
        
        // Write to display 1
        draw(TFT_CS1, TFT_CS2);
        
        // Write to display 2
        draw(TFT_CS2, TFT_CS1);
    }
}