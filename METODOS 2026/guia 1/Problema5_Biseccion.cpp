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

// Problema 5: ciclo termodinamico, x = T2/T1, gamma = 5/3
// eta(x) = [ln(x)-(1-1/x)] / [ln(x)+(1-1/x)/(gamma-1)] - 0.30 = 0
// Datos de prueba: a=3, b=8, exponente=6  (tol = 1e-6)
double f(double x)
{
	double gamma = 5.0/3.0;
	return ( (log(x) - (1 - (1/x))) / (log(x) + ((1 - (1/x))/(gamma - 1))) ) - 0.30;
}
