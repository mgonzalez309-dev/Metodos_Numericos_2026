#include <iostream>
#include <math.h>

using namespace std;

void biseccion();
void regula_falsi();
double f(double x);

int main(int argc, char *argv[]) {

	printf("=== METODO DE BISECCION ===\n");
	biseccion();

	printf("\n\n=== METODO DE REGULA FALSI ===\n");
	regula_falsi();

	return 0;
}

void biseccion()
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

	if((f(a) * f(b)) > 0)
	{
		printf("No existe una raiz en ese intervalo (no hay cambio de signo)");
		exit(0);
	}

	do
	{
		c = (b + a)/2;
		error = fabs((b-a)/2);
		iteracion++;

		if((f(a) * f(c)) < 0)
		{
			b = c;
		}
		else if((f(a) * f(c)) > 0)
		{
			a = c;
		}
		else
		{
			error = 0;
			break;
		}
	} while(error >= error_minimo && iteracion < 1000);

	printf("La raiz es la siguiente: %lf\nCantidad de iteraciones: %d\nError: %lf", c, iteracion, error);
}

void regula_falsi()
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

	if((f(a) * f(b)) > 0)
	{
		printf("No existe una raiz en ese intervalo (no hay cambio de signo)");
		exit(0);
	}

	do
	{
		c = ((a * f(b)) - (b * f(a))) / (f(b) - f(a));
		iteracion++;

		if((f(a) * f(c)) < 0)
		{
			error = fabs((c - b)/c) * 100;  // error relativo % (mejor que |b-a|/2 en regula falsi)
			b = c;
		}
		else if((f(a) * f(c)) > 0)
		{
			error = fabs((c - a)/c) * 100;
			a = c;
		}
		else
		{
			error = 0;
			break;
		}
	} while(error >= error_minimo && iteracion < 10000);

	printf("La raiz es la siguiente: %lf\nCantidad de iteraciones: %d\nError: %lf", c, iteracion, error);
}

// Problema 2: g(a) = a^10 - 1  (raiz positiva a=1)
// Datos de prueba: a=0, b=1.3, exponente=5  (tol = 1e-5)
double f(double x)
{
	return pow(x, 10) - 1;
}
