#ifndef CONNECT4
#define CONNECT4

#include <stdint.h>

typedef struct {
    uint8_t x : 4;
    uint8_t y : 4;
} move_t;

typedef move_t (* ai_move)(move_t);
#define ai_init __attribute((constructor))

uint8_t create_ai(ai_move);

#endif
