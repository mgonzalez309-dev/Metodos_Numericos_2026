#include <iostream>
#include <math.h>

using namespace std;

int main(int argc, char *argv[]) {

	double a = 0, b = 0, delta = 0;
	int n = 0;

	printf("a = ");
	scanf("%lf", &a);
	printf("\nb = ");
	scanf("%lf", &b);
	printf("\ndelta (tolerancia deseada) = ");
	scanf("%lf", &delta);

	// De |r - c| <= |b-a| / 2^n   =>   n >= log2(|b-a| / delta)
	n = (int) ceil( log2( fabs(b - a) / delta ) );

	printf("Numero de bisecciones necesarias: %d\n", n);

	return 0;
}

// Problema 4
// Datos de prueba: a=0, b=1, delta=0.0001  (como en el Problema 1)  -> n = 14
