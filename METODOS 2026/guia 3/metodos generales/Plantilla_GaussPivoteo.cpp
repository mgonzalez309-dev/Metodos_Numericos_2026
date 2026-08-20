#include <iostream>
#include <math.h>

using namespace std;

#define MAX 20   // tamano maximo soportado (subir si el sistema es mas grande)

int main(int argc, char *argv[]) {

	int N = 0;
	double array[MAX][MAX], resultados[MAX], x[MAX];
	double pivote = 0, factor = 0, determinante = 1, temp = 0, suma = 0, norma = 0;
	int cambio_filas = 1;

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
	}

	// ============================================================
	// ELIMINACION GAUSSIANA CON PIVOTEO PARCIAL
	// ============================================================
	for(int i = 0; i < N; i++)
	{
		// --- Pivoteo parcial: buscar SIEMPRE el mayor |valor| en la
		// columna i, pero SOLO entre las filas i..N-1 (las de abajo,
		// nunca las ya procesadas arriba) ---
		int fila_pivote = i;
		double mayor = fabs(array[i][i]);
		for(int z = i + 1; z < N; z++)
		{
			if(fabs(array[z][i]) > mayor)
			{
				mayor = fabs(array[z][i]);
				fila_pivote = z;
			}
		}

		if(mayor < 1e-12)
		{
			printf("\nEl sistema no tiene solucion unica (pivote nulo)\n");
			exit(1);
		}

		if(fila_pivote != i)
		{
			for(int q = 0; q < N; q++)
			{
				temp = array[i][q];
				array[i][q] = array[fila_pivote][q];
				array[fila_pivote][q] = temp;
			}
			temp = resultados[i];
			resultados[i] = resultados[fila_pivote];
			resultados[fila_pivote] = temp;
			cambio_filas *= -1;
		}

		pivote = array[i][i];

		// --- Eliminacion hacia abajo ---
		for(int j = i + 1; j < N; j++)
		{
			factor = -(array[j][i] / pivote);
			resultados[j] += resultados[i] * factor;
			for(int k = i; k < N; k++)
			{
				array[j][k] += factor * array[i][k];
			}
		}
	}

	// --- Determinante = producto de la diagonal, con el signo de los cambios de fila ---
	for(int s = 0; s < N; s++)
	{
		determinante *= array[s][s];
	}
	determinante *= cambio_filas;

	// ============================================================
	// SUSTITUCION HACIA ATRAS (CORREGIDA: el indice jj NUNCA debe
	// incluir a ii, porque x[ii] todavia no esta calculado)
	// ============================================================
	for(int ii = N - 1; ii >= 0; ii--)
	{
		suma = 0;
		for(int jj = N - 1; jj > ii; jj--)   // <-- jj > ii (antes decia jj >= ii, ese era el bug)
		{
			suma += array[ii][jj] * x[jj];
		}
		x[ii] = (resultados[ii] - suma) / array[ii][ii];
	}

	// ============================================================
	// SALIDA
	// ============================================================
	printf("\nMatriz triangular superior resultante:\n");
	for(int s = 0; s < N; s++)
	{
		for(int q = 0; q < N; q++)
		{
			printf("%0.4lf\t", array[s][q]);
			norma += pow(array[s][q], 2);
		}
		printf("|\t%0.4lf\n", resultados[s]);
	}

	printf("\nDeterminante: %0.6lf\n", determinante);

	printf("\nSolucion:\n");
	for(int c = 0; c < N; c++)
	{
		printf("x%d = %0.6lf\n", c + 1, x[c]);
	}

	return 0;
}
