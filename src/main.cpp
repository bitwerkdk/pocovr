// Demo based on:
// UTFT_Demo_320x240 by Henning Karlsen
// web: http://www.henningkarlsen.com/electronics
//
/*

 This sketch uses the GLCD and font 2 only.
 
 Make sure all the display driver and pin comnenctions are correct by
 editting the User_Setup.h file in the TFT_eSPI library folder.

 #########################################################################
 ###### DON'T FORGET TO UPDATE THE User_Setup.h FILE IN THE LIBRARY ######
 #########################################################################
 */
#include <Arduino.h>
#include "SPI.h"

#include "TFT_eSPI.h"

#define TFT_GREY 0x7BEF

TFT_eSPI tft = TFT_eSPI();       // Invoke custom library

unsigned long runTime = 0;
void setup()
{
  pinMode(15, OUTPUT);
  pinMode(5, OUTPUT);
  digitalWrite(15, LOW);
  digitalWrite(5, LOW);

  randomSeed(analogRead(A0));
// Setup the LCD
  tft.init();
  tft.setRotation(3);

  tft.fillScreen(0xFFFF);

  digitalWrite(15, HIGH);
  digitalWrite(5, HIGH);

  runTime = millis();
  //digitalWrite(15, HIGH);
  //digitalWrite(5, LOW);
}

unsigned long loops;

void loop()
{
  randomSeed(millis());
  //digitalWrite(15, HIGH);
  //digitalWrite(5, LOW);
  
  loops++;
  
  digitalWrite(15, LOW);
  digitalWrite(5, HIGH);

  //tft.fillScreen(random(65535));
  tft.fillScreen(loops);
  //tft.fillTriangle(0, 0, 320, 0, 0, 240, random(65535));

  tft.setTextColor(TFT_BLUE+TFT_GREEN,0xF800);
  tft.drawCentreString("FPS: ", 160, 210,2);
  tft.setTextDatum(TC_DATUM);
  tft.drawNumber(loops * 1000 / (millis() - runTime), 160, 225,2);
  
  digitalWrite(15, HIGH);
  digitalWrite(5, LOW);

  //tft.fillScreen(random(65535));
  tft.fillScreen(loops);
  //tft.fillTriangle(0, 0, 320, 0, 0, 240, random(65535));

  tft.setTextColor(TFT_BLUE+TFT_GREEN,0xF800);
  tft.drawCentreString("FPS: ", 160, 210,2);
  tft.setTextDatum(TC_DATUM);
  tft.drawNumber(loops * 1000 / (millis() - runTime), 160, 225,2);
  
  //randomSeed(1234); // This ensure test is repeatable with exact same draws each loop
  /*int buf[318];
  int x, x2;
  int y, y2;
  int r;
  runTime = millis();
// Clear the screen and draw the frame
  tft.fillScreen(TFT_BLACK);


  tft.fillRect(0, 0, 319, 14,TFT_RED);

  tft.fillRect(0, 226, 319, 14,TFT_GREY);

  tft.setTextColor(TFT_BLACK,TFT_RED);
  tft.drawCentreString("* TFT_eSPI *", 160, 4, 1);
  tft.setTextColor(TFT_YELLOW,TFT_GREY);
  tft.drawCentreString("Adapted by Bodmer", 160, 228,1);

  tft.drawRect(0, 14, 319, 211, TFT_BLUE);

// Draw crosshairs
  tft.drawLine(159, 15, 159, 224,TFT_BLUE);
  tft.drawLine(1, 119, 318, 119,TFT_BLUE);
  for (int i=9; i<310; i+=10)
    tft.drawLine(i, 117, i, 121,TFT_BLUE);
  for (int i=19; i<220; i+=10)
    tft.drawLine(157, i, 161, i,TFT_BLUE);

// Draw sin-, cos- and tan-lines  
  tft.setTextColor(TFT_CYAN);
  tft.drawString("Sin", 5, 15,2);
  for (int i=1; i<318; i++)
  {
    tft.drawPixel(i,119+(sin(((i*1.13)*3.14)/180)*95),TFT_CYAN);
  }
  tft.setTextColor(TFT_RED);
  tft.drawString("Cos", 5, 30,2);
  for (int i=1; i<318; i++)
  {
    tft.drawPixel(i,119+(cos(((i*1.13)*3.14)/180)*95),TFT_RED);
  }
  tft.setTextColor(TFT_YELLOW);
  tft.drawString("Tan", 5, 45,2);
  for (int i=1; i<318; i++)
  {
    tft.drawPixel(i,119+(tan(((i*1.13)*3.14)/180)),TFT_YELLOW);
  }

  delay(0);

  tft.fillRect(1,15,317,209,TFT_BLACK);

  tft.drawLine(159, 15, 159, 224,TFT_BLUE);
  tft.drawLine(1, 119, 318, 119,TFT_BLUE);
int col = 0;
// Draw a moving sinewave
  x=1;
  for (int i=1; i<(317*20); i++) 
  {
    x++;
    if (x==318)
      x=1;
    if (i>318)
    {
      if ((x==159)||(buf[x-1]==119))
        col = TFT_BLUE;
      else
      tft.drawPixel(x,buf[x-1],TFT_BLACK);
    }
    y=119+(sin(((i*1.1)*3.14)/180)*(90-(i / 100)));
    tft.drawPixel(x,y,TFT_BLUE);
    buf[x-1]=y;
  }

  delay(0);

  tft.fillRect(1,15,317,209,TFT_BLACK);

// Draw some filled rectangles
  for (int i=1; i<6; i++)
  {
    switch (i)
    {
      case 1:
        col = TFT_MAGENTA;
        break;
      case 2:
        col = TFT_RED;
        break;
      case 3:
        col = TFT_GREEN;
        break;
      case 4:
        col = TFT_BLUE;
        break;
      case 5:
        col = TFT_YELLOW;
        break;
    }
    tft.fillRect(70+(i*20), 30+(i*20), 60, 60,col);
  }

  delay(0);

  tft.fillRect(1,15,317,209,TFT_BLACK);

// Draw some filled, rounded rectangles
  for (int i=1; i<6; i++)
  {
    switch (i)
    {
      case 1:
        col = TFT_MAGENTA;
        break;
      case 2:
        col = TFT_RED;
        break;
      case 3:
        col = TFT_GREEN;
        break;
      case 4:
        col = TFT_BLUE;
        break;
      case 5:
        col = TFT_YELLOW;
        break;
    }
    tft.fillRoundRect(190-(i*20), 30+(i*20), 60,60, 3,col);
  }
  
  delay(0);

  tft.fillRect(1,15,317,209,TFT_BLACK);

// Draw some filled circles
  for (int i=1; i<6; i++)
  {
    switch (i)
    {
      case 1:
        col = TFT_MAGENTA;
        break;
      case 2:
        col = TFT_RED;
        break;
      case 3:
        col = TFT_GREEN;
        break;
      case 4:
        col = TFT_BLUE;
        break;
      case 5:
        col = TFT_YELLOW;
        break;
    }
    tft.fillCircle(100+(i*20),60+(i*20), 30,col);
  }
  
  delay(0);

  tft.fillRect(1,15,317,209,TFT_BLACK);

// Draw some lines in a pattern

  for (int i=15; i<224; i+=5)
  {
    tft.drawLine(1, i, (i*1.44)-10, 223,TFT_RED);
  }

  for (int i=223; i>15; i-=5)
  {
    tft.drawLine(317, i, (i*1.44)-11, 15,TFT_RED);
  }

  for (int i=223; i>15; i-=5)
  {
    tft.drawLine(1, i, 331-(i*1.44), 15,TFT_CYAN);
  }

  for (int i=15; i<224; i+=5)
  {
    tft.drawLine(317, i, 330-(i*1.44), 223,TFT_CYAN);
  }
  
  delay(0);


  tft.fillRect(1,15,317,209,TFT_BLACK);

// Draw some random circles
  for (int i=0; i<100; i++)
  {
    x=32+random(256);
    y=45+random(146);
    r=random(30);
    tft.drawCircle(x, y, r,random(0xFFFF));
  }

  delay(0);

  tft.fillRect(1,15,317,209,TFT_BLACK);

// Draw some random rectangles
  for (int i=0; i<100; i++)
  {
    x=2+random(316);
    y=16+random(207);
    x2=2+random(316);
    y2=16+random(207);
    if (x2<x) {
      r=x;x=x2;x2=r;
    }
    if (y2<y) {
      r=y;y=y2;y2=r;
    }
    tft.drawRect(x, y, x2-x, y2-y,random(0xFFFF));
  }

  delay(0);


  tft.fillRect(1,15,317,209,TFT_BLACK);

// Draw some random rounded rectangles
  for (int i=0; i<100; i++)
  {
    x=2+random(316);
    y=16+random(207);
    x2=2+random(316);
    y2=16+random(207);
    // We need to get the width and height and do some window checking
    if (x2<x) {
      r=x;x=x2;x2=r;
    }
    if (y2<y) {
      r=y;y=y2;y2=r;
    }
    // We need a minimum size of 6
    if((x2-x)<6) x2=x+6;
    if((y2-y)<6) y2=y+6;
    tft.drawRoundRect(x, y, x2-x,y2-y, 3,random(0xFFFF));
  }

  delay(0);

  tft.fillRect(1,15,317,209,TFT_BLACK);

 //randomSeed(1234);
 int colour = 0;
 for (int i=0; i<100; i++)
  {
    x=2+random(316);
    y=16+random(209);
    x2=2+random(316);
    y2=16+random(209);
    colour=random(0xFFFF);
    tft.drawLine(x, y, x2, y2,colour);
  }

  delay(0);

  tft.fillRect(1,15,317,209,TFT_BLACK);

  // This test has been modified as it takes more time to calculate the random numbers
  // than to draw the pixels (3 seconds to produce 30,000 randoms)!
  for (int i=0; i<10000; i++)
  {
    tft.drawPixel(2+random(316), 16+random(209),random(0xFFFF));
  }

  // Draw 10,000 pixels to fill a 100x100 pixel box
  // use the coords as the colour to produce the banding
  //byte i = 100;
  //while (i--) {
  //  byte j = 100;
  //  while (j--) myGLCD.drawPixel(i+110,j+70,i+j);
  //  //while (j--) myGLCD.drawPixel(i+110,j+70,0xFFFF);
  //}
  delay(0);

  tft.fillScreen(TFT_BLUE);
  tft.fillRoundRect(80, 70, 239-80,169-70, 3,TFT_RED);
  
  tft.setTextColor(TFT_WHITE,TFT_RED);
  tft.drawCentreString("That's it!", 160, 93,2);
  tft.drawCentreString("Restarting in a", 160, 119,2);
  tft.drawCentreString("few seconds...", 160, 132,2);

  runTime = millis()-runTime;
  tft.setTextColor(TFT_GREEN,TFT_BLUE);
  tft.drawCentreString("Runtime: (msecs)", 160, 210,2);
  tft.setTextDatum(TC_DATUM);
  tft.drawNumber(runTime, 160, 225,2);
  delay (5000);*/
}

