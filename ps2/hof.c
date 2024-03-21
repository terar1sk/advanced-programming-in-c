#include <stdio.h>
#include <stdbool.h>
#include <string.h>
#include "hof.h"

#define MAX_ENTRIES 10

int load(struct player list[]){
    FILE *file = fopen(HOF_FILE, "r");
    if(file == NULL){
        /*printf("Error opening file for reading!\n");*/
        return -1;
    }

    int count = 0;
    while(fscanf(file, "%s %d", list[count].name, &list[count].score) == 2){
        count++;
        if(count >= MAX_ENTRIES){
            break;
        }
    }

    fclose(file);
    return count;
}

bool save(const struct player list[], const int size){
    FILE *file = fopen(HOF_FILE, "w");
    if(file == NULL){
        /*printf("Error opening file for writing!\n");*/
        return false;
    }
    for(int a = 0; a < size; a++){
        fprintf(file, "%s%s%d\n", list[a].name, DELIMITER, list[a].score);
    }

    fclose(file);
    return true;
}

bool add_player(struct player list[], int *size, const struct player new_player){
    if(*size == 0){
        list[0] = new_player;
        (*size)++;
        return true;
    }

    int ins_ind = 0;
    while(ins_ind < *size && (new_player.score > list[ins_ind].score || (new_player.score == list[ins_ind].score && strcmp(new_player.name, list[ins_ind].name) < 0))){
          ins_ind++;
    }
    if(*size < MAX_ENTRIES){
        for(int a = *size; a > ins_ind; a--){
            list[a] = list[a - 1];
        }
        list[ins_ind] = new_player;
        (*size)++;
        return true;
    }
    if(ins_ind >= MAX_ENTRIES){
        return false;
    }
    for(int a = MAX_ENTRIES - 1; a > ins_ind; a--){
        list[a] = list[a - 1];
    }
    list[ins_ind] = new_player;

    return true;
}

