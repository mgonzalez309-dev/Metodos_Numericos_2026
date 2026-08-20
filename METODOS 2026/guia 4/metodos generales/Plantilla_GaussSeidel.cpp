#include <iostream>
#include <math.h>
using namespace std;

#define MAX 20   // tamano maximo soportado

int main(int argc, char *argv[]) {

	int N = 0;
	double array[MAX][MAX], resultados[MAX], x[MAX] = {0};
	double factor = 0, x_viejo = 0, error = 1e9;
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
	}

	// --- Chequeo INFORMATIVO de dominancia diagonal (no reordena solo) ---
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
		printf("El metodo puede converger igual (Gauss-Seidel converge\n");
		printf("garantizado si la matriz es simetrica y definida positiva,\n");
		printf("aunque no sea diagonalmente dominante), pero no siempre.\n");
		printf("Si diverge, probar reordenando las ecuaciones a mano.\n\n");
	}

	// ============================================================
	// METODO DE GAUSS-SEIDEL
	// ============================================================
	while(error > 1e-10 && iteraciones < 10000)
	{
		iteraciones++;
		error = 0;

		for(int m = 0; m < N; m++)
		{
			factor = resultados[m];
			for(int k = 0; k < N; k++)
			{
				if(m != k)
				{
					factor -= array[m][k] * x[k];
				}
			}
			x_viejo = x[m];
			x[m] = factor / array[m][m];
			error += pow(x[m] - x_viejo, 2);
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
