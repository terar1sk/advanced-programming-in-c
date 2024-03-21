#include <stdbool.h>
#include <stdio.h>
#include "k.h"
#include "hof.h"
#include "ui.h"

int main() {
    struct game game = {
        .board = {
            {' ', ' ', ' ', 'A'},
            {' ', ' ', ' ', ' '},
            {' ', ' ', ' ', 'B'},
            {' ', ' ', 'A', 'D'}
        },
        .score = 0
    };

    int y, x;
    //add_random_tile(&game);
    //add_random_tile(&game);
    render(game);
    do{
        printf("\nEnter side: ");
        scanf("%d %d", &y, &x);
        if(update(&game, y, x)) {
            add_random_tile(&game);
            render(game);
        }
        else
            printf("You can't move\n");
    }while((y != 0 || x != 0) && is_move_possible(game) && is_game_won(game) == false);
    if(is_game_won(game)) {
        printf("You won!\n");
    }else {
        printf("You loose!\n");
    }
    
    struct player list[10];
    int count = load(list);

        for(int i = 0; i < count; i++) {
        printf("%s - %d\n", list[i].name, list[i].score);
    }

    struct player list2[10] = {
        {"John", 150},
        {"Genry", 170},
        {"Aenry", 170}
    };

    save(list2, 3);

    int size = 10;
    struct player list3[10] = {
        {"manager", 5000},
        {"manager", 4000},
        {"manager", 4000},
        {"manager", 2000},
        {"manager", 1000},
        {"manager", 500},
        {"manager", 400},
        {"manager", 300},
        {"manager", 200},
        {"manager", 100},
    };
    struct player player = {.name="John", .score=100};;

    add_player(list3, &size, player);
    for(int i = 0; i < size; i++) {
        printf("%s - %d\n", list3[i].name, list3[i].score);
    }
    return 0;
}
