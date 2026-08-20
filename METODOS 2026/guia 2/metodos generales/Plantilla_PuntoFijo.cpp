#include <iostream>
#include <math.h>

using namespace std;

void encontrar_raiz(double x_viejo);
double g(double x);
double gprima(double x);

int main(int argc, char *argv[]) {
	double x_viejo = 1;   // <-- CAMBIAR: valor inicial (x0) segun el enunciado

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
			printf("La funcion no converge (nan/inf) - probar otro x0");
			exit(1);
		}
		// OJO: comparamos contra el valor de |g'| en la iteracion actual.
		// Si esto da >= 1, el metodo de punto fijo NO puede converger con
		// esta g(x) (condicion necesaria |g'(raiz)| < 1). En ese caso hay
		// que despejar x = g(x) de otra forma a partir de f(x)=0.
		if(fabs(gprima(x_nuevo)) >= 1)
		{
			printf("|g'(x)| >= 1 cerca de la raiz: el punto fijo no converge con esta g(x).\nProbar despejar x=g(x) de otra manera.");
			exit(1);
		}
		if(error_nuevo > error_viejo)
		{
			printf("El error esta creciendo: la iteracion se aleja de la raiz");
			exit(1);
		}
		error_viejo = error_nuevo;
		x_viejo = x_nuevo;
	}

	if(iteracion >= 10000)
		printf("ATENCION: se alcanzo el maximo de iteraciones sin converger\n\n");

	printf("El error es: %0.15f\nCant de iteraciones: %d\nRaiz: %.12f", error_nuevo, iteracion, x_nuevo);
}

// ============================================================
// UNICA PARTE QUE SE CAMBIA PARA CADA EJERCICIO DEL PARCIAL:
// despeja x = g(x) a partir del f(x)=0 que te den, y ajusta x_viejo.
// ============================================================
double g(double x)
{
	return cos(sin(x));   // <-- reemplazar
}

// Derivada numerica de g (diferencia central) -- sirve para cualquier g(x)
double gprima(double x)
{
	double h = 1e-6;
	return (g(x + h) - g(x - h)) / (2*h);
}
