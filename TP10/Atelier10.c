#define _USE_MATH_DEFINES
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <time.h>

double cosinus (double x){
    return cos(x);
}

double sinus (double x){
    return sin(x);
}

double exponentielle (double x){
    return exp(x);
}

double puissance_de_10 (double x){
    return pow(x,10);
}



double rectangle(double (*f)(double), double a, double b, long n){
    double res = 0.0;
    if (n==0){
        printf("Impossible, n est égal à 0");
        exit(69);
    }
    for(long i=0;i<=n-1;i++){
        res += f(a + i * ((b-a))/n);
    }

    res*= ((b-a)/n);
    return res;
}

double trapeze(double (*f)(double), double a, double b, long n){
    double aux1, x1, h;
    h = (b-a)/n;
    aux1 = 0;
    for(x1=a+h; x1 < b - h/2; x1 += h)
        aux1 += f(x1);
    return (h/2)*(f(a)+ 2*aux1 + f(b)) ;
}

double simpson(double (*f)(double), double a, double b, long n){
    double aux1, aux2, x1, x2, h, h2;
    h = (b-a)/n;
    h2 = 2*h ;
    aux1 = f(a+h);
    aux2 = 0;
    for(x1 = a + 3*h , x2 = a + h2; x1 < b; x1+= h2 , x2 += h2){
        aux1 += f(x1);
        aux2 += f(x2);
    }
    return (h/3)*(f(a)+ 4*aux1 + 2*aux2 + f(b)) ;
}

int main(){
    double a,b;
    long n;
    int k;
    printf("Veuillez choisir un nombre entier entre 4 et 10 inclus : k=");
    scanf("%d",&k);
    if ((k<4)||(k>10)){
        printf("Mauvaise entrée.\n");
        exit(31);
    }
    n = pow(2,k);
    a = 0;
    b = 1;

    double rescos, ressin, resexp, respow10, rescos2, ressin2, resexp2, respow102;
    // Test de la fonction rectangle avec intervale [0,1];
    printf("________________________________\n\nAvec fonction rectangle et k=%d : \n",k );
    time_t debut = clock();
    rescos = rectangle(&cosinus,a,b,n);
    ressin = rectangle(&sinus,a,b,n);
    resexp = rectangle(&exponentielle,a,b,n);
    respow10 = rectangle(&puissance_de_10,a,b,n);
    rescos2 = rectangle(&cosinus,a,M_PI,n);
    ressin2 = rectangle(&sinus,a,M_PI,n);
    resexp2 = rectangle(&exponentielle,a,M_PI,n);
    respow102 = rectangle(&puissance_de_10,a,M_PI,n);
    time_t fin = clock();
    time_t tps = (double)(fin - debut) *1000000/ CLOCKS_PER_SEC;
    printf("Intervalle [0,1] :\n");
    printf("%e\n%e\n%e\n%e\n",rescos,ressin,resexp,respow10);
    printf("\nIntervalle [0,π] :\n");
    printf("%e\n%e\n%e\n%e\n",rescos2,ressin2,resexp2,respow102);
    printf("Temps pris pour rectangle : %ldμs\navec %ldμs en moyenne par appel\n",tps,tps/8);
    printf("________________________________\n");


    printf("________________________________\n\nAvec fonction trapeze et k=%d : \n",k );
    debut = clock();
    rescos = trapeze(&cosinus,a,b,n);
    ressin = trapeze(&sinus,a,b,n);
    resexp = trapeze(&exponentielle,a,b,n);
    respow10 = trapeze(&puissance_de_10,a,b,n);
    rescos2 = trapeze(&cosinus,a,M_PI,n);
    ressin2 = trapeze(&sinus,a,M_PI,n);
    resexp2 = trapeze(&exponentielle,a,M_PI,n);
    respow102 = trapeze(&puissance_de_10,a,M_PI,n);
    fin = clock();
    tps = (double)(fin - debut) *1000000/ CLOCKS_PER_SEC;
    printf("Intervalle [0,1] :\n");
    printf("%e\n%e\n%e\n%e\n",rescos,ressin,resexp,respow10);
    printf("\nIntervalle [0,π] :\n");
    printf("%e\n%e\n%e\n%e\n",rescos2,ressin2,resexp2,respow102);
    printf("Temps pris pour trapeze : %ldμs\navec %ldμs en moyenne par appel\n",tps,tps/8);
    printf("________________________________\n");


    printf("________________________________\n\nAvec fonction simpson et k=%d : \n",k );
    debut = clock();
    rescos = simpson(&cosinus,a,b,n);
    ressin = simpson(&sinus,a,b,n);
    resexp = simpson(&exponentielle,a,b,n);
    respow10 = simpson(&puissance_de_10,a,b,n);
    rescos2 = simpson(&cosinus,a,M_PI,n);
    ressin2 = simpson(&sinus,a,M_PI,n);
    resexp2 = simpson(&exponentielle,a,M_PI,n);
    respow102 = simpson(&puissance_de_10,a,M_PI,n);
    fin = clock();
    tps = (double)(fin - debut) *1000000/ CLOCKS_PER_SEC;
    printf("Intervalle [0,1] :\n");
    printf("%e\n%e\n%e\n%e\n",rescos,ressin,resexp,respow10);
    printf("\nIntervalle [0,π] :\n");
    printf("%e\n%e\n%e\n%e\n",rescos2,ressin2,resexp2,respow102);
    printf("Temps pris pour simpson : %ldμs\navec %ldμs en moyenne par appel\n",tps,tps/8 );
    printf("________________________________\n");

    /* On remarque qu'en moyenne, trapeze et simpson sont plus rapides que rectangle
    */
    return 0;
}