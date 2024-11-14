#include <stdio.h>
#include <stdlib.h>
#include <math.h>

double f(double x){
    return exp(x)-4;
}

double g(double x){
    return sin(x-3);
}

double h(double x){
    return (162*(pow(x,3))-18*x -3);
}

double p(double x){
    return (2*(pow(x,2)) - pow(x,3) - 2*(pow(x,4)) + pow(x,5));
}

double fprime(double x){
    return exp(x);
}

double gprime(double x){
    return cos(x-3);
}

double hprime(double x){
    return 486 *pow(x,2) - 18;
}

double pprime(double x){
    return ((4* x) - (3*pow(x,2)) - 8*(pow(x,3)) + (5*pow(x,4)));
}

int bissection(double *z, double (*f) (double), double a, double b, double eps){
    double a1, b1, m, fa1, fb1, fm;
    if (b < a){ 
        a1 = b; b1 = a;
    }
    else{ 
        a1 = a; b1 = b;
    }
    fa1 = f(a1); fb1 = f(b1);
    if (fa1*fb1 > 0) exit(0);
    do{
        m = (a1+b1)/2.0;
        fm = f(m);
        if (fa1*fm <0){ 
            b1 = m; fb1 = fm; 
        }
        else{ 
            a1 = m; fa1 = fm; 
        }
    } 
    while (fabs(b1-a1)>eps);

    *z = a1;
    return 1;
}

int newton(double *z, double (*f)(double), double (*fprime)(double), double a, double b, double eps){
    double x0;
    double x1 = (a+b)/2;

    do{
        x0 = x1;
        double fx0 = f(x0);
        double fpx0 = fprime(x0);
        if (fpx0 == 0){
            return 0;
        }
        x1 = x0 -(fx0 / fpx0);


    } while(fabs(x1-x0) > eps);
    *z = x1;
    
    return 1;
}

int findZero(double *z, double (*f)(double), double (*fprime)(double), double a, double b, double eps){
    double a1, b1, m, fa1, fb1, fm;
    if (b < a){ 
        a1 = b; b1 = a;
    }
    else{ 
        a1 = a; b1 = b;
    }
    fa1 = f(a1); fb1 = f(b1);
    if (fa1*fb1 > 0) exit(0);

    do{
        m = (a1+b1)/2.0;
        fm = f(m);
        if (fa1*fm <0){ 
            b1 = m; fb1 = fm; 
        }
        else{ 
            a1 = m; fa1 = fm; 
        }
    } 
    while (fabs((b1-a1)/a1)<0.1);

    return newton(z,f,fprime,a1,b1,eps);
}

int main(){

    printf("Avec la méthode de bissection : \n");
    // fonction 1 :
    double z;
    double a = 1;
    double b = 1.5;
    double eps = pow(10,-8);
    if (bissection(&z,&f,a,b,eps)==1)
        printf("avec la fonction f(x) = exp(x)-4   \t\t\t\t\t  : z = %lf\n",z);

    // fonction 2 

    a = -0.5;
    b = 0.5;
    if (bissection(&z,&g,a,b,eps)==1)
        printf("avec la fonction g(x) = sin(x-3)   \t\t\t\t\t  : z = %lf\n",z);

    // fonction 3

    a = -(1/3);
    b = 1;
    if (bissection(&z,&h,a,b,eps)==1)
        printf("avec la fonction h(x) = 162*(pow(x,3))-18*x -3    \t\t\t  : z = %lf\n",z);

    // fonction 4

    a = -1.5;
    b = 0.5;
    if (bissection(&z,&p,a,b,eps)==1)
        printf("avec la fonction p(x) = 2*(pow(x,2)) - pow(x,3) - 2*(pow(x,4)) + pow(x,5) : z = %lf\n\n",z);

    printf("Avec la méthode de Newton : \n");
    // fonction 1 de exo 2
    a = 1;
    b = 1.5;
    if(newton(&z,&f,&fprime,a,b,eps)){
        printf("avec la fonction f(x) = exp(x)-4   \t\t\t\t\t  : z = %lf\n",z);
    }

    // fonction 2 de exo 2
    a = -0.5;
    b = 0.5;
    if(newton(&z,&g,&gprime,a,b,eps)){
        printf("avec la fonction g(x) = sin(x-3)   \t\t\t\t\t  : z = %lf\n",z);
    }
    
    // fonction 3 de exo 2
    a = -(1/3);
    b = 1;
    if(newton(&z,&h,&hprime,a,b,eps)){
        printf("avec la fonction h(x) = 162*(pow(x,3))-18*x -3    \t\t\t  : z = %lf\n",z);
    }

    // fonction 4 de exo 2
    a = -1.5;
    b = 0.5;
    if(newton(&z,&p,&pprime,a,b,eps)){
        printf("avec la fonction p(x) = 2*(pow(x,2)) - pow(x,3) - 2*(pow(x,4)) + pow(x,5) : z = %lf\n\n",z);
    }

    printf("Avec findZero : \n");
    // fonction 1 de exo 3
    a = 1;
    b = 1.5;
    if(findZero(&z,&f,&fprime,a,b,eps)){
        printf("avec la fonction f(x) = exp(x)-4   \t\t\t\t\t  : z = %lf\n",z);
    }

    // fonction 2 de exo 3
    a = -0.5;
    b = 0.5;
    if(findZero(&z,&g,&gprime,a,b,eps)){
        printf("avec la fonction g(x) = sin(x-3)   \t\t\t\t\t  : z = %lf\n",z);
    }
    
    // fonction 3 de exo 3
    a = -(1/3);
    b = 1;
    if(findZero(&z,&h,&hprime,a,b,eps)){
        printf("avec la fonction h(x) = 162*(pow(x,3))-18*x -3    \t\t\t  : z = %lf\n",z);
    }

    // fonction 4 de exo 3
    a = -1.5;
    b = 0.5;
    if(findZero(&z,&p,&pprime,a,b,eps)){
        printf("avec la fonction p(x) = 2*(pow(x,2)) - pow(x,3) - 2*(pow(x,4)) + pow(x,5) : z = %lf\n\n",z);
    }
}