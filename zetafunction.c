#include<stdio.h>

double pow(double x, int e)
{
    double res = x;

    for (int i = 1; i < e; i++) res *= x;

    return res;
}

double zetadouble(double s, int k)
{
    double zeta = 0.0;

    for (int i = 1; i <= k; i++) zeta += 1.0/pow(s, i);
    
    return zeta;
}

float zetafloat(float s, int k )
{
    float zeta = 0.0f;

    for (int i = 1; i <= k; i++) zeta += 1.0/pow(s, i);

    return zeta;
}

int main()
{
    double x;
    int k;
    printf("Eingabe (s und k): \n");
    scanf("%lf %i", &x, &k);
    printf("x: %f   k = %i\n", x, k);

    printf("Ausgabe in double: %.20f\n", zetadouble(x, k));
    printf("Ausgabe in float (double Eingabe): %.20f\n", zetadouble((float) x, k));
    printf("Ausgabe in float: %.20f\n", zetafloat(x, k));
}

