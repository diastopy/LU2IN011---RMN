#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <fenv.h>

void gauss_ap(float *a, float *b, int n){
    int i,j,k,il;
    float X1, X2;
    for(i=0;i<n-1;i++){
        X1=fabs(*(a + i*n + i));
        il=i;
        for(k = i+1; k < n; k++)
            if (X1<fabs(*(a + k*n + i))){
                X1 = fabs(*(a + k*n + i));
                il = k;
            };
        if (il != i){
            for(j=i;j<n;j++){
                X1 = *(a + il*n + j);
                *(a + il*n + j) = *(a + i*n + j);
                *(a + i*n + j) = X1;
            }
            X1 = *(b + il);
            *(b + il) = *(b + i);
            *(b + i) = X1;
        }
        X1 = *(a + i*n + i);
        for(k=i+1; k<n; k++)
            *(a + i*n + k) /= X1;
        *(b + i) /= X1;
        for(k=i+1;k<n;k++){
            X2 = *(a + k*n + i);
            for(j=i+1;j<n;j++)
                *(a + k*n + j) -= X2 * *(a + i*n + j);
            *(b + k) -= X2 * *(b+i);
        }
    }
    *(b + n-1) /= *(a + n*n -1);
    for(i=n-2;i>=0;i--){
        X1= *(b + i);
        for(k=i+1;k<n;k++)
            X1 -= *(a + i*n + k) * *(b + k);
        *(b + i) = X1;
    }
}

void gauss_sp(float *a, float *b, int n){
    int i,j,k;
    float X1, X2;
    for(i=0;i<n-1;i++){
        X1 = *(a + i*n + i);
        for(k=i+1; k<n; k++)
            *(a + i*n + k) /= X1;
        *(b + i) /= X1;
        for(k=i+1;k<n;k++){
            X2 = *(a + k*n + i);
            for(j=i+1;j<n;j++)
                *(a + k*n + j) -= X2 * *(a + i*n + j);
            *(b + k) -= X2 * *(b+i);
        }
    }
    *(b + n-1) /= *(a + n*n -1);
    for(i=n-2;i>=0;i--){
        X1= *(b + i);
        for(k=i+1;k<n;k++)
            X1 -= *(a + i*n + k) * *(b + k);
        *(b + i) = X1;
    }
}

int main(){
    int n;
    printf("Appuyez sur un chiffre entre 0 et 3 afin de definir un mode d'arrondi : 0 pour zero, 1 pour au_plus_pres, 2 pour moins_infini et 3 pour plus_infini\n");
    scanf("%d",&n);
    switch (n){
    case 0 : fesetround(FE_TOWARDZERO);break;
    case 1 : fesetround(FE_TONEAREST);break;
    case 2 : fesetround(FE_DOWNWARD);break;
    case 3 : fesetround(FE_UPWARD);break;
    }
    printf("\n");
    printf("Activite 1-1\n");
    float mA[16] = {2.5,1.5,1.7,2.5,
                    1.7,1.8,2.2,1.8,
                    2.0,1.2,2.5,3.0,
                    2.1,1.2,2.2,1.5};
    float mB[4] = {11.11,10.67,12.41,10.52};
    gauss_sp(mA,mB,4);
    for(int i=0;i<4;i++){
        printf("%.4f\t",mB[i]);
    }
    printf("\nActivite 2-1\n");
    float mC[16] = {21.0,130.0,0.0,2.1,
                    13.0,80.0,4.74,752.0,
                    0.0,-0.4,3.9816,4.2,
                    0.0,0.0,1.7,0.9};
    float mD[4] = {153.1,849.74,7.7816,2.6};
    gauss_sp(mC,mD,4);
    for(int i=0;i<4;i++){
        printf("%.4f\t",mD[i]);
    }

    printf("\nActivite 2-1\n");
    float mE[16] = {21.0,130.0,0.0,2.1,
                    13.0,80.0,4.74,752.0,
                    0.0,-0.4,3.9816,4.2,
                    0.0,0.0,1.7,0.9};
    float mF[4] = {153.1,849.74,7.7816,2.6};
    gauss_ap(mE,mF,4);
    for(int i=0;i<4;i++){
        printf("%.4f\t",mF[i]);
    }
    printf("\n\n");
}
/* Résultats :
    Sans mode d'arrondi : 
        Activite 1-1
        1.5000  0.8000  2.3000  0.9000
        Activite 2-1
        62.6199 -8.9540 0.0000  1.0000
        Activite 2-1
        0.9988  1.0002  1.0000  1.0000

    Mode arrondi pour 0 : 
        Activite 1-1
        1.5000  0.8000  2.3000  0.9000
        Activite 2-1
        62.6199 -8.9540 0.0000  1.0000
        Activite 2-1
        0.9992  1.0001  1.0000  1.0000

    Mode arrondi au plus près :
        Activite 1-1
        1.5000  0.8000  2.3000  0.9000
        Activite 2-1
        62.6199 -8.9540 0.0000  1.0000
        Activite 2-1
        0.9988  1.0002  1.0000  1.0000
        
    Mode arrondi à moins l'infini :
        Activite 1-1
        1.5000  0.8000  2.3000  0.9000
        Activite 2-1
        -106.0067       18.2857 2.7366  1.0000
        Activite 2-1
        1.0000  1.0000  1.0000  1.0000

    Mode arrondi à plus l'infini :
        Activite 1-1
        Activite 1-1
        1.5000  0.8000  2.3000  0.9000
        Activite 2-1
        -121.6167       20.8073 2.9899  1.0000
        Activite 2-1
        0.9992  1.0001  1.0000  1.0000

         */
        





/*Ex 2 Question 
    Avec la recherche partielle de pivot : 
        La descente de Gauss avec recherche partielle de pivot 
        maximum transforme un système linéaire général 
        en un système trinagulaire supérieur équivalent 
        avec des 1 sur la diagonale 
        si et seulement si la matrice du système  est inversible
        Cela permet d'obtenir les inconnues plus rapidement*/