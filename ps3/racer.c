#include<stdio.h>
#include <stdbool.h>
#include<math.h>

void calcul(int *size, int *c, int *d, int *f, float *border, float *frontier);
float find(int *size, int *c, int *d, int *f, float *border, float *frontier);
int test(int *size, int *c, int *d, int *f, float *g, float *e);

void calcul(int *size, int *c, int *d, int *f, float *border, float *frontier){
    float tp, e;
    tp = f[0];
    for(int a=0; a< *size; a++){
        if(f[a]< tp){
            tp = (float)f[a];
        }
    }
    
    tp = -tp;
    *border =tp;
    while(true){
        tp=tp+1;
        if(!test(size, c, d, f, &tp, &e) || e >= 0.0){
            *frontier = tp;
            break;
        }
    }
}

int test(int *size, int *c, int *d, int *f, float *g, float *e){
    *e = 0.0;
    for(int a=0; a<*size; a++){
        *e += ((float)d[a]/((float)f[a]+*g));
    }
    *e -= (float)*c;
    return fabs(*e) <= 1e-9;
}

float find(int *size, int *c, int *d, int *f, float *border, float *frontier){
    float nr = 0.0;
    float e = 0.0;
    while(true){
        nr = (*border + *frontier) / 2;
        if(test(size, c, d, f, &nr, &e)){
            return nr;
        }
        else{
            if(e > 0){
                *border = nr;
            }
            else{
                *frontier = nr;
            }
        }
    }
}

int main(){
    int c=0;
    int size=0;
    int d[199999]={0};
    int f[199999]={0};
    long double g=0.0;
    float border=0.0;
    float frontier=0.0;

    scanf("%d %d", &size, &c);
    for(int i=0; i<size; i++){
        scanf("%d %d", &d[i], &f[i]);
    }
    calcul(&size, &c, d, f, &border, &frontier);
    g = find(&size, &c, d, f, &border, &frontier);
    printf("%Lf\n",g);
    
    return 0;
}

