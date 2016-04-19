#ifndef CONNECT4
#define CONNECT4

#include <stdint.h>

typedef struct {
    uint8_t x : 4; // 0 - 6 for x index
    uint8_t y : 4; // 0-5 for y index
} move_t;

typedef move_t (* ai_move)(move_t);
#define ai_init __attribute((constructor))

uint8_t create_ai(ai_move ai_fn);

#endif
