#include <stdio.h>
#include <stdlib.h>

int conversion(int tab[]){
  
  int tab[10], nbr, i;  
  
  printf("Entrez le nombre à convertir: ");  
  scanf("%d",&nbr);  
  
  for(i=0; nbr > 0; i++)  
  {  
    tab[i] = nbr%2;  
    nbr = nbr/2;  
  } 
  
  printf("\nLe nombre binaire est = ");
  
  for(i=i-1; i >= 0; i--)  
  {  
    printf("%d",tab[i]);  
  }  
  
  return 0;
}
void gauss_sp(float *a, float *b, int n){
    int i,j,k;
    float aux, aux2;
    for(i=0;i<n-1;i++){
        aux = *(a + i*n + i);
        for(k=i+1; k<n; k++)
            *(a + i*n + k) /= aux;
        *(b + i) /= aux;
        for(k=i+1;k<n;k++){
            aux2 = *(a + k*n + i);
            for(j=i+1;j<n;j++)
                *(a + k*n + j) -= aux2 * *(a + i*n + j);
            *(b + k) -= aux2 * *(b+i);
        }
    }
    *(b + n-1) /= *(a + n*n -1);
    for(i=n-2;i>=0;i--){
        aux= *(b + i);
        for(k=i+1;k<n;k++)
            aux -= *(a + i*n + k) * *(b + k);
        *(b + i) = aux;
    }
}

int main(){
    float mA[16] = {2.5,1.5,1.7,2.5,
                    1.7,1.8,2.2,1.8,
                    2.0,1.2,2.5,3.0,
                    2.1,1.2,2.2,1.5};
    float mB[4] = {11.11,10.67,12.41,10.52};
    gauss_sp(mA,mB,4);
    for(int i=0;i<4;i++){
        printf("%f\t",mB[i]);
    }
}