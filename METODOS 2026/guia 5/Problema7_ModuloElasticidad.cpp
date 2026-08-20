#include <iostream>
#include <math.h>
using namespace std;

#define N 12   // 4 tensiones x 3 ensayos = 12 puntos (sigma, epsilon)

int main(int argc, char *argv[]) {

	// sigma [MPa] repetido para cada uno de los 3 ensayos
	double sigma[N] = {34.5,69.0,103.5,138.0,  34.5,69.0,103.5,138.0,  34.5,69.0,103.5,138.0};
	// epsilon [m/mm] medido en cada ensayo
	double eps[N]   = {0.46,0.95,1.48,1.93,    0.34,1.02,1.51,2.09,    0.73,1.10,1.62,2.12};

	// Buscamos sigma = E*epsilon + B  (regresion lineal, x=epsilon, y=sigma)
	double Sx=0, Sy=0, Sxy=0, Sx2=0;
	for(int i = 0; i < N; i++)
	{
		Sx  += eps[i];
		Sy  += sigma[i];
		Sxy += eps[i]*sigma[i];
		Sx2 += eps[i]*eps[i];
	}

	double E = (N*Sxy - Sx*Sy) / (N*Sx2 - Sx*Sx);   // pendiente = modulo de elasticidad
	double B = (Sy - E*Sx) / N;

	printf("sigma(epsilon) = %.10lf * epsilon + %.10lf\n", E, B);
	printf("\nModulo de elasticidad estimado E = %.6lf MPa\n", E);

	double suma_err2 = 0;
	for(int i = 0; i < N; i++)
	{
		double sigma_ajustado = E*eps[i] + B;
		suma_err2 += pow(sigma_ajustado - sigma[i], 2);
	}
	double ECM = sqrt(suma_err2/N);
	printf("ECM = %.6lf\n", ECM);

	return 0;
}
