#include <iostream>
#include <math.h>
using namespace std;

#define N 8   // cantidad de puntos

int main(int argc, char *argv[]) {

	double x[N] = {-1, 0, 1, 2, 3, 4, 5, 6};
	double y[N] = {10, 9, 7, 5, 4, 3, 0, -1};

	double sum_x = 0, sum_y = 0, sum_xy = 0, sum_x2 = 0, sum_y2 = 0;
	for(int i = 0; i < N; i++)
	{
		sum_x  += x[i];
		sum_y  += y[i];
		sum_xy += x[i] * y[i];
		sum_x2 += x[i] * x[i];
		sum_y2 += y[i] * y[i];
	}

	// f(x) = A*x + B  (regresion lineal por minimos cuadrados)
	double A = (N * sum_xy - sum_x * sum_y) / (N * sum_x2 - sum_x * sum_x);
	double B = (sum_y - A * sum_x) / N;

	printf("f(x) = %.8lf * x + %.8lf\n", A, B);

	// Error cuadratico medio
	double suma_error2 = 0;
	for(int i = 0; i < N; i++)
	{
		double fi = A * x[i] + B;
		suma_error2 += pow(fi - y[i], 2);
	}
	double ECM = sqrt(suma_error2 / N);
	printf("ECM = %.8lf\n", ECM);

	// Coeficiente de correlacion R (formula (3) del enunciado)
	double numerador = N * sum_xy - sum_x * sum_y;
	double denominador = sqrt(N * sum_x2 - sum_x * sum_x) * sqrt(N * sum_y2 - sum_y * sum_y);
	double R = numerador / denominador;
	printf("R = %.8lf\n", R);

	// Forma alternativa de R (formula (4)) usando la media de y
	double y_medio = sum_y / N;
	double suma_dev2 = 0;
	for(int i = 0; i < N; i++)
	{
		suma_dev2 += pow(y[i] - y_medio, 2);
	}
	double R_alt = (suma_dev2 - suma_error2) / suma_dev2;
	printf("R (formula alternativa) = %.8lf\n", R_alt);

	return 0;
}
