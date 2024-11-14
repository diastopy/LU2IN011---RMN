#include <stdio.h>  
#include <stdlib.h>
#include <math.h>

int bitcommun (double x,double y){

    return -log2(fabs((2*(x-y))/(x+y)));
}

void horner(double x0, double a, double epsilon){
    double xn = x0;
    double xn1 = (((4*xn - 3*a +2)* xn - a)* xn - 2*a)/((5*xn - 4*a +3)* xn - 2*a -2);
    int cpt = 0;

    printf("X%d = %.15lf\n",cpt,xn);
    printf("Nombre de bits en coommun entre X%d et X%d : %d\n\n",cpt,cpt+1,bitcommun(xn,xn1));
    while (fabs(xn1 - xn)>epsilon){
        xn = xn1;
        xn1 = (((4*xn - 3*a +2)* xn - a)* xn - 2*a)/((5*xn - 4*a +3)* xn - 2*a -2);
        cpt++;
        printf("X%d = %.15lf\n",cpt, xn);
        printf("Nombre de bits en coommun entre X%d et X%d : %d\n\n",cpt,cpt+1,bitcommun(xn,xn1));
    }
    printf("X%d = %.15lf\n\n\n",cpt+1, xn1);
}

int main(){
    printf ("Cas test avec X0 = 2.0, a = 0.3, epsilon = 10⁻3\n");
    horner(2,0.3,0.001);
    printf ("Premier cas avec X0 = 2.0, a = 0.3, epsilon = 10⁻14\n");
    horner(2,0.3,0.00000000000001);
    printf ("Deuxième cas avec X0 = 5.0, a = 3.5, epsilon = 10⁻14\n");
    horner(5,3.5,0.00000000000001);
    printf ("Troisième cas avec X0 = 0.5, a = 3.5, epsilon = 10⁻14\n");
    horner(0.5,3.5,0.00000000000001);
    printf ("Quatrième cas avec X0 = -3.0, a = 1.0, epsilon = 10⁻14\n");
    horner(-3.0,1.0,0.00000000000001);
    printf ("Cinquième cas avec X0 = 2, a = 1.0, epsilon = 10⁻14\n");
    horner(2.0,1.0,.00000000000001);
}

/*  Le premier cas, avec x0 = 2, α = 0.3, ε = 10 −14, 
        est LINEAIRE, le nombre de bits en commun augmente de manière minime et,
        de 1 en 1 ou de 1 en 0 selon les tours de boucle. 
        Converge vers 1

    Le deuxième cas, avec x0 = 5, α = 3.5, ε = 10 −14,
        est EXPONENTIEL, le nombre de bit en commun augmente de manière linéaire entre X0 et X3, 
        puis de manière exponentiellen notamment entre X6 et X7 avec 28 puis X7 et X8 avec 50 (22 bits d'écart entre 2 comparaisons)
        Converge vers 3.5 (a)

    Le troisième cas, avec x0 = 0.5, α = 3.5, ε = 10 −14,
        est LINEAIRE, le nombre de bits en commun augmente de manière minime et,
        de 1 en 1 ou de 1 en 0 selon les tours de boucle. 
        Converge 1 

    Le quatrième cas, avec x 0 = −3.0, α = 1.0, ε = 10 −14, 
        est LINEAIRE, le nombre de bits en commun augmente de manière minime et,
        de 1 en 1 ou de 1 en 0 selon les tours de boucle. 
        Converge vers -2

    Le cinquième cas, avec x 0 = 2.0, α = 1.0, ε = 10 −14,
        est LINEAIRE, le nombre de bits en commun augmente de manière minime et,
        de 1 en 1 ou de 1 en 0 selon les tours de boucle. 
        Converge vers 1


    Etude théorique :
        Les points fixes sont x = -2 pour tout a != -2, x = 1 pour tout a != 1 et  x = a pour tout a^2 + a != 2
        On voit notamment que 3 cas d'appel à horner convergent vers 1, 1 converge vers -2 et 1, converge vers a (3,5)

*/