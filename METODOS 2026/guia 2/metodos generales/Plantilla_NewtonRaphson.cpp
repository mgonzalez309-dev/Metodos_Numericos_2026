#include <iostream>
#include <math.h>

using namespace std;

void encontrar_raiz(double x_viejo);
double f(double x);
double fprima(double x);

int main(int argc, char *argv[]) {
	double x_viejo = 0.5;   // <-- CAMBIAR: valor inicial (x0) segun el enunciado

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

		if(fabs(fprima(x_viejo)) < 1e-12)
		{
			printf("La derivada es casi cero, Newton no puede continuar (probar otro x0)");
			exit(1);
		}

		x_nuevo = x_viejo - f(x_viejo)/fprima(x_viejo);
		error = fabs(x_nuevo - x_viejo);

		if(isnan(x_nuevo) || isinf(x_nuevo))
		{
			printf("La funcion no converge (nan/inf) - probar otro x0");
			exit(1);
		}

		x_viejo = x_nuevo;
	}

	if(iteracion >= 10000)
		printf("ATENCION: se alcanzo el maximo de iteraciones sin converger\n\n");

	printf("Raiz: %.12f\nEl error es: %0.15lf\nCant de iteraciones: %d\n", x_nuevo, error, iteracion);
}

// ============================================================
// UNICA PARTE QUE SE CAMBIA PARA CADA EJERCICIO DEL PARCIAL:
// escribi aca la f(x) = 0 que te den, y ajusta x_viejo en el main.
// ============================================================
double f(double x)
{
	return pow(x, 5) - 3*pow(x, 3) - 2*pow(x, 2) + 2;   // <-- reemplazar
}

// Derivada NUMERICA (diferencia central) -- funciona para cualquier f(x)
// sin tener que derivarla a mano. Si la profe pide la derivada analitica
// especificamente, reemplazar el cuerpo por la formula de f'(x) a mano.
double fprima(double x)
{
	double h = 1e-6;
	return (f(x + h) - f(x - h)) / (2*h);
}
