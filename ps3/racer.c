#include <stdio.h>
#include <stdbool.h>
#include <math.h>

void calcul(int *size, int *c, int *d, int *f, float *border, float *frontier);
float find(int *size, int *c, int *d, int *f, float *border, float *frontier);
int test(int *size, int *c, int *d, int *f, float *g, float *e);

void calcul(int *size, int *c, int *d, int *f, float *border, float *frontier){
  float tm, e;
  tm = f[0];
  
  for(int a = 0; a < *size; a++){
    if(f[a] < tm){
      tm = (float)f[a];
    }
  }
  tm = -tm;
  *border = tm;

  while(true){
    tm = tm + 1;
    test(size, c, d, f, &tm, &e);

    if(e < 0.0){
      *frontier = tm;
      break;
    }
  }
}

int test(int *size, int *c, int *d, int *f, float *g, float *e){
  *e = 0.0;

  for(int a = 0; a < *size; a++){
    *e += ((float)d[a] / ((float)f[a] + *g));
  }
  *e -= (float)*c;
  if(*e <= 0.0000000009 && *e >= -0.0000000001){
    return 1;
  }
  else{
    return 0;
  }
}

float find(int *size, int *c, int *d, int *f, float *border, float *frontier){
  float nn =0.0;
  float e =0.0;

  while(true){
    nn = (*border + *frontier) / 2;
    if(test(size, c, d, f, &nn, &e)){
      return nn;
    }
    else{
      if(e > 0){
        *border=nn;
      }
      if(e < 0){
        *frontier = nn;
      }
    }
  }
  return 0;
}

int main(){
  int c = 0;
  int size = 0;
  int d[199999] = {0};
  int f[199999] = {0};
  long double g = 0.0;
  float border = 0.0;
  float frontier = 0.0;

  scanf("%d %d", &size, &c);
  for(int a = 0; a < size; a++){
    scanf("%d %d", &d[a], &f[a]);
  }

  calcul(&size, &c, d, f, &border, & frontier);
  g = find(&size, &c, d, f, &border, &frontier);
  printf("%Lf\n",g);

  return 0;
}


