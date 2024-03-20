#include <stdbool.h>
#include <stdio.h>
#include "k.h"


int main(){

	// game is not won
struct game game = {
    .board = {
        {'A', ' ', ' ', ' '},
        {' ', ' ', ' ', ' '},
        {' ', ' ', ' ', 'A'},
        {'B', ' ', ' ', ' '}
    },
    .score = 0
};

printf("is won: %d\n", is_game_won(game));
// stdout: 0

return 0;
}
