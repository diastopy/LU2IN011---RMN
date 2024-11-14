#include <stdlib.h>
#include <stdio.h>
#define TAILLE 5

// Inverse toute forme de matrice
void invmat(float *a, int n){
    float AX;
    int i,j,k;
    for(i=0;i<n;i++){
        AX = *(a + n*i +i);
        for(j=0;j<n;j++)
            *(a + n*i + j) /= AX;
        *(a + n*i +i) = 1.0/AX;
        for(k=0;k<n;k++)
        if (k!=i){
            AX = *(a +n*k + i);
            for(j=0;j<n;j++)
                *(a +n*k + j) -= AX* *(a +n*i + j);
            *(a +n*k + i) = - AX* *(a +n*i + i);
        }
    }
}

// Inverse une matrice triangulaire inférieure
void invlinf(float *a, int n){
    float AX;
    int i,j,k;
    for(i=0;i<n;i++){
        AX = *(a + n*i +i);
        for(j=0;j<=i;j++)
            *(a + n*i + j) /= AX;
        *(a + n*i +i) = 1.0/AX;
        for(k=0;k<n;k++)
        if (k!=i){
            AX = *(a +n*k + i);
            for(j=0;j<n;j++)
                *(a +n*k + j) -= AX* *(a +n*i + j);
            if (i<=j)
                *(a +n*k + i) = - AX* *(a +n*i + i);
        }
    }
}

// Inverse une matrice triangulaire supérieure
void invusup(float *a, int n){
    float AX;
    int i,j,k;
    for(i=0;i<n;i++){
        for(k=0;k<n;k++)
        if (k<i){
            AX = *(a +n*k + i);
            for(j=0;j<n;j++)
                *(a +n*k + j) -= AX* *(a +n*i + j);
            *(a +n*k + i) = - AX* *(a +n*i + i);
        }
    }
}

// Décompose la matrice A
void decomplu(float *a, int n){
    int i,j,k;
    float aux, aux2;
    for(i=0;i<n-1;i++){
        aux = *(a + i*n + i);
        for(k=i+1; k<n; k++)
        *(a + i*n + k) /= aux;
        for(k=i+1;k<n;k++){
            aux2 = *(a + k*n + i);
            for(j=i+1;j<n;j++)
                *(a + k*n + j) -= aux2 * *(a + i*n + j);
        }
    }
}

// Crée les matrices triangulaires L et U à partir de la matrice A décomposée
void triangle(float *L, float *U, float *A, int n){

    // Création de la matrice L 
    for(int i = 0; i<n; i++){
        for(int j=0; j<=i; j++){
            *(L+ n*i + j)= *(A + n*i +j);
        }
    }

    // Création de la matrice U 
    for(int i = 0; i<n; i++){
        for(int j=i; j<n; j++){
            if (i==j){
                *(U+ n*i + j) = 1;
            }
            else{
                *(U+ n*i + j) = *(A + n*i +j);
            }
        }
    }
}

// Crée une matrice M, produit de deux matrices A et B
void prodmatmat(float *a,float *b,float *m,int n){
    int x;
    for(int i = 0;i<n;i++){
        for(int j = 0;j<n;j++){
            x = i*n + j;
            *(m+x) = 0;
            for(int k = 0;k<n;k++){
                *(m+x) += *(a+i*n+k) * *(b+k*n+j);
            }
        }
    }
}

// Sert à afficher une matrice
void affiche(float *m,int n){
    printf("|---------------------------------------|\n"); 
    for (int i=0;i<n;i++){
        printf("|");
        for(int j=0;j<n;j++){
            printf("%.3f\t",*(m+n*i+j));
        }
        printf("|");
        printf(" \n");
    }
    printf("|---------------------------------------|\n\n");
}

int main(){

    printf("\n");
    //Déclaration et initialisation des matrices
    float A [TAILLE*TAILLE] =   {1,1,1,1,1,
                                1,0,0,0,0,
                                1,-1,1,-1,1,
                                1,-2,4,-8,16,
                                1,-3,9,-27,81};
    float B [TAILLE*TAILLE] =   {1,1,1,1,1,
                                1,0,0,0,0,
                                1,-1,1,-1,1,
                                1,-2,4,-8,16,
                                1,-3,9,-27,81};
    float L [TAILLE*TAILLE] = {0};
    float U [TAILLE*TAILLE] = {0};
    float M [TAILLE*TAILLE] = {0};
    float N [TAILLE*TAILLE] = {0};

    //Test décomposition de A = L*U :
    decomplu(A,5);
    printf("Affichage decomposition de A\n");
    affiche(A,5);

    //Test fonction triangle :
    triangle(L,U,A,TAILLE);
    printf("Affichage matrice L\n");
    affiche(L,TAILLE);
    printf("Affichage matrice U\n");
    affiche(U,TAILLE);

    //Test recomposition de la matrice A à partir de L et U      : 
    prodmatmat(L,U,M,TAILLE);
    printf("Affichage recomposition matrice A par produit de U et L\n");
    affiche(M,TAILLE);

    //Test d'inversion des matrices L et U avec les fonctions spécifiques : 
    invusup(U,TAILLE);
    invlinf(L,TAILLE);
    printf("Affichage matrice L^-1\n");
    affiche(L,TAILLE);
    printf("Affichage matrice U^-1\n");
    affiche(U,TAILLE); 

    // Test du produit des matrices inverses L et U, et comparaison avec l'inversion de B : 
    // Création de la matrice inverse à partir des matrices triangulaires inverses
    prodmatmat(U,L,N,TAILLE);
    // Inversion de la matrice B (Initiliasée comme la matrice A, mais non modifiée pendant toute la durée du programme)
    invmat(B,TAILLE);
    printf("Affichage matrice N(matrice inverse à partir de L^-1 et U^-1)\n");
    affiche(N,TAILLE); 
    printf("Affichage matrice B^-1\n");
    affiche(B,TAILLE); 

}