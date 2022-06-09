#include <stdio.h>
#include <time.h>
#include <math.h> 
#include <stdlib.h>

double Funkcija (double x) {
    return (asinh(pow(x, 1.5) + sin(pow(x,2/3)) + cos(3*x) + 1/3))/(pow(x, 5) + 1);
}

double Integral (double *vi, int n,  double a, double b) {
    double vsota = 0;
    double vsota2 = 0;

    srand(time(NULL)); //Inicializacija faktorja naključnih števil.
    for (int i = 0; i < n; i++) {
        double u = (double)rand() / (double)(RAND_MAX + 1);
        double x = a + (b - a) * u;
        vsota += Funkcija(x);
        vsota2 += pow(Funkcija(x), 2);
    }
    
    *vi = (vsota * (b - a)) / n;
    vsota /= n;
    vsota2 /= n;

    return (b - a) * sqrt((vsota2 - pow(vsota, 2)) / n);
}

int main(void) {

    double a = 0;
    double b = 4; 
    double v = 0;
    double *vi = &v;
    int n = 2;

    FILE *kazalec_na_datoteko = fopen("Datoteka.csv", "w");

    fprintf(kazalec_na_datoteko, "poskusi; vrednost; napaka\n");

    for(int i = 0; i < 16; i++) {
        double sn = Integral(vi, n, a, b);
        fprintf(kazalec_na_datoteko, "%d; %lf; %lf;\n", n, *vi, sn);
        n *= 2;
    }

    fclose(kazalec_na_datoteko);

    return 0;
}