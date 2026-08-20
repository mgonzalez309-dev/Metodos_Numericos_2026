#include <iostream>
#include <math.h>

using namespace std;

void encontrar_raiz(double x0, double x1);
double f(double x);

int main(int argc, char *argv[]) {
	double x0 = 0, x1 = 1;   // <-- CAMBIAR: dos valores iniciales segun el enunciado

	encontrar_raiz(x0, x1);
	return 0;
}

void encontrar_raiz(double x0, double x1)
{
	double x2 = 0, tolerancia = 0, error = 1e9;
	int iteracion = 0, exponente = 0;

	printf("Ingrese el exponente para la tolerancia: ");
	scanf("%d", &exponente);
	tolerancia = pow(10, -exponente);

	while((error > tolerancia) && (iteracion < 10000))
	{
		iteracion++;

		double denominador = f(x1) - f(x0);
		if(fabs(denominador) < 1e-14)
		{
			printf("f(x1)-f(x0) es casi cero, la secante no puede continuar");
			exit(1);
		}

		// formula de la secante: x2 = x1 - f(x1)*(x1-x0)/(f(x1)-f(x0))
		x2 = x1 - f(x1) * (x1 - x0) / denominador;
		error = fabs(x2 - x1);

		if(isnan(x2) || isinf(x2))
		{
			printf("La funcion no converge (nan/inf) - probar otros x0,x1");
			exit(1);
		}

		x0 = x1;
		x1 = x2;
	}

	if(iteracion >= 10000)
		printf("ATENCION: se alcanzo el maximo de iteraciones sin converger\n\n");

	printf("Raiz: %.12f\nEl error es: %0.15lf\nCant de iteraciones: %d\n", x2, error, iteracion);
}

// ============================================================
// UNICA PARTE QUE SE CAMBIA PARA CADA EJERCICIO DEL PARCIAL:
// escribi aca la f(x) = 0 que te den, y ajusta x0, x1 en el main.
// ============================================================
double f(double x)
{
	return 8*pow(x, 3) + 7*pow(x, 2) + 11*x + 13;   // <-- reemplazar
}
