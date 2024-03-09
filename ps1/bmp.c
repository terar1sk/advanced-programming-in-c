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
    if(key == NULL || text == NULL || key[0] == '\0' || text[0] == '\0'){
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
    char key_char = toupper(key[b]);
    if(isalpha(key_char)){
        if(isalpha(text[a])){
            encrypted[a] = ((toupper(text[a]) - 'A' + (key_char - 'A')) % 26) + 'A';
        }
        else{
            encrypted[a] = text[a]; 
            --b;
        }
    }
    else{
        encrypted[a] = text[a];
        --b;
    }
}
    encrypted[tl] = '\0';
    return encrypted;
}

char* vigenere_decrypt(const char* key, const char* text) {
    if(key == NULL || text == NULL || key[0] == '\0' || text[0] == '\0'){
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
