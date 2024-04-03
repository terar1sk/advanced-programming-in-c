#include <stdio.h>

int sumnum(int a){
    int sum = 0;
    while(a > 0){
        sum += a % 10;
        a /= 10;
    }
    return sum;
}

int mm(int a){
    while(a >= 10){
      a = sumnum(a);
    }
    return a;
}

/*
int main(){
    int num;
    scanf("%d", &num);

    int result = mm(num);
    printf("%d\n", result);

    return 0;
}
*/

