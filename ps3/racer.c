#include <stdio.h>

int main(){
    int c, d;
    scanf("%d %d", &c, &d);

    double td = 0.0;
    double tw = 0.0;

    for(int a = 0; a < c; a++){
        int e, f;
        scanf("%d %d", &e, &f);
          td += e;
          tw += e * f;
    }

    double g = (tw / td) - 1;
    printf("%.9lf\n", g);

    return 0;
}

