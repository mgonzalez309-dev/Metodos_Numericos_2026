#include <iostream>
#include <math.h>

using namespace std;

void encontrar_raiz(double x_viejo);
double h(double x);
double hprima(double x);

int main(int argc, char *argv[]) {
	double x_viejo = 1.1;

	encontrar_raiz(x_viejo);
	return 0;
}

void encontrar_raiz(double x_viejo)
{
	double x_nuevo = 0, tolerancia = 0, error = 1e9;
	int iteracion = 0, exponente = 0;

	printf("Ingrese el exponente para la tolerancia: ");
	scanf("%d", &exponente);
	tolerancia = pow(10, -exponente);

	while((error > tolerancia) && (iteracion < 10000))
	{
		iteracion++;

		if(fabs(hprima(x_viejo)) < 1e-12)
		{
			printf("La derivada es casi cero, Newton no puede continuar");
			exit(1);
		}

		x_nuevo = x_viejo - h(x_viejo)/hprima(x_viejo);
		error = fabs(x_nuevo - x_viejo);

		if(isnan(x_nuevo) || isinf(x_nuevo))
		{
			printf("La funcion no converge (nan/inf)");
			exit(1);
		}

		x_viejo = x_nuevo;
	}

	printf("El error es: %0.15f\nCant de iteraciones: %d\nRaiz: %.12f", error, iteracion, x_nuevo);
}

// g(x) = x^(x - cos(x))
double g(double x)
{
	return pow(x, x - cos(x));
}

// h(x) = g(x) - x   (buscamos donde h(x)=0, que es el punto fijo de g)
double h(double x)
{
	return g(x) - x;
}

// Derivada numerica de h (evita errores en la formula analitica con logaritmos)
double hprima(double x)
{
	double delta = 1e-6;
	return (h(x + delta) - h(x - delta)) / (2*delta);
}
