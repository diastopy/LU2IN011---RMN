#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>

uint32_t pgcd(uint32_t A, uint32_t B, uint32_t * u, uint32_t * v, uint32_t * res){
	uint32_t u1=1,u2=0,u3=A,v1=0,v2=1,v3=B,t1,t2,t3;
	uint32_t q;
	while(v3!=0){
	    q= u3/v3;
		t1=u1-q*v1;
		u1=v1;
		v1=t1;
		t2=u2-q*v2;
		u2=v2;
		v2=t2;
		t3=u3-q*v3;
		u3=v3;
		v3=t3;
	}
	*u=u1;
	*v=u2;
	*res=u3;
	return u3;
}

int main(){
	uint32_t A,B;
	uint32_t u,v,res;
	scanf("%d",&A);
	scanf("%d",&B);
	pgcd(A,B,&u,&v,&res);
	printf("le premier coefficient est %d,\n le deuxième coefficient est %d,\n le résultat est pgcd(A,B)=%d\n\n",u,v,res);
	return 0;
}
	
