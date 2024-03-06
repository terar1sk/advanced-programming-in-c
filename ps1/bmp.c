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


char* vigenere_encrypt(const char* key, const char* text){
    if(key == NULL || text == NULL){
        return NULL;
    }
    int kl = strlen(key);
    int tl = strlen(text);

    char* encrypted = (char*)malloc((tl + 1) * sizeof(char));
    if(encrypted == NULL){
        return NULL;
    }
    for(int a = 0, b = 0; a < tl; ++a, ++b){
        if(b == kl){
            b = 0;
        }
        char key_char = toupper(key[b]) - 'A';
        char text_char = toupper(text[a]);
        if(isalpha(text_char)){
            encrypted[a] = ((text_char - 'A' + key_char) % 26) + 'A';
        }
        else{
            encrypted[a] = text_char; 
            --b;
        }
    }
    encrypted[tl] = '\0';
    return encrypted;
}

char* vigenere_decrypt(const char* key, const char* text) {
    if(key == NULL || text == NULL){
        return NULL;
    }
    int kl = strlen(key);
    int tl = strlen(text);

    char* decrypted = (char*)malloc((tl + 1) * sizeof(char));
    if(decrypted == NULL){
        return NULL;
    }
    for(int a = 0, b = 0; a < tl; ++a, ++b){
        if(b == kl){
            b = 0;
        }
        char key_char = toupper(key[b]) - 'A';
        char text_char = toupper(text[a]);
        if(isalpha(text_char)){
            decrypted[a] = ((text_char - 'A' - key_char + 26) % 26) + 'A';
        }
        else{
            decrypted[a] = text_char;
            --b;
        }
    }
    decrypted[tl] = '\0';
    return decrypted;
}
