#include "connect4.h"

move_t make_move(move_t prev);

/*
 * Initialize any memory things here.
 * you are not guaranteed to have the first
 * move
 */
void ai_init setup_function(void) {
    create_ai(make_move);
}

/* 
 * if other player's move is 11, 11, there was no
 * previous move
 */
move_t make_move(move_t prev) {
    move_t a = {.x=0, .y=(prev.y+1)};
    return a;
}
