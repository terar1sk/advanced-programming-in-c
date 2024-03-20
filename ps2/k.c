#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>

#include "k.h"

/*
void add_random_tile(struct game *game){
    int row, col;
    // find random, but empty tile
    do{
        row = rand() % SIZE;
        col = rand() % SIZE;
    }while(game->board[row][col] != ' ');

    // place to the random position 'A' or 'B' tile
    if(rand() % 2 == 0){
        game->board[row][col] = 'A';
    }else{
        game->board[row][col] = 'B';
    }
}
*/

bool is_game_won(const struct game current_game){
    for(int i = 0; i < SIZE; ++i){
        for(int j = 0; j < SIZE; ++j){
            if(current_game.board[i][j] == 'K'){
                return true;
            }
        }
    }
    return false;
}

