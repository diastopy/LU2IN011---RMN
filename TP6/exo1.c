#include <stdlib.h>
#include <stdio.h>

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

int main(){
    float a[3*3]={2,3,-1,4,4,-3,-2,3,-1};
    invmat(a,3);
    for(int i=0;i<3;i++){
        for(int j=0;j<3;j++){
            printf("%.3f ", *(a + 3*i +j));
        }
        printf("\n");
    }
}