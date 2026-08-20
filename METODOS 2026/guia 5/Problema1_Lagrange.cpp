#include <iostream>
#include <math.h>
using namespace std;

#define N 2   // grado del polinomio (2 = cuadratico, 3 nodos)

double f(double x);
double C(int k, double x_prima, double x[N+1]);
double Pn(double x_prima, double x[N+1], double y[N+1]);

int main(int argc, char *argv[]) {

	double x[N+1] = {1, 2, 2.5};   // nodos x0, x1, x2
	double y[N+1];
	for(int i = 0; i <= N; i++) y[i] = f(x[i]);

	double puntos[2] = {1.5, 1.2};

	for(int p = 0; p < 2; p++)
	{
		double xp = puntos[p];
		printf("\n--- x' = %.2lf ---\n", xp);

		double suma_C = 0;
		for(int k = 0; k <= N; k++)
		{
			double Ck = C(k, xp, x);
			suma_C += Ck;
			printf("C_%d,%d(%.2lf) = %.6lf\n", N, k, xp, Ck);
		}
		printf("Suma de coeficientes (debe dar 1): %.6lf\n", suma_C);

		double resultado = Pn(xp, x, y);
		double exacto = f(xp);
		printf("P_N(x') = %.6lf\n", resultado);
		printf("f(x')   = %.6lf\n", exacto);
		printf("Error   = %.6lf\n", fabs(exacto - resultado));
	}

	// Verificacion extra: C_k(x_k) debe ser 1, C_k(x_j) debe ser 0 para j!=k
	printf("\n--- Verificacion C_k(x_j) ---\n");
	for(int k = 0; k <= N; k++)
	{
		for(int j = 0; j <= N; j++)
		{
			printf("C_%d(x_%d) = %.6lf\t", k, j, C(k, x[j], x));
		}
		printf("\n");
	}

	return 0;
}

// Problema 1: f(x) = x + 2/x
double f(double x)
{
	return x + 2.0/x;
}

// Coeficiente de Lagrange C_{N,k}(x)
double C(int k, double x_prima, double x[N+1])
{
	double productoria = 1;
	for(int i = 0; i <= N; i++)
	{
		if(i != k)
		{
			productoria *= (x_prima - x[i]) / (x[k] - x[i]);
		}
	}
	return productoria;
}

// Polinomio de Lagrange completo
double Pn(double x_prima, double x[N+1], double y[N+1])
{
	double sumatoria = 0;
	for(int k = 0; k <= N; k++)
	{
		sumatoria += y[k] * C(k, x_prima, x);
	}
	return sumatoria;
}
