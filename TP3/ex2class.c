int main(void)
{
    double start,stop;
    start=clock();

    int n;
    printf("Rentrer la dimension de votre matrice. \n");
    scanf("%d",&n);

    printf("Matrice A\n");
    double a[n][n];
    for(int i = 0; i<n; i++)
    {
        for(int j = 0; j<n; j++)
        {
        a[i][j] = (rand()%(3)-1);
        //printf("%.2f ",a[i][j]);
        }
    }
    printf("\n");

    double *b = (double*)malloc((sizeof(double))*n*n);
    printf("Matrice B\n");
    //double b[n][n];
    for(int g = 0; g<n; g++)
    {
        for(int k = 0; k<n; k++)
        {
        b[g*n+k] = (rand()%(3)-1);
       //printf("%.2f ",b[g*n+k]);
        }

    }
    printf("\n");

    //double p[n*n];
    stop=clock();
    double k;
    k= (stop-start)/1000 ;
    printf("Le temps d'exucution est T=%.3f. \n",k);
}

/*{

    double start,stop;
    start=clock();
    
    int n;
    printf("Rentrer la dimension de votre matrice.\n");
    scanf("%d",&n);

    //printf("Matrice A\n");
    //double *a = malloc((sizeof(double))*n*n);
    double a[n*n];
    for(int i = 0; i<n;i++)
    {
        for(int j = 0; j<n;j++)
        {
            *(a+i*n+j) = (rand()%(3)-1);
   //         printf("%.1f ",*(a+i*n+j));

        }printf("\n");
    }
    printf("\n");

    //double *b = malloc((sizeof(double))*n*n);
    double b[n*n];
    for(int k = 0; k<n;k++)
    {
        for(int l = 0; l<n;l++)
        {
            *(b+k*n+l) = (rand()%(3)-1);
   //         printf("%.1f ",*(b+k*n+l));

        }printf("\n");
    }
    int x;
    double f[n*n];
    for(int z = 0;z<n;z++){
        for(int y = 0;y<n;y++){
            x = z*n + y;
            *(f+x) = 0;
            for(int k = 0;k<n;k++){
                *(f+x) += *(a+z*n+k) * *(b+k*n+y);
                printf("%.1f",*f+k*n+1);
            }
        }
    }

    /*double *p*n;
    p = malloc((sizeof(double))*n);
    free(p);

    //printf("\n");
    stop=clock();
    double k;
    k= (stop-start)/1000 ;
    printf("Le temps d'exucution est T=%f. \n",k);

    return 0;
}*/