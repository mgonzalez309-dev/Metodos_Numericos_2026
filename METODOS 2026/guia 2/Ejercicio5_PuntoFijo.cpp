#include <iostream>
#include <math.h>

using namespace std;

void encontrar_raiz(double x_viejo);
double g(double x, double a, double b);
double gprima(double x, double a, double b);

int main(int argc, char *argv[]) {
	double x_viejo = 1.1;   // valor inicial; funciona bien para (a,b) del tipo (10,6) o (12,5)

	encontrar_raiz(x_viejo);
	return 0;
}

void encontrar_raiz(double x_viejo)
{
	double x_nuevo = 0, tolerancia = 0, error_viejo = 1e9, error_nuevo = 1e9, a = 0, b = 0;
	int iteracion = 0, exponente = 0;

	printf("Ingrese el exponente para la tolerancia: ");
	scanf("%d", &exponente);
	printf("Ingrese el valor de a: ");
	scanf("%lf", &a);
	printf("Ingrese el valor de b: ");
	scanf("%lf", &b);

	tolerancia = pow(10, -exponente);

	// NOTA: esta funcion converge lento (cientos/miles de iteraciones) porque
	// g'(C) esta cerca de 1 en la solucion. Es normal, no es un error.
	// Subimos el limite de iteraciones para darle margen.
	while((error_nuevo > tolerancia) && (iteracion < 200000))
	{
		iteracion++;
		x_nuevo = g(x_viejo, a, b);
		error_nuevo = fabs(x_nuevo - x_viejo);

		if(isnan(x_nuevo) || isinf(x_nuevo))
		{
			printf("La funcion no converge (nan/inf) - probar otro x0");
			exit(1);
		}
		if(error_nuevo > error_viejo * 1.5)   // margen para no cortar por ruido numerico
		{
			printf("Se aleja de la raiz, no converge");
			exit(1);
		}
		error_viejo = error_nuevo;
		x_viejo = x_nuevo;
	}

	printf("El error es: %0.15f\nCant de iteraciones: %d\nRaiz (C): %.12f", error_nuevo, iteracion, x_nuevo);
}

// Catenaria: b = C*cosh(a/C) - C   =>   C = g(C) = C*cosh(a/C) - b  ... reordenado como punto fijo
double g(double x, double a, double b)
{
	return x * cosh(a/x) - b;
}

double gprima(double x, double a, double b)
{
	double h = 1e-6;
	return (g(x + h, a, b) - g(x - h, a, b)) / (2*h);
}
