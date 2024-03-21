#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>

#include "k.h"


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


bool is_move_possible(const struct game game){
    for(int a = 0; a < SIZE; ++a){
        for(int b = 0; b < SIZE; ++b){
            if(game.board[a][b] == ' '){
                return true;
            }
        }
    }
    for(int a = 0; a < SIZE; ++a){
        for(int b = 0; b < SIZE - 1; ++b){
            if(game.board[a][b] == game.board[a][b + 1]){
                return true;
            }
        }
    }
    for(int a = 0; a < SIZE - 1; ++a){
        for(int b = 0; b < SIZE; ++b){
            if(game.board[a][b] == game.board[a + 1][b]){
                return true;
            }
        }
    }
    
    return false;
}


bool update(struct game *game, int dy, int dx){
    if(dy != -1 && dy != 0 && dy != 1) return false;
    if(dx != -1 && dx != 0 && dx != 1) return false;
    if(dy != 0 && dx != 0) return false;

    bool moved = false;

    if(dy == 1){
        for(int j = 0; j < SIZE; ++j){
            for(int i = 1; i < SIZE; ++i){
                for(int k = i; k > 0; --k){
                    if(game->board[k][j] == ' '){
                        game->board[k][j] = game->board[k - 1][j];
                        game->board[k - 1][j] = ' ';
                        moved = true;
                    }
                    else if(game->board[k][j] == game->board[k - 1][j]){
                        game->board[k][j]++;
                        game->score += 1 << (game->board[k][j] - 'A');
                        game->board[k - 1][j] = ' ';
                        moved = true;
                        break;
                    }
                }
            }
        }
    }

    if(dy == -1){
        for(int j = 0; j < SIZE; ++j){
            for(int i = SIZE - 2; i >= 0; --i){
                for(int k = i; k < SIZE - 1; ++k){
                    if(game->board[k][j] == ' '){
                        game->board[k][j] = game->board[k + 1][j];
                        game->board[k + 1][j] = ' ';
                        moved = true;
                    }
                    else if(game->board[k][j] == game->board[k + 1][j]){
                        game->board[k][j]++;
                        game->score += 1 << (game->board[k][j] - 'A');
                        game->board[k + 1][j] = ' ';
                        moved = true;
                        break;
                    }
                }
            }
        }
    }

    if(dx == 1){
        for(int i = 0; i < SIZE; ++i){
            for(int j = 1; j < SIZE; ++j){
                for(int k = j; k > 0; --k){
                    if(game->board[i][k] == ' '){
                        game->board[i][k] = game->board[i][k - 1];
                        game->board[i][k - 1] = ' ';
                        moved = true;
                    }
                    else if(game->board[i][k] == game->board[i][k - 1]){
                        game->board[i][k]++;
                        game->score += 1 << (game->board[i][k] - 'A');
                        game->board[i][k - 1] = ' ';
                        moved = true;
                        break;
                    }
                }
            }
        }
    }

    if(dx == -1){
        for(int i = 0; i < SIZE; ++i) {
            for(int j = SIZE - 2; j >= 0; --j){
                for(int k = j; k < SIZE - 1; ++k){
                    if(game->board[i][k] == ' '){
                        game->board[i][k] = game->board[i][k + 1];
                        game->board[i][k + 1] = ' ';
                        moved = true;
                    }
                    else if(game->board[i][k] == game->board[i][k + 1]){
                        game->board[i][k]++;
                        game->score += 1 << (game->board[i][k] - 'A');
                        game->board[i][k + 1] = ' ';
                        moved = true;
                        break;
                    }
                }
            }
        }
    }

    return moved;
}
