// See 
// • https://code.austinmorlan.com/austin/embedded-game-programming
// • https://austinmorlan.com/posts/embedded_game_programming_3/

#pragma once

#include <stdint.h>


#define LCD_WIDTH (320)
#define LCD_HEIGHT (240)
#define LCD_DEPTH (2)


void Odroid_InitializeDisplay(void);
void Odroid_DrawFrame(uint16_t* buffer);
