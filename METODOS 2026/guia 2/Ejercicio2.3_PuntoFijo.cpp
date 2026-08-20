#include <iostream>
#include <math.h>

using namespace std;

void encontrar_raiz(double x_viejo);
double g(double x);
double gprima(double x);

int main(int argc, char *argv[]) {
	double x_viejo = 0.9;   // OJO: con x0=0 la funcion es 0^(-1) (indeterminado) y diverge.
	                        // Cualquier x0 entre 0.5 y 1.5 (menos 0 y 1 exactos) converge a raiz=1.

	encontrar_raiz(x_viejo);
	return 0;
}

void encontrar_raiz(double x_viejo)
{
	double x_nuevo = 0, tolerancia = 0, error_viejo = 1e9, error_nuevo = 1e9;
	int iteracion = 0, exponente = 0;

	printf("Ingrese el exponente para la tolerancia: ");
	scanf("%d", &exponente);
	tolerancia = pow(10, -exponente);

	while((error_nuevo > tolerancia) && (iteracion < 10000))
	{
		iteracion++;
		x_nuevo = g(x_viejo);
		error_nuevo = fabs(x_nuevo - x_viejo);

		if(isnan(x_nuevo) || isinf(x_nuevo))
		{
			printf("La funcion no converge (nan/inf) - revisar x0");
			exit(1);
		}
		if(error_nuevo > error_viejo)
		{
			printf("Se aleja de la raiz, no converge (probar otro x0)");
			exit(1);
		}
		if(fabs(gprima(x_nuevo)) >= 1)
		{
			printf("|g'(x)| >= 1 cerca de la raiz, el punto fijo no converge aca");
			exit(1);
		}
		error_viejo = error_nuevo;
		x_viejo = x_nuevo;
	}

	printf("El error es: %0.15f\nCant de iteraciones: %d\nRaiz: %.12f", error_nuevo, iteracion, x_nuevo);
}

// Problema 2, funcion 3: g(n) = n^(n - cos(n))
double g(double x)
{
	return pow(x, x - cos(x));
}

// Derivada numerica (mas segura que la formula analitica con logaritmos)
double gprima(double x)
{
	double h = 1e-6;
	return (g(x + h) - g(x - h)) / (2*h);
}
