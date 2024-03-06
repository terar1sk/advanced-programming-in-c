#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include "bmp.h"

char* reverse(const char* text){
    if(text == NULL){
        return NULL;
    }

    int lgh = strlen(text);
    char* reversed = (char*)malloc((lgh + 1) * sizeof(char)); 
    if(reversed == NULL){
        return NULL;
    }

    for(int a = 0; a < lgh; a++){
        reversed[a] = toupper(text[lgh - a - 1]);
    }
    reversed[lgh] = '\0';
    return reversed;
}

