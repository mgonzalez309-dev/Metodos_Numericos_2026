#include <iostream>
#include <math.h>
using namespace std;

#define TAM 4

void Gauss(double array[TAM][TAM], double resultados[TAM], double x[TAM]);

int main(int argc, char *argv[]) {

	double array[TAM][TAM] = {0}, resultados[TAM] = {0}, x[TAM] = {0};

	// CAMBIAR ACA los datos del sistema que te den en el parcial:
	array[0][0] = 3;
	array[0][1] = 2;
	array[0][2] = 8;
	array[0][3] = 0;
	resultados[0] = 2;
	array[1][0] = 1;
	array[1][1] = 3;
	array[1][2] = 1;
	array[1][3] = 1;
	resultados[1] = 5;
	array[2][0] = 1;
	array[2][1] = 2;
	array[2][2] = 1;
	array[2][3] = 1;
	resultados[2] = 3;
	array[3][0] = 1;
	array[3][1] = 3;
	array[3][2] = 2;
	array[3][3] = 7;
	resultados[3] = 4;

	Gauss(array, resultados, x);

	return 0;
}


void Gauss(double array[TAM][TAM], double resultados[TAM], double x[TAM])
{
	double pivote = 0, factor = 0, determinante = 1, temp = 0, suma_cocientes = 0;
	int cambio_filas = 1;

	for(int i = 0; i < TAM; i++)
	{
		// --- Pivoteo parcial CORREGIDO: buscar el mayor |valor| solo
		// entre las filas i..TAM-1 (nunca las de arriba, ya resueltas) ---
		int fila_pivote = i;
		double mayor = fabs(array[i][i]);
		for(int z = i + 1; z < TAM; z++)
		{
			if(fabs(array[z][i]) > mayor)
			{
				mayor = fabs(array[z][i]);
				fila_pivote = z;
			}
		}

		if(mayor < 1e-12)
		{
			printf("No tiene solucion unica (pivote nulo)");
			exit(1);
		}

		if(fila_pivote != i)
		{
			for(int q = 0; q < TAM; q++)
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

		for(int j = i + 1; j < TAM; j++)
		{
			factor = -((array[j][i])/pivote);
			resultados[j] += resultados[i] * factor;
			for(int k = i; k < TAM; k++)
			{
				array[j][k] += factor * array[i][k];
			}
		}
	}

	for(int s = 0; s < TAM; s++)
	{
		determinante *= array[s][s];
	}
	determinante *= cambio_filas;

	// --- Sustitucion hacia atras CORREGIDA: jj > ii, NUNCA jj == ii,
	// porque x[ii] todavia no fue calculado en ese punto (antes esto
	// funcionaba "de casualidad" solo porque x[] se inicializaba en {0}) ---
	for(int ii = TAM - 1; ii >= 0; ii--)
	{
		suma_cocientes = 0;
		for(int jj = TAM - 1; jj > ii; jj--)
		{
			suma_cocientes += array[ii][jj] * x[jj];
		}
		x[ii] = (resultados[ii] - suma_cocientes) / array[ii][ii];
	}

	for(int s = 0; s < TAM; s++)
	{
		for(int q = 0; q < TAM; q++)
		{
			printf("%0.2lf\t", array[s][q]);
		}
		printf("|\t%0.2lf\n", resultados[s]);
	}
	printf("\nDeterminante: %0.2lf\n", determinante);

	for(int c = 0; c < TAM; c++)
	{
		printf("x%d: %0.2lf\t", c + 1, x[c]);
	}
}
