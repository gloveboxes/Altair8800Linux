#include "front_panel_pi_sense_hat.h"

static uint16_t panel_buffer[NUM_OF_LEDS];

void init_altair_hardware(void)
{
    pi_sense_hat_init();
}

static uint16_t *uint8_to_uint16_t(uint8_t bitmap, uint16_t *buffer)
{
    uint16_t mask = 1;
    uint8_t bit_number = 8;
    uint8_t pixel_number = 0;

    while (pixel_number < 8) {
        buffer[pixel_number++] = bitmap & mask ? RGB565_RED : 0x0000;
        mask = (uint16_t)(mask << 1);
    }
}

void update_panel_status_leds(uint8_t status, uint8_t data, uint16_t bus)
{
    uint8_to_uint16_t(status, panel_buffer);
    uint8_to_uint16_t(data, panel_buffer + (3 * 8));

    uint8_to_uint16_t((uint8_t)(bus >> 8), panel_buffer + (6 * 8));
    uint8_to_uint16_t((uint8_t)(bus), panel_buffer + (7 * 8));

    pi_sense_8x8_panel_update(panel_buffer, PI_SENSE_8x8_BUFFER_SIZE);
}