#include <iostream>
#include <math.h>

using namespace std;

void encontrar_raiz();
double f(double x);

int main(int argc, char *argv[]) {

	encontrar_raiz();

	return 0;
}

void encontrar_raiz()
{
	double a = 0, b = 0, c = 0, error = 1000, error_minimo = 0;
	int iteracion = 0, exponente = 0;

	printf("a = ");
	scanf("%lf", &a);
	printf("\nb = ");
	scanf("%lf", &b);
	printf("\nexponente error minimo = ");
	scanf("%d", &exponente);
	error_minimo = 1 * pow(10, -exponente);

	// Verificacion de cambio de signo ANTES de arrancar el loop
	if((f(a) * f(b)) > 0)
	{
		printf("No existe una raiz en ese intervalo (no hay cambio de signo)\n");
		exit(0);
	}
	if(f(a) == 0) { printf("La raiz es: %lf\n", a); return; }
	if(f(b) == 0) { printf("La raiz es: %lf\n", b); return; }

	do
	{
		c = (b + a)/2;
		error = fabs((b-a)/2);
		iteracion++;

		if(f(c) == 0)
		{
			error = 0;
			break;
		}
		else if((f(a) * f(c)) < 0)
		{
			b = c;
		}
		else
		{
			a = c;
		}
	} while(error >= error_minimo && iteracion < 1000);

	printf("La raiz es la siguiente: %lf\nCantidad de iteraciones: %d\nError: %lf", c, iteracion, error);
}

// ============================================================
// UNICA PARTE QUE SE CAMBIA PARA CADA EJERCICIO DEL PARCIAL:
// escribi aca la f(x) del problema que te den.
// ============================================================
double f(double x)
{
	return pow(x, 10) - 1;   // <-- reemplazar por la funcion del ejercicio
}
