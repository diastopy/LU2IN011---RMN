#include <stdio.h>
#include <stdlib.h>
#include <time.h>

void prodmatmat(double *mA, double *mB, double *mF, int n){
    for(int i = 0; i < n; i++){
        for(int j = 0; j < n; j++){
        
            *(mF + i*n + j) = 0;
            
            for(int k = 0; k < n; k++) {
                *(mF + i*n + j) += *(mA + i*n + k) * *(mB + k*n + j);
            }
        }
    }
}



void prodmatmatopti(double *mA, double *mB, double *mF, int n){
    double *pa, *pb, *pp, *pa2, *pb2;
    
    for(pa = mA, pp = mF; pa < mA + n*n; pa += n){
        for(pb = mB; pb < mB + n; pb++, pp++){
            *pp = 0;
            for(pa2 = pa, pb2 = pb; pa2 < pa + n; pa2++, pb2 += n){
                *pp += (*pa2) * (*pb2);
            }
        }
    }
}

int main(){
    
    int n;
    printf("Entrez la dimension des matrices :\n"); scanf("%d",&n);
    
    double *mA, *mB, *mF;
    mA = (double *) malloc(sizeof(double)*(n*n)); double *pa;
    mB = (double *) malloc(sizeof(double)*(n*n)); double *pb;
    mF = (double *) malloc(sizeof(double)*(n*n)); 
    
    for(pa = mA, pb = mB; pa < mA + n*n && pb < mB + n*n; pa++, pb++){
        *pa = (double)rand()/RAND_MAX * (2.0 - 1.0);
        *pb = (double)rand()/RAND_MAX * (2.0 - 1.0);
    }



    clock_t start, stop; 
    
    start = clock();
    prodmatmat(mA,mB,mF,n);
    stop = clock();
    
    double tempsClassique = (stop - start)*1000.0 / CLOCKS_PER_SEC;
    printf("Tps de calcul avec formulation classique (n = %d) : %.3f ms\n", n, tempsClassique);
    
    
    start = clock();
    prodmatmatopti(mA,mB,mF,n);
    stop = clock();
    
    double tempsOpti = (stop - start)*1000.0 / CLOCKS_PER_SEC;
    printf("Tps de calcul avec formulation optimisee (n = %d) : %.3f ms\n", n, tempsOpti);
    
    double resultatDiff = tempsClassique - tempsOpti;
    
    if (resultatDiff >= 0)
        printf("La version optimisee est plus rapide de %.3f ms.\n", resultatDiff);
    else
        printf("La version classique est plus rapide de %.3f ms.\n", -resultatDiff);
    
    free(mA); free(mB); free(mF);
    
    return 0;
    /*
    Pour n=10
    -> Opti      = 0 ms
    -> Classique = 0 ms

    Pour n=100
    -> Opti     = 8 ms
    -> Clasique = 8 ms

    Pour n=500
    -> Opti      = 1104 ms
    -> Classique = 1190 ms

    Pour n=1000
    -> Opti      = 9733 ms
    -> Classique = 10592 ms

    On remarque donc que, plus n augmente, plus il faudra utiliser la version optimisée*/
}







/*
Résultats avec formulation optimisée:
Pour n=10, T=1.731000
Pour n=100, T=5.105000
Pour n=500, T=
Résultats avec formulation classique:
Pour n=10, T=1.844000
Pour n=100, T=7.797000
Pour n=500, T=
*/