#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include "bmp.h"

int main(){
    char* reversed = reverse("Hello world!");
    if(reversed == NULL){
        return 1;
    }
    printf("%s\n", reversed);
    free(reversed);

    
    char* encrypted;
    encrypted = vigenere_encrypt("CoMPuTeR", "Hello world!");
    if(encrypted != NULL){
        printf("%s\n", encrypted);
        free(encrypted);
        return 0;
    }
    
    char* decrypted;
    decrypted = vigenere_decrypt("CoMPuTeR", "Hello world!");
    if(decrypted != NULL){
        printf("%s\n", decrypted);
        free(decrypted);
        return 0;
    }
    
    return 1;
}
