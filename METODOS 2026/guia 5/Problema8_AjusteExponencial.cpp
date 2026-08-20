#include <iostream>
#include <math.h>
using namespace std;

#define N 12

int main(int argc, char *argv[]) {

	double t[N]     = {0, 0.5, 1, 1.5, 2.0, 2.5, 3.0, 3.5, 4.0, 4.5, 5.0, 5.5};
	double gamma[N] = {1.0, 0.994, 0.990, 0.985, 0.979, 0.977, 0.972, 0.969, 0.967, 0.960, 0.956, 0.952};

	// gamma(t) = a * e^(-b*t)
	// Linealizando: ln(gamma) = ln(a) - b*t  ==>  y = B + A*t   (con A=-b, B=ln(a))
	// Es una regresion lineal comun, pero sobre ln(gamma) en vez de gamma.

	double y[N];
	for(int i = 0; i < N; i++) y[i] = log(gamma[i]);

	double Sx=0, Sy=0, Sxy=0, Sx2=0;
	for(int i = 0; i < N; i++)
	{
		Sx  += t[i];
		Sy  += y[i];
		Sxy += t[i]*y[i];
		Sx2 += t[i]*t[i];
	}

	double pendiente = (N*Sxy - Sx*Sy) / (N*Sx2 - Sx*Sx);
	double ordenada  = (Sy - pendiente*Sx) / N;

	double b = -pendiente;
	double a = exp(ordenada);

	printf("gamma(t) = %.10lf * e^(-%.10lf * t)\n", a, b);
	printf("\na = %.10lf\n", a);
	printf("b = %.10lf\n", b);

	// Error cuadratico medio sobre los valores originales (no los linealizados)
	double suma_err2 = 0;
	for(int i = 0; i < N; i++)
	{
		double gamma_ajustado = a * exp(-b * t[i]);
		suma_err2 += pow(gamma_ajustado - gamma[i], 2);
	}
	double ECM = sqrt(suma_err2 / N);
	printf("ECM (sobre gamma original) = %.10lf\n", ECM);

	return 0;
}
