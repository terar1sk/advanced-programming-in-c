#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main(){
char n[199999];
int board[199999];
long long int k=0;

scanf("%199999[^\n]", n);
int len = strlen(n);

for(int a=0; a< len; a++){
	board[a] = n[a]-'0';
	k=k+board[a];
}

int rez = 0;
    while(k >= 10){
        for(int i = k; i > 0; i/=10){
	    rez += i%10;
	}
	k = rez;
	rez = 0;
    }

    printf("%lld\n",k);
    return 0;
}

