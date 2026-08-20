#include <iostream>
#include <math.h>
using namespace std;

#define MAX 20   // tamano maximo soportado

int main(int argc, char *argv[]) {

	int N = 0;
	double array[MAX][MAX], resultados[MAX], x[MAX] = {0}, x_viejo[MAX] = {0};
	double factor = 0, suma_cocientes = 0, error = 1e9;
	int iteraciones = 0;

	printf("Tamano del sistema (N): ");
	scanf("%d", &N);

	for(int i = 0; i < N; i++)
	{
		for(int j = 0; j < N; j++)
		{
			printf("Fila %d, Columna %d: ", i, j);
			scanf("%lf", &array[i][j]);
		}
		printf("Resultado de Fila %d: ", i);
		scanf("%lf", &resultados[i]);
		x[i] = 0;
		x_viejo[i] = 0;
	}

	// --- Chequeo INFORMATIVO de dominancia diagonal (no reordena solo) ---
	// OJO: si no es diagonalmente dominante, el metodo puede converger
	// igual (es condicion suficiente, no necesaria) o puede divergir.
	// Si diverge, la solucion en el parcial es CAMBIAR VOS el orden de
	// las ecuaciones a mano (mirando cual fila conviene poner en cada
	// posicion) y volver a correr el programa con esos datos.
	bool dominante = true;
	for(int l = 0; l < N; l++)
	{
		double suma = 0;
		for(int o = 0; o < N; o++)
		{
			if(o != l) suma += fabs(array[l][o]);
		}
		if(fabs(array[l][l]) < suma)
		{
			dominante = false;
		}
	}
	if(!dominante)
	{
		printf("\nATENCION: la matriz NO es diagonalmente dominante.\n");
		printf("El metodo puede converger igual, pero no esta garantizado.\n");
		printf("Si diverge, probar reordenando las ecuaciones a mano.\n\n");
	}

	// ============================================================
	// METODO DE JACOBI
	// ============================================================
	while(error > 1e-10 && iteraciones < 10000)
	{
		iteraciones++;

		for(int m = 0; m < N; m++)
		{
			factor = resultados[m];
			for(int k = 0; k < N; k++)
			{
				if(m != k)
				{
					factor -= array[m][k] * x_viejo[k];
				}
			}
			x[m] = factor / array[m][m];
		}

		error = 0;
		for(int p = 0; p < N; p++)
		{
			error += pow(x[p] - x_viejo[p], 2);
			x_viejo[p] = x[p];
		}
		error = sqrt(error);

		if(isnan(error) || isinf(error))
		{
			printf("El metodo diverge para esta matriz/orden de ecuaciones.\n");
			printf("Probar reordenando las ecuaciones a mano.\n");
			return 1;
		}
	}

	if(iteraciones >= 10000)
		printf("ATENCION: se alcanzo el maximo de iteraciones sin converger\n\n");

	printf("\nSolucion:\n");
	for(int u = 0; u < N; u++)
	{
		printf("x%d = %0.6lf\n", u + 1, x[u]);
	}
	printf("\nIteraciones: %d\nError: %0.10lf\n", iteraciones, error);

	return 0;
}
