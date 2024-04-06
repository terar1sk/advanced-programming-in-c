#include <stdio.h>
#include <stdbool.h>
#include <math.h>

void calcul(int *size, int *c, int *d, int *f, float *border, float *frontier);
float find(int *size, int *c, int *d, int *f, float *border, float *frontier);
int test(int *size, int *c, int *d, int *f, float *g, float *e);

void calcul(int *size, int *c, int *d, int *f, float *border, float *frontier){
    float sum_sv = 0, sum_v = 0;
    for(int a = 0; a < *size; a++){
        sum_sv += d[a] * f[a];
        sum_v += f[a];
    }
    float j = (sum_sv - *c * sum_v) / (sum_v - *size * *c);
    *border = j;
    *frontier = j;
}

int test(int *size, int *c, int *d, int *f, float *g, float *e){
    *e = 0.0;
    for(int a = 0; a < *size; a++){
        *e += ((float)d[a] / ((float)f[a] + *g));
    }
    *e -= (float)*c;
    return fabs(*e) <= 1e-6;
}

float find(int *size, int *c, int *d, int *f, float *border, float *frontier){
    float left = *border, right = *frontier, middle;
    float e;
    while(right - left > 1e-6){
        middle = left + (right - left) / 2;
        if(test(size, c, d, f, &middle, &e)){
            right = middle;
        }
        else{
            left = middle;
   	}
    }
    return left + (right - left) / 2;
}

int main(){
    int c = 0;
    int size = 0;
    int d[1000] = {0};
    int f[1000] = {0};
    long double g = 0.0;
    float border = 0.0;
    float frontier = 0.0;

    scanf("%d %d", &size, &c);
    for(int a = 0; a < size; a++){
        scanf("%d %d", &d[a], &f[a]);
    }
    calcul(&size, &c, d, f, &border, &frontier);
    g = find(&size, &c, d, f, &border, &frontier);
    printf("%.9Lf\n", g);

    return 0;
}

