#include <stdio.h>
#include "connect4.h"

move_t make_move(move_t prev);
/*
 * Initialize any memory things here.
 * you are not guaranteed to have the first
 * move
 *
 * MUST BE NAMED setup
 */
void ai_init setup(void) {
    create_ai(make_move);
}

/* 
 * if other player's move is 11, 11, there was no
 * previous move
 *
 * MUST BE NAMED make_move
 */
move_t make_move(move_t prev) {
    int x = 0;
    scanf("%d", &x);
    prev.x = x;
    return prev;
}
