#include <iostream>
#include <math.h>
using namespace std;

// ============================================================
// Programa GENERAL de interpolacion de Lagrange de grado n
// (interpola n+1 puntos arbitrarios (x[i], y[i]))
// ============================================================
double Lagrange(double x_prima, double x[], double y[], int n)
{
	double sumatoria = 0;
	for(int k = 0; k <= n; k++)
	{
		double productoria = 1;
		for(int i = 0; i <= n; i++)
		{
			if(i != k)
			{
				productoria *= (x_prima - x[i]) / (x[k] - x[i]);
			}
		}
		sumatoria += y[k] * productoria;
	}
	return sumatoria;
}

double f1(double x) { return exp(-x*x); }
double f2(double x) { return 4*pow(x,3) - 3*pow(x,2) + 2; }
double f3(double x) { return pow(x, x); }

int main(int argc, char *argv[]) {

	// ------------------------------------------------------------
	// Funcion 1: f(x) = e^(-x^2), polinomios pares n=2,4,6,8
	// nodos simetricos alrededor de 0
	// ------------------------------------------------------------
	printf("=== Funcion 1: f(x) = e^(-x^2) ===\n");
	double xp1 = 0.5;   // punto de evaluacion, dentro del rango
	for(int n = 2; n <= 8; n += 2)
	{
		double x[20], y[20];
		for(int i = 0; i <= n; i++)
		{
			x[i] = -n/2.0 + i;
			y[i] = f1(x[i]);
		}
		double P = Lagrange(xp1, x, y, n);
		printf("n=%d: nodos en [%.1f, %.1f]  P(%.2f)=%.6f  exacto=%.6f  error=%.6f\n",
			n, x[0], x[n], xp1, P, f1(xp1), fabs(f1(xp1)-P));
	}
	// Extrapolacion (fuera del rango de nodos, n=8: rango es [-4,4])
	double xfuera1 = 5.0;
	{
		double x[9], y[9];
		for(int i = 0; i <= 8; i++) { x[i] = -4.0 + i; y[i] = f1(x[i]); }
		double P = Lagrange(xfuera1, x, y, 8);
		printf("Extrapolacion (n=8) en x=%.1f (fuera de [-4,4]): P=%.4f  exacto=%.6f  -> ¡disparatado!\n",
			xfuera1, P, f1(xfuera1));
	}

	// ------------------------------------------------------------
	// Funcion 2: f(x) = 4x^3 - 3x^2 + 2, ordenes n=1,2,3
	// nodos 0,1,2,...,n
	// ------------------------------------------------------------
	printf("\n=== Funcion 2: f(x) = 4x^3 - 3x^2 + 2 ===\n");
	for(int n = 1; n <= 3; n++)
	{
		double x[10], y[10];
		for(int i = 0; i <= n; i++) { x[i] = i; y[i] = f2(x[i]); }

		double xp_dentro = n / 2.0;
		double xp_fuera = n + 1.5;

		double P_dentro = Lagrange(xp_dentro, x, y, n);
		double P_fuera  = Lagrange(xp_fuera, x, y, n);

		printf("n=%d: dentro x=%.2f  P=%.4f  exacto=%.4f  error=%.6f\n",
			n, xp_dentro, P_dentro, f2(xp_dentro), fabs(f2(xp_dentro)-P_dentro));
		printf("      fuera  x=%.2f  P=%.4f  exacto=%.4f  error=%.6f\n",
			xp_fuera, P_fuera, f2(xp_fuera), fabs(f2(xp_fuera)-P_fuera));
	}
	printf("Nota: con n=3 (grado 3, igual al grado real de f2) el polinomio\n");
	printf("interpolador COINCIDE EXACTO con f2, dentro y fuera del rango,\n");
	printf("porque f2 ya es un polinomio de grado 3.\n");

	// ------------------------------------------------------------
	// Funcion 3: f(x) = x^x (dominio x>0), varios ordenes
	// ------------------------------------------------------------
	printf("\n=== Funcion 3: f(x) = x^x ===\n");
	for(int n = 1; n <= 3; n++)
	{
		double x[10], y[10];
		for(int i = 0; i <= n; i++) { x[i] = 0.5 + i; y[i] = f3(x[i]); }

		double xp = x[0] + (x[n]-x[0])/2;   // punto medio del rango, dentro
		double P = Lagrange(xp, x, y, n);

		printf("n=%d: nodos desde %.1f hasta %.1f  P(%.2f)=%.4f  exacto=%.4f  error=%.6f\n",
			n, x[0], x[n], xp, P, f3(xp), fabs(f3(xp)-P));
	}

	printf("\nConclusion general: fuera del rango de interpolacion [x0,xN],\n");
	printf("el polinomio de Lagrange NO es confiable para extrapolar; el\n");
	printf("error puede crecer enormemente (ver Funcion 1 y 2, caso 'fuera').\n");

	return 0;
}
