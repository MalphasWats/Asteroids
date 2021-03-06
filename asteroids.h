#ifndef ASTEROIDS_H
# define ASTEROIDS_H

#include "GLYPH.h"

typedef struct Sprite {
    int16_t x;
    int16_t y;

    int16_t vx;
    int16_t vy;

    int16_t size;

    uint16_t tile;
} Sprite;

#define MAX_VELOCITY 6
#define UPDATE_DELAY 60
#define MOVE_DELAY 60
#define ACTION_DELAY 180

static const __flash uint8_t SHIP[] = {
    0x60, 0x98, 0xc6, 0xc1, 0xc6, 0x98, 0x60, 0x00,
    0x20, 0x50, 0x68, 0xe4, 0x82, 0xf1, 0x0f, 0x00,
    0x18, 0x34, 0x74, 0xe2, 0x82, 0x61, 0x19, 0x07,
    0x1c, 0xf4, 0xb4, 0x44, 0x22, 0x12, 0x0a, 0x06,
    0x7c, 0xba, 0x82, 0x44, 0x44, 0x28, 0x28, 0x10,
    0x38, 0x2f, 0x2d, 0x22, 0x44, 0x48, 0x50, 0x60,
    0x18, 0x2c, 0x2e, 0x47, 0x41, 0x86, 0x98, 0xe0,
    0x04, 0x0a, 0x16, 0x27, 0x41, 0x8f, 0xf0, 0x00,
    0x06, 0x19, 0x63, 0x83, 0x63, 0x19, 0x06, 0x00,
    0x00, 0xf0, 0x8f, 0x41, 0x27, 0x16, 0x0a, 0x04,
    0xe0, 0x98, 0x86, 0x41, 0x47, 0x2e, 0x2c, 0x18,
    0x60, 0x50, 0x48, 0x44, 0x22, 0x2d, 0x2f, 0x38,
    0x10, 0x28, 0x28, 0x44, 0x44, 0x82, 0xba, 0x7c,
    0x06, 0x0a, 0x12, 0x22, 0x44, 0xb4, 0xf4, 0x1c,
    0x07, 0x19, 0x61, 0x82, 0xe2, 0x74, 0x34, 0x18,
    0x00, 0x0f, 0xf1, 0x82, 0xe4, 0x68, 0x50, 0x20,
};

static const __flash uint8_t SHIP_MASKS[] = {
    0x9f, 0x07, 0x01, 0x00, 0x01, 0x07, 0x9f, 0xff,
    0xdf, 0x8f, 0x87, 0x03, 0x01, 0x00, 0xf0, 0xff,
    0xe7, 0xc3, 0x83, 0x01, 0x01, 0x80, 0xe0, 0xf8,
    0xe3, 0x03, 0x03, 0x83, 0xc1, 0xe1, 0xf1, 0xf9,
    0x03, 0x01, 0x01, 0x83, 0x83, 0xc7, 0xc7, 0xef,
    0xc7, 0xc0, 0xc0, 0xc1, 0x83, 0x87, 0x8f, 0x9f,
    0xe7, 0xc3, 0xc1, 0x80, 0x80, 0x01, 0x07, 0x1f,
    0xfb, 0xf1, 0xe1, 0xc0, 0x80, 0x00, 0x0f, 0xff,
    0xf8, 0xe0, 0x80, 0x00, 0x80, 0xe0, 0xf9, 0xff,
    0xff, 0x0f, 0x00, 0x80, 0xc0, 0xe1, 0xf1, 0xfb,
    0x1f, 0x07, 0x01, 0x80, 0x80, 0xc1, 0xc3, 0xe7,
    0x9f, 0x8f, 0x87, 0x83, 0xc1, 0xc0, 0xc0, 0xc7,
    0xef, 0xc7, 0xc7, 0x83, 0x83, 0x01, 0x01, 0x83,
    0xf9, 0xf1, 0xe1, 0xc1, 0x83, 0x03, 0x03, 0xe3,
    0xf8, 0xe0, 0x80, 0x01, 0x01, 0x83, 0xc3, 0xe7,
    0xff, 0xf0, 0x00, 0x01, 0x03, 0x87, 0x8f, 0xdf,
};

static const __flash uint8_t TORPEDO[] = {
    0x03, 0x03, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0xfc, 0xfc, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff,
};

static const __flash uint8_t ASTEROIDS[] = {
    0x00, 0x00, 0xe0, 0x10, 0x08, 0x04, 0x02, 0x12,
    0x2c, 0x44, 0x04, 0x04, 0x02, 0x02, 0x02, 0x02,
    0x04, 0x84, 0x48, 0x30, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x07, 0x08, 0xd0, 0x20, 0x20, 0x20,
    0x50, 0x48, 0x80, 0x00, 0x00, 0x00, 0x08, 0x96,
    0x01, 0x06, 0x18, 0x20, 0x20, 0xc0, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x06, 0x09, 0x10, 0x20, 0x10,
    0x08, 0x08, 0x08, 0x08, 0x30, 0x40, 0x41, 0x41,
    0x26, 0x18, 0x20, 0x20, 0x10, 0x0f, 0x00, 0x00,

    0x00, 0x00, 0xf0, 0x08, 0x04, 0x02, 0x02, 0x04, // 9
    0x08, 0x10, 0x20, 0x40, 0x40, 0x80, 0x80, 0x80,
    0x00, 0x00, 0x80, 0x80, 0x40, 0x80, 0x00, 0x00,
    0x00, 0x0f, 0x30, 0x40, 0x80, 0x04, 0x08, 0x30,
    0xc8, 0x04, 0x00, 0x20, 0x10, 0x28, 0x44, 0x42,
    0x01, 0x01, 0x00, 0x00, 0xe0, 0x1e, 0x01, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x03, 0x0c, 0x10, 0x10,
    0x08, 0x09, 0x0a, 0x04, 0x08, 0x10, 0x20, 0x20,
    0x10, 0x10, 0x08, 0x04, 0x03, 0x00, 0x00, 0x00,

    0x00, 0x00, 0x00, 0x60, 0x40, 0x00, 0x00, 0x00, // Debris (18)
    0x00, 0x00, 0x00, 0x04, 0x1c, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x20, 0x14, 0x08, 0x00,
    0x00, 0x12, 0x04, 0x00, 0x00, 0x00, 0x00, 0x00,

    0x00, 0x00, 0xb8, 0x44, 0x84, 0x04, 0x04, 0x04, // Medium (22)
    0x08, 0x08, 0x08, 0x10, 0xe0, 0x00, 0x00, 0x00,
    0x00, 0x1f, 0x20, 0x20, 0x40, 0x41, 0x41, 0x42,
    0x50, 0x48, 0x48, 0x48, 0x45, 0x42, 0x3c, 0x00,

    0x00, 0x00, 0x00, 0x00, 0xc0, 0x30, 0x08, 0x84,
    0x04, 0x04, 0x08, 0x30, 0xc0, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x07, 0x08, 0x14, 0x22, 0x21,
    0x20, 0x20, 0x46, 0x41, 0x40, 0x21, 0x1e, 0x00,

    0x00, 0x00, 0x38, 0x44, 0x44, 0x28, 0x10, 0x00, // Small (30)
    0x00, 0x00, 0x34, 0x4a, 0x24, 0x18, 0x00, 0x00,
    0x00, 0x00, 0x1c, 0x22, 0x44, 0x38, 0x00, 0x00,
    0x00, 0x00, 0x6c, 0x92, 0x84, 0x98, 0x60, 0x00,
};

static const __flash uint8_t ASTEROID_MASKS[] = {
    0xff, 0xff, 0x1f, 0x0f, 0x07, 0x03, 0x01, 0x01,
    0x03, 0x03, 0x03, 0x03, 0x01, 0x01, 0x01, 0x01,
    0x03, 0x03, 0x87, 0xcf, 0xff, 0xff, 0xff, 0xff,
    0xff, 0xff, 0xf8, 0xf0, 0x20, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x01, 0x07, 0x1f, 0x1f, 0x3f, 0xff, 0xff,
    0xff, 0xff, 0xff, 0xf9, 0xf0, 0xe0, 0xc0, 0xe0,
    0xf0, 0xf0, 0xf0, 0xf0, 0xc0, 0x80, 0x80, 0x80,
    0xc0, 0xe0, 0xc0, 0xc0, 0xe0, 0xf0, 0xff, 0xff,

    0xff, 0xff, 0x0f, 0x07, 0x03, 0x01, 0x01, 0x03, // 9
    0x07, 0x0f, 0x1f, 0x3f, 0x3f, 0x7f, 0x7f, 0x7f,
    0xff, 0xff, 0x7f, 0x7f, 0x3f, 0x7f, 0xff, 0xff,
    0xff, 0xf0, 0xc0, 0x80, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x00, 0xe0, 0xfe, 0xff,
    0xff, 0xff, 0xff, 0xff, 0xfc, 0xf0, 0xe0, 0xe0,
    0xf0, 0xf0, 0xf0, 0xf8, 0xf0, 0xe0, 0xc0, 0xc0,
    0xe0, 0xe0, 0xf0, 0xf8, 0xfc, 0xff, 0xff, 0xff,

    0xff, 0xff, 0xff, 0x9f, 0xbf, 0xff, 0xff, 0xff, // Debris (18)
    0xff, 0xff, 0xff, 0xfb, 0xe3, 0xff, 0xff, 0xff,
    0xff, 0xff, 0xff, 0xff, 0xdf, 0xeb, 0xf7, 0xff,
    0xff, 0xed, 0xfb, 0xff, 0xff, 0xff, 0xff, 0xff,

    0xff, 0xff, 0x47, 0x03, 0x03, 0x03, 0x03, 0x03, // Medium (22)
    0x07, 0x07, 0x07, 0x0f, 0x1f, 0xff, 0xff, 0xff,
    0xff, 0xe0, 0xc0, 0xc0, 0x80, 0x80, 0x80, 0x80,
    0x80, 0x80, 0x80, 0x80, 0x80, 0x81, 0xc3, 0xff,

    0xff, 0xff, 0xff, 0xff, 0x3f, 0x0f, 0x07, 0x03,
    0x03, 0x03, 0x07, 0x0f, 0x3f, 0xff, 0xff, 0xff,
    0xff, 0xff, 0xff, 0xf8, 0xf0, 0xe0, 0xc0, 0xc0,
    0xc0, 0xc0, 0x80, 0x80, 0x80, 0xc0, 0xe1, 0xff,

    0xff, 0xff, 0xc7, 0x83, 0x83, 0xc7, 0xef, 0xff, // Small (30)
    0xff, 0xff, 0xcb, 0x81, 0xc3, 0xe7, 0xff, 0xff,
    0xff, 0xff, 0xe3, 0xc1, 0x83, 0xc7, 0xff, 0xff,
    0xff, 0xff, 0x93, 0x01, 0x03, 0x07, 0x9f, 0xff,
};

static const __flash uint8_t STARFIELD[] = {
    0x00, 0x00, 0x00, 0x00, 0x00, 0x10, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x80, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x20, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x02, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x08, 0x14, 0x08, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x02, 0x05, 0x02, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x02, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x01, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x01, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x40, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x80, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x04, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x80, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x04, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x20, 0x70, 0xf8, 0x70, 0x20, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x20, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x20, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x20, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x20, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
};

#define MAX_ASTEROIDS 15
#define MAX_TORPEDOS 6

#define LARGE1 0
#define LARGE2 9

#define MEDIUM1 22
#define MEDIUM2 26

#define SMALL1  30
#define SMALL2  31
#define SMALL3  32
#define SMALL4  33

#define DEBRIS 18

uint8_t collide_with_asteroid(int16_t x, int16_t y);
void draw_asteroid(Sprite *a);

void asteroids_game(void);

#endif
