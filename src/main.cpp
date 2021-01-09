#include <Arduino.h>
#include "macros.h"
#include "display.h"

#define firstScreenCS 21
#define secondScreenCS 22

uint16_t* colorBuffer;

int x, y;

void setup() {
  Serial.begin(115200);
  
  pinMode(firstScreenCS, OUTPUT);
  pinMode(secondScreenCS, OUTPUT);

  // Initialize both displays
  digitalWrite(firstScreenCS, LOW);
  digitalWrite(secondScreenCS, LOW);

  colorBuffer = (uint16_t*)malloc(LCD_WIDTH * LCD_HEIGHT * LCD_DEPTH);
  Serial.println("Before initializing");
  Odroid_InitializeDisplay();
  Serial.println("After initializing");
}

void loop() {
  memset(colorBuffer, 0x00, LCD_WIDTH * LCD_HEIGHT * LCD_DEPTH);
  for (int row = y; row < y + 50; ++row)
	{
		for (int col = x; col < x + 50; ++col)
		{
			colorBuffer[LCD_WIDTH * row + col] = 0xF800;
		}
	}
  Odroid_DrawFrame(colorBuffer);
}