#include <stdio.h>
#include <math.h>

void readData(FILE *fp, int *length, double arr[]);
double cumSum(double arr[], int length);
void safeValue(double sigma);
void safeSinTable(int length, FILE *fp);
int dataset1();
int dataset2();

int main()
{
    dataset1();
        
    dataset2();

    printf("\n in feature branch");
}

int dataset1()
{
  // open file and check if success
   FILE *fp = fopen("dataset1_", "r");
    
   if (fp != NULL)
   {
        printf("file opened successfully\n");
   } 
   else
   {
        printf("file could not be opened\n");
        return 0;
   }

    int length;
    double arr[1000];

    readData(fp, &length, arr);

    double sigma = cumSum(arr, length);
    safeValue(sigma);
  
    fclose(fp);
}

int dataset2()
{
    FILE *fp = fopen("dataset2_", "rb");
    
   if (fp != NULL)
   {
        printf("file opened successfully\n");
   } 
   else
   {
        printf("file could not be opened\n");
        return 0;
   }

    int length;
    fread(&length, sizeof(int), 1, fp);

    safeSinTable(length, fp);

   fclose(fp);
}

void readData(FILE *fp, int *length, double arr[])
{
    fscanf(fp, "%i", length);

    for (int i = 0; i<1000; i++)
    {
        fscanf(fp, "%lf", arr + i);
        printf("%f  %i\n", arr[i], i);
    }
}

double cumSum(double arr[], int length)
{
    double sigma = 0;
    for (int i = 0; i < length; i++)
    {
        sigma += arr[i]*arr[i];
    }

    return sigma;
}

void safeValue( double sigma)
{
    FILE * wp = fopen("quadratsumme.txt", "w");
    fprintf(wp, "Die kumulative Quadratsumme vom dataset1 ist s = %f", sigma);

    fclose(wp);
}

void safeSinTable(int length, FILE *fp)
{
    FILE * wp = fopen("tabelle.txt", "w");

    for (int i = 0; i< length; i++)
    {
        double val;
        fread(&val, sizeof(double), 1, fp);
        fprintf(wp, "%f   %f\n", val, sin(val));
    }

    fclose(wp);
}



