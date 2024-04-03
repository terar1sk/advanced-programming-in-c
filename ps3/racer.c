#include<stdio.h>
#include <stdbool.h>
#include<math.h>

void calcul(int *size, int *t, int *s, int *v, float *border, float *frontier);
float find(int *size, int *t, int *s, int *v, float *border, float *frontier);
int test(int *size, int *t, int *s, int *v, float *k, float *r);

void calcul(int *size, int *t, int *s, int *v, float *border, float *frontier){
	float tp, r;
	tp = v[0];
	for(int a=0; a< *size; a++){
		if(v[a]< tp){
			tp = (float)v[a];
		}
	}
	
	tp = -tp;
	*border =tp;
	while(true){
		tp=tp+1;
		test(size, t, s, v, &tp, &r);
		if(r < 0.0){
			*frontier = tp;
			break;
		}
	}
}

int test(int *size, int *t, int *s, int *v, float *k, float *r){
	*r = 0.0;
	for(int a=0; a<*size; a++){
		*r += ((float)s[a]/((float)v[a]+*k));
	}
	*r -= (float)*t;
	if(*r <=0.0000000009 && *r >= -0.0000000001){
		return 1;
	}
	else{
		return 0;
	}
}

float find(int *size, int *t, int *s, int *v, float *border, float *frontier){
	float nr =0.0;
	float r =0.0;
	while(true){
		nr =(*border + *frontier)/2;
		if(test(size, t, s, v,&nr, &r)){
			return nr;
		}
		else{
			if(r > 0){
				*border=nr;
			}
			if(r < 0){
				*frontier = nr;
			}
		}
	}
	return 0;
}

int main(){
	int t=0;
	int size=0;
	int s[199999]={0};
	int v[199999]={0};
	long double k=0.0;
	float border=0.0;
	float frontier=0.0;

	scanf("%d %d", &size, &t);
	for(int i=0; i<size; i++){
		scanf("%d %d", &s[i], &v[i]);
	}
	calcul(&size, &t, s, v, &border, &frontier);
	k = find(&size, &t, s, v, &border, &frontier);
	printf("%Lf\n",k);
	
	return 0;
}

