#include <stdio.h>
#include <math.h>


void afficheRacines(double a, double b, double c){
	double d = (b*b)-(4*a*c);
	if (d<0){
	printf("Pas de racine reelle\n");
	}
	else if (d>0) {
	double res1=(-b-sqrt(d))/(2.0*a);
	double res2=(-b+sqrt(d))/(2.0*a);
	printf("Les deux racines sont %lf et %lf\n", res2,res1);
	}
	else {
	double res=-b/(2.0*a);
	printf("La racine double est %lf\n",res);
	}
}

int main() {
  double a,b,c;
  
  scanf("%lf",&a);
  scanf("%lf",&b);
  scanf("%lf",&c);
 
  printf("Racines de %lf*x*x + %lf*x + %lf\n",a,b,c);
  afficheRacines(a,b,c);
 
  
  return 0;
}