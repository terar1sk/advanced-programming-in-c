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
    for(int a = 0; a < SIZE; ++a){
        for(int b = 0; b < SIZE; ++b){
            if(current_game.board[a][b] == 'K'){
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
    if(dy != -1 && dy != 0 && dy != 1){
      return false;
    }
    if(dx != -1 && dx != 0 && dx != 1){
      return false;
    }
    if(dy != 0 && dx != 0){
      return false;
    }

    bool move = false;

    if(dy == 1){
        for(int a = 0; a < SIZE; ++a){
            for(int b = 1; b < SIZE; ++b){
                for(int c = a; c > 0; --c){
                    if(game->board[c][b] == ' '){
                        game->board[c][b] = game->board[c - 1][b];
                        game->board[c - 1][b] = ' ';
                        move = true;
                    }
                    else if(game->board[c][b] == game->board[c - 1][b]){
                        game->board[c][b]++;
                        game->score += 1 << (game->board[c][b] - 'A');
                        game->board[c - 1][b] = ' ';
                        move = true;
                        break;
                    }
                }
            }
        }
    }

    if(dy == -1){
        for(int b = 0; b < SIZE; ++b){
            for(int a = SIZE - 2; a >= 0; --a){
                for(int c = a; c < SIZE - 1; ++c){
                    if(game->board[c][b] == ' '){
                        game->board[c][b] = game->board[c + 1][b];
                        game->board[c + 1][b] = ' ';
                        move = true;
                    }
                    else if(game->board[c][b] == game->board[c + 1][b]){
                        game->board[c][b]++;
                        game->score += 1 << (game->board[c][b] - 'A');
                        game->board[c + 1][b] = ' ';
                        move = true;
                        break;
                    }
                }
            }
        }
    }

    if(dx == 1){
        for(int a = 0; a < SIZE; ++a){
            for(int b = 1; b < SIZE; ++b){
                for(int c = b; c > 0; --c){
                    if(game->board[a][c] == ' '){
                        game->board[a][c] = game->board[a][c - 1];
                        game->board[a][c - 1] = ' ';
                        move = true;
                    }
                    else if(game->board[a][c] == game->board[a][c - 1]){
                        game->board[a][c]++;
                        game->score += 1 << (game->board[a][c] - 'A');
                        game->board[a][c - 1] = ' ';
                        move = true;
                        break;
                    }
                }
            }
        }
    }

    if(dx == -1){
        for(int a = 0; a < SIZE; ++a) {
            for(int b = SIZE - 2; b >= 0; --b){
                for(int c = b; c < SIZE - 1; ++c){
                    if(game->board[a][c] == ' '){
                        game->board[a][c] = game->board[a][c + 1];
                        game->board[a][c + 1] = ' ';
                        move = true;
                    }
                    else if(game->board[a][c] == game->board[a][c + 1]){
                        game->board[a][c]++;
                        game->score += 1 << (game->board[a][c] - 'A');
                        game->board[a][c + 1] = ' ';
                        move = true;
                        break;
                    }
                }
            }
        }
    }

    return move;
}
