#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>

void calcul(int tab[], int n, int * j){
	int i=0;
	if (n==0){
		tab[i]=0;
		*j=1;
	}
	else{
		for (i=0;n>0;i++){
			if (n%2==0){
				tab[i]=0;
				n=n/2;
			}
			else{
				tab[i]=1;
				n=n/2;
			}
			*j=i+1;
		}
		if (n==0){
			tab[i]=0;
		}
		else{
			tab[i]=1;
		}
	}
}
	

int main(){
	int n=0;
	int i;
	scanf("%d",&n);
	int tab[32];
	int j=32;
	calcul(tab,n, &j);
	for(i=j-1;i>=0;i--){
	printf("%d",tab[i]);
	}
	printf("\n\n");
	return 0;
}
	 
