#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <time.h>

void eval_Horner_1(double a, double *coeff_f, int n, double *f_a){
    double y = coeff_f[n];
    for(int i = n-1; i>= 0; i--){
        y = y * a + coeff_f[i];
    }
    *f_a = y;
}

void eval_Horner_2(double a,double* coeff_f,int n,double* f_a,double* f_minus_a){
    double yi, yp, x2;
    int i;
    x2 = a*a;
    if (n%2 != 0){ 
        yi = coeff_f[n]; yp = coeff_f[n-1]; i = n-2; 
    }
    else{ 
        yi = 0; yp = coeff_f[n]; i = n-1;
    }
    for(; i >= 0; i -= 2){
        yi = yi*x2 + coeff_f[i];
        yp = yp*x2 + coeff_f[i-1];
    }
    *f_a = yp + a*yi;
    *f_minus_a = yp - a*yi;
}

void gauss(double *a, double *b, int n){
    int i,j,k;
    double X1, X2;
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

void interpol_linalg(double* a, double* f_a, int n, double* coeff_f){
    double c[n * n];
    for (int i = 0; i<n; i++){
        *(c + i * n) = 1;
        coeff_f[i] = f_a[i];
        for (int j = 1; j<n; j++){
            *(c+i * n+j) = *(c+i * n+j -1) * a[i];
        }
    }
    gauss(c,coeff_f,n);
}

double s(double* t, int iF, int num) {
  double res = 0;
  for (int i = 0; i < num; i++) {
    res += t[iF - i];
  }
  return res;
}

void interpol_Lagrange(double* a, double* f_a, int n, double* coeff_f) {
  double l[n][n];
  double c;
  double d[n];
  double t[n], tt[n];
  int ti = 0;
  for (int i = 0; i < n; i++) {
    c = f_a[i];
    d[0] = 1;
    ti = 0;
    for (int j = 0; j < n; j++) {
      if (i != j) {
        c /= (a[i] - a[j]);
        t[ti] = -a[j];
        tt[ti] = -a[j];
        ti++;
      }
    }
    d[1] = s(t, n - 2, n - 1);
    for (int k = 2; k < n; k++) {
      d[k] = 0;
      for (int l = 0; l < n - k; l++) {
        tt[l] = t[l] * s(tt, n - k, n - k - l);

        d[k] += tt[l];
      }
    }
    for (int m = 0; m < n; m++) {
      l[i][n - m - 1] = d[m] * c;
      // printf("l[%d][%d] = %f,d[%d]=%f,c=%f\n", i, n - m - 1, l[i][n - m - 1],m,d[m], c);
    }
  }
  for (int i = 0; i < n; i++) {
    coeff_f[n - i - 1] = 0;
    for (int j = 0; j < n; j++) {
      coeff_f[n - i - 1] += l[j][n - i - 1];
    }
  }
}

int main(){    
    srand((double)time(NULL));
    int f;
    printf("Choisissez un nombre entre 0 et 16 : ");
    scanf("%d",&f);
    if ((f > 16) || (f < 0)){
        printf("La valeur choisie  est incorrecte\n");
        return -1;
    }
    int taille = pow(2,f);
    double atab[taille];
    double f_atab[taille];
    double coeff_f[taille];
    for(int i=0; i<taille; i++){
        atab[i] = ((double)rand()) / (double)RAND_MAX * 2.0 - 1.0;
        f_atab[i] = ((double)rand()) / (double)RAND_MAX * 2.0 - 1.0;
        coeff_f[i] = f_atab[i];
    }

    
    time_t debut = clock();
    interpol_linalg(atab, f_atab, taille, coeff_f);
    //for(int i =0; i<taille; i++){
    //    printf("%e\n",coeff_f[i]);
    //}
    time_t fin = clock();
    time_t tps = (double)(fin - debut) *1000/ CLOCKS_PER_SEC;
    printf("Temps pour interpole_linalg : %ldms\n",tps);


    debut = clock();
    interpol_Lagrange(atab, f_atab, taille, coeff_f);
    //for(int i =0; i<taille; i++){
    //    printf("%e\n",coeff_f[i]);
    //}
    fin = clock();
    tps = (double)(fin - debut) *1000/ CLOCKS_PER_SEC;
    printf("Temps pour interpole_lagrange : %ldms\n",tps);

    return 0;
}