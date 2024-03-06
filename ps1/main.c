#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include "bmp.h"

int main() {
    char* reversed = reverse("Hello world!");
    if (reversed == NULL) {
        return 1; 
    }
    
    printf("%s\n", reversed);
    free(reversed);
    return 0;
}


