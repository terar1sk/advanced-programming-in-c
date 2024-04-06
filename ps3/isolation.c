#include <stdio.h>
#include <stdlib.h>

int main(){
    int c1 = 20;
    int c2 = 0;
    int c3 = 0;
    int u = 0;
    int p = 0;
    int desk[41][41];
    for(int a = 0; a < 41; a++){
        for(int b = 0; b < 41; b++){
            desk[a][b]=228228;
        }
    }
    scanf("%d", &u);
    scanf("%d", &p);
    int dn[u][p];
    for(int a = 0; a < u; a++){
        for(int b = 0; b < p; b++){
            dn[a][b]=228228;
        }
    }
    if(p == 1){
        printf("%d",p);
        return 0;
    }
    if(u == 1){
        printf("1");
        return 0;
    }
    int m1[u][p];
    for(int n2 = 0; n2 < u; n2++){
        for(int k2 = 0; k2 < p; k2++){
            scanf("%d", &m1[n2][k2]);
        }
    }
    for(int n1 = 0; n1 < u; n1++){
        for(int k1 = 0; k1 < p; k1++){
            c1 = 20;
            c2 = 0;
            int a = c1;
            int q = c2;
                    if(k1 == 0){
                          desk[q][a]=m1[n1][k1];
                        goto K1;
                    }

                if(desk[q][a]!=228228){
                        for(int t=0; t<k1; t++){
                            if(desk[q][a]==228228)
                                break;
                            if(m1[n1][k1] > desk[q][a]){
                                a++;
                                q++;
                                continue;
                            }
                            else if(m1[n1][k1] < desk[q][a]){
                                a--;
                                q++;
                                continue;
                            }
                        }
                    }
                    if(k1 == (p-1)){
                        if(m1[n1][k1] > desk[q][a]){
                              desk[q][a] = m1[n1][k1];
                        }
                        else if(m1[n1][k1] < desk[q][a]){
                              desk[q][a] = m1[n1][k1];
                        }
                        for(int c = 0; c < 41; c++){
                               for(int b = 0; b < 41; b++){
                                   if(desk[c][b]!=228228){
                                        dn[n1][c3] = b;
                                         c3++;
                                   }
                               }
                           }
                          c3=0;
                        for(int a = 0; a < 41; a++){
                               for(int b = 0; b < 41; b++){
                                     desk[b][a]=228228;
                               }
                           }
                        goto K2;
                    }


                    if(desk[q][a]==228228){
                          desk[q][a]=m1[n1][k1];
                    }
        K1:
            continue;
        }
    K2:
        continue;
    }
    int sum = u;
    int sc = 0;
    for(int s = 0; s < u; s++){
        for(int q=(s+1); q < u; q++){
            for(int e = 0; e < p; e++){
                if(dn[s][e] == dn[q][e]){
                    sc++;
                }
            }
            if(sc == p){
                sum--;
            }
            sc=0;
        }
    }
    printf("%d\n", sum);
    return 0;
}

