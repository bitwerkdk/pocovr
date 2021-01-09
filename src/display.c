// See 
// • https://code.austinmorlan.com/austin/embedded-game-programming
// • https://austinmorlan.com/posts/embedded_game_programming_3/

#include "display.h"
#include "macros.h"
#include <driver/gpio.h>
#include <driver/spi_master.h>
#include <esp_log.h>


static const char* LOG_TAG = "OdroidDisplay";

static const gpio_num_t LCD_PIN_MISO = GPIO_NUM_19;
static const gpio_num_t LCD_PIN_MOSI = GPIO_NUM_23;
static const gpio_num_t LCD_PIN_SCLK = GPIO_NUM_18;
static const gpio_num_t LCD_PIN_CS = GPIO_NUM_5;
static const gpio_num_t LCD_PIN_DC = GPIO_NUM_21;
static const gpio_num_t LCD_PIN_BACKLIGHT = GPIO_NUM_14;


typedef enum
{
	SOFTWARE_RESET = 0x01u,
	SLEEP_OUT = 0x11u,
	DISPLAY_ON = 0x29u,
	COLUMN_ADDRESS_SET = 0x2Au,
	PAGE_ADDRESS_SET = 0x2Bu,
	MEMORY_WRITE = 0x2Cu,
	MEMORY_ACCESS_CONTROL = 0x36u,
	PIXEL_FORMAT_SET = 0x3Au,
} CommandCode;


typedef struct
{
	CommandCode code;
	uint8_t parameters[15];
	uint8_t length;
} StartupCommand;


static spi_device_handle_t gSpiHandle;

static StartupCommand gStartupCommands[] =
{
	// Reset to defaults
	{
		SOFTWARE_RESET,
		{},
		0
	},

	// Landscape Mode
	// Top-Left Origin
	// BGR Panel
	{
		MEMORY_ACCESS_CONTROL,
		{0x20 | 0xC0 | 0x08},
		1
	},

	// 16 bits per pixel
	{
		PIXEL_FORMAT_SET,
		{0x55},
		1
	},

	// Exit sleep mode
	{
		SLEEP_OUT,
		{},
		0
	},

	// Turn on the display
	{
		DISPLAY_ON,
		{},
		0
	},
};


static
void SendCommandCode(CommandCode code)
{
	spi_transaction_t transaction = {};

	transaction.length = BYTES_TO_BITS(1);
	transaction.tx_data[0] = (uint8_t)code;
	transaction.flags = SPI_TRANS_USE_TXDATA;

	gpio_set_level(LCD_PIN_DC, 0);
	spi_device_transmit(gSpiHandle, &transaction);
}

static
void SendCommandParameters(uint8_t* data, int length)
{
	spi_transaction_t transaction = {};

	transaction.length = BYTES_TO_BITS(length);
	transaction.tx_buffer = data;
	transaction.flags = 0;

	gpio_set_level(LCD_PIN_DC, 1);
	spi_device_transmit(gSpiHandle, &transaction);
}


void Odroid_InitializeDisplay(void)
{
	// Initialize the SPI bus
	{
		spi_bus_config_t spiBusConfig = {};
		spiBusConfig.miso_io_num = LCD_PIN_MISO;
		spiBusConfig.mosi_io_num = LCD_PIN_MOSI;
		spiBusConfig.sclk_io_num = LCD_PIN_SCLK;
		spiBusConfig.quadwp_io_num = -1;
		spiBusConfig.quadhd_io_num = -1;
		spiBusConfig.max_transfer_sz = LCD_WIDTH * LCD_HEIGHT * LCD_DEPTH;

		ESP_ERROR_CHECK(spi_bus_initialize(VSPI_HOST, &spiBusConfig, 1));

		ESP_LOGI(LOG_TAG, "Initialized SPI Bus");
	}


	// Add the display device to the SPI bus
	{
		spi_device_interface_config_t spiDeviceConfig = {};
		spiDeviceConfig.clock_speed_hz = SPI_MASTER_FREQ_40M;
		spiDeviceConfig.spics_io_num = LCD_PIN_CS;
		spiDeviceConfig.queue_size = 1;
		spiDeviceConfig.flags = SPI_DEVICE_NO_DUMMY;

		ESP_ERROR_CHECK(spi_bus_add_device(VSPI_HOST, &spiDeviceConfig, &gSpiHandle));

		ESP_LOGI(LOG_TAG, "Added display to SPI bus");
	}


	// Set the DC and backlight pins as outputs
	{
		gpio_set_direction(LCD_PIN_DC, GPIO_MODE_OUTPUT);
		gpio_set_direction(LCD_PIN_BACKLIGHT, GPIO_MODE_OUTPUT);
	}


	// Send the initialization commands to the display
	{
		int commandCount = ARRAY_COUNT(gStartupCommands);

		for (int commandIndex = 0; commandIndex < commandCount; ++commandIndex)
		{
			StartupCommand* command = &gStartupCommands[commandIndex];

			SendCommandCode(command->code);

			if (command->length > 0)
			{
				SendCommandParameters(command->parameters, command->length);
			}
		}

		ESP_LOGI(LOG_TAG, "Initialized display");
	}
}

void Odroid_DrawFrame(uint16_t* buffer)
{
	// Set drawing window width to (0, LCD_WIDTH)
	uint8_t drawWidth[] = { 0, 0, UPPER_BYTE_16(LCD_WIDTH), LOWER_BYTE_16(LCD_WIDTH) };
	SendCommandCode(COLUMN_ADDRESS_SET);
	SendCommandParameters(drawWidth, ARRAY_COUNT(drawWidth));

	// Set drawing window height to (0, LCD_HEIGHT)
	uint8_t drawHeight[] = { 0, 0, UPPER_BYTE_16(LCD_HEIGHT), LOWER_BYTE_16(LCD_HEIGHT) };
	SendCommandCode(PAGE_ADDRESS_SET);
	SendCommandParameters(drawHeight, ARRAY_COUNT(drawHeight));

	// Send the buffer to the display
	SendCommandCode(MEMORY_WRITE);
	SendCommandParameters((uint8_t*)buffer, LCD_WIDTH * LCD_HEIGHT * LCD_DEPTH);
}

