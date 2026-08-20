#include <iostream>
#include <math.h>
using namespace std;

#define N 7   // cantidad de puntos

int main(int argc, char *argv[]) {

	double h[N]   = {0, 1.525, 3.050, 4.575, 6.10, 7.625, 9.150};
	double rho[N] = {1, 0.8617, 0.7385, 0.6292, 0.5328, 0.4481, 0.3741};

	// Ajuste f(x) = A*x^2 + B*x + C  (Problema 5: sistema de ecuaciones normales 3x3)
	// [ sum(x^4)  sum(x^3)  sum(x^2) ] [A]   [ sum(x^2*y) ]
	// [ sum(x^3)  sum(x^2)  sum(x)   ] [B] = [ sum(x*y)   ]
	// [ sum(x^2)  sum(x)    N        ] [C]   [ sum(y)     ]

	double Sx=0, Sx2=0, Sx3=0, Sx4=0, Sy=0, Sxy=0, Sx2y=0;
	for(int i = 0; i < N; i++)
	{
		double xi = h[i], yi = rho[i];
		Sx   += xi;
		Sx2  += xi*xi;
		Sx3  += xi*xi*xi;
		Sx4  += xi*xi*xi*xi;
		Sy   += yi;
		Sxy  += xi*yi;
		Sx2y += xi*xi*yi;
	}

	// Resolver el sistema 3x3 por eliminacion Gaussiana simple
	double M[3][4] = {
		{Sx4, Sx3, Sx2, Sx2y},
		{Sx3, Sx2, Sx,  Sxy},
		{Sx2, Sx,  (double)N, Sy}
	};

	for(int i = 0; i < 3; i++)
	{
		double piv = M[i][i];
		for(int j = i+1; j < 3; j++)
		{
			double factor = M[j][i]/piv;
			for(int k = i; k < 4; k++) M[j][k] -= factor*M[i][k];
		}
	}
	double C_coef[3];
	for(int i = 2; i >= 0; i--)
	{
		double suma = M[i][3];
		for(int j = i+1; j < 3; j++) suma -= M[i][j]*C_coef[j];
		C_coef[i] = suma / M[i][i];
	}
	double A = C_coef[0], B = C_coef[1], C = C_coef[2];

	printf("f(x) = %.10lf*x^2 + %.10lf*x + %.10lf\n", A, B, C);

	double suma_err2 = 0;
	for(int i = 0; i < N; i++)
	{
		double fi = A*h[i]*h[i] + B*h[i] + C;
		suma_err2 += pow(fi - rho[i], 2);
	}
	double ECM = sqrt(suma_err2/N);
	printf("ECM = %.10lf\n", ECM);

	double h_eval = 10.5;
	double rho_eval = A*h_eval*h_eval + B*h_eval + C;
	printf("\nDensidad relativa estimada a h=%.1f km: %.6lf\n", h_eval, rho_eval);

	return 0;
}
