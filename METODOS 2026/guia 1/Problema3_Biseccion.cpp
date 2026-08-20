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

// Problema 3: velocidad del paracaidista
// v(t,m,c) = (g*m/c)*(1 - exp(-c/m*t)) - 35 = 0,  g=9.81, c=14, t=7
// Datos de prueba: a=50, b=200, exponente=4  (tol = 1e-4)
double f(double x)
{
	double g = 9.81, c = 14.0, t = 7.0, v_obj = 35.0;
	return ((g * x)/c) * (1 - exp(-(c/x) * t)) - v_obj;
}
