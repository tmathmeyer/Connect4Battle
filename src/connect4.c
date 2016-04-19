#include <time.h>
#include <stdlib.h>
#include <stdio.h>
#include "connect4.h"

ai_move ai_a = 0;
ai_move ai_b = 0;

uint8_t create_ai(ai_move ai_function) {
    if (ai_a == 0) {
        int x = time(0);
        printf("%i\n", x);
        srand(x);
        ai_a = ai_function;
    } else if (ai_b == 0) {
        ai_b = ai_function;
    } else {
        puts("more than two players compiled in! only two please");
        exit(1);
    }
    uint8_t res = rand();
    return res;
}

move_t timeout_ai_move(ai_move ai, move_t m, int64_t time) {
    move_t result;
    clock_t start = clock(), diff;
    result = ai(m);
    diff = clock() - start;
    if (diff > time) {
        printf("AI timed out!");
        result.x = 11;
    }
    return result;
}

int make_move(uint8_t board[7][6], move_t *move, uint8_t player) {
    for(int i=0;i<6;i++) {
        if(board[move->x][i] == 2) {
            board[move->x][i] = player;
            move->y = i;
            return 1;
        }
    }
    return 0;
}

void print_board(uint8_t board[7][6]) {
    printf("board so far: \n");
    for(int i=0;i<6;i++) {
        printf("| ");
        for(int j=0;j<7;j++) {
            switch(board[j][5-i]) {
                case  1: printf("x "); break;
                case  0: printf("o "); break;
                case  2: printf("  "); break;
                default: exit(0);
            }
        }
        printf("|\n");
    }
    printf("-----------------\n\n");
}

int no_winner(uint8_t board[7][6], move_t last) {
    if (last.x > 6) {
        return 1; // invalid move, catch this elsewhere
    }

    uint8_t player = board[last.x][last.y];

    // check 4 down are the same
    if (last.y > 2) {
        int down = 0;
        for(int i=last.y; i>=0; i--) {
            if (player == board[last.x][i]) {
                down++;
                if (down>=4) {
                    puts("down");
                    return 0; // this player won!
                }
            } else {
                i=0;
            }
        }
    }

    { // check horizontals
        int max_sy = last.x;
        int min_sy = last.x;
        while(max_sy<7 && board[max_sy][last.y] == player) {
            max_sy++;
        }
        while(min_sy>0 && board[min_sy-1][last.y] == player) {
            min_sy--;
        }
        if (max_sy - min_sy >= 4) {
            puts("horizontal");
            return 0; // this player won!
        }
    }

    { // check positive slope
        int lr[2] = {last.x, last.y};
        int ul[2] = {last.x, last.y};
        while(ul[0]<7 && ul[1]<6 && board[ul[0]][ul[1]] == player) {
            ul[1]++;
            ul[0]++;
        }
        while(lr[0]>0 && lr[1]>0 && board[lr[0]-1][lr[1]-1] == player) {
            lr[1]--;
            lr[0]--;
        }
        if (ul[0] - lr[0] >= 4) {
            puts("positive slope");
            return 0; // this player won!
        }
    }

    { // check negative slope
        int ll[2] = {last.x, last.y};
        int ur[2] = {last.x, last.y};
        while(ll[0]<7 && ll[1]>0 && board[ll[0]+1][ll[1]-1] == player) {
            ll[1]--;
            ll[0]++;
        }
        while(ur[0]>0 && ur[1]<6 && board[ur[0]][ur[1]] == player) {
            ur[1]++;
            ur[0]--;
        }
        if (ll[0] - ur[0] >= 4) {
            puts("positive slope");
            return 0; // this player won!
        }
    }

    return 1; // no winner for now
}

int main(int argc, char **argv) {
    (void) argc;
    (void) argv;
    if (ai_a == 0 || ai_b == 0) {
        puts("two players must be compiled in");
        exit(1);
    }
    uint8_t current = rand() & 0x01;
    uint8_t board[7][6];
    for(int i=0;i<6;i++) {
        for(int j=0;j<7;j++) {
            board[j][i] = 2;
        }
    }

    move_t last = {.x=11, .y=11};

    while(no_winner(board, last)) {
        last = timeout_ai_move(current?ai_a:ai_b, last, 1000000000);
        if (!make_move(board, &last, current)) {
            current = 1 - current;
            printf("invalid move from player: %c\n", current?'x':'o');
            break;
        }
        print_board(board);
        current = 1 - current;
    }
    printf("winner is player: %c\n", current?'o':'x');
}
