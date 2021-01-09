// See 
// • https://code.austinmorlan.com/austin/embedded-game-programming
// • https://austinmorlan.com/posts/embedded_game_programming_3/

#pragma once


// Counts the number of elements in an array
#define ARRAY_COUNT(value) ( sizeof(value) / sizeof(value[0]) )

// Swaps the endianness of a 16-bit value
#define SWAP_ENDIAN_16(value) ( (((value) & 0xFFu) << 8u) | ((value) >> 8u)  )

// Constructs a 16-bit color value of the form RGB565 with proper ESP32 endianness
#define RGB565(red, green, blue) ( (((red) >> 3u) << 11u) | (((green) >> 2u) << 5u) | ((blue) >> 3u) )

// Converts bytes to bits
#define BYTES_TO_BITS(value) ( (value) * 8 )

// Extracts the upper byte of a 16-bit value
#define UPPER_BYTE_16(value) ( (value) >> 8u )

// Extracts the lower byte of a 16-bit value
#define LOWER_BYTE_16(value) ( (value) & 0xFFu )
