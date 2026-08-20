#include <iostream>
#include <math.h>
using namespace std;

#define TAM 3
int main(int argc, char *argv[]) {
	
	double array[TAM][TAM], resultados[TAM], x[TAM], residuo[TAM], x_viejo[TAM];
	double factor = 0, mayor = 0, temp = 0, suma_cocientes = 0, norma_residuo = 5;
	int posicion_mayor = 0, iteraciones = 0;
	
	
	array[0][0] = 3;
	array[0][1] = 1;
	array[0][2] = 1;
	resultados[0] = 5;
	x_viejo[0] = 0;
	x[0] = 0;
	array[1][0] = 2;
	array[1][1] = 6;
	array[1][2] = 1;
	resultados[1] = 9;
	x_viejo[1] = 0;
	x[1] = 0;
	array[2][0] = 1;
	array[2][1] = 1;
	array[2][2] = 4;
	resultados[2] = 6;
	x_viejo[2] = 0;
	x[2] = 0;
	
	
	
	for(int i = 0; i < TAM; i++)
	{
		for(int j = 0; j < TAM; j++)
		{
			if(abs(array[j][i]) > abs(mayor))
			{
				mayor = array[j][i];
				posicion_mayor = j;
			}
		}
		
		for(int k = 0; k < TAM; k++)
		{
			temp = array[i][k];
			array[i][k] = array[posicion_mayor][k];
			array[posicion_mayor][k] = temp;
		}
		
		temp = resultados[i];
		resultados[i] = resultados[posicion_mayor];
		resultados[posicion_mayor] = temp;
		mayor = 0;
	}
	
	for(int l = 0; l < TAM; l++)
	{
		suma_cocientes = 0;
		for(int o = 0; o < TAM; o++)
		{
			suma_cocientes += abs(array[l][o]);
		}
		if(abs(array[l][l]) < suma_cocientes - abs(array[l][l]))
		{
			printf("No es diagonalmente dominante\n");
			break;
		}
	}
	
	
	while(norma_residuo > pow(10, -11) && (iteraciones < 10000))
	{
		iteraciones++;
		norma_residuo = 0;

		for(int m = 0; m < TAM; m++)
		{
			factor = resultados[m];
			for(int k = 0; k < TAM; k++)
			{
				if(m != k)
				{
					factor -= array[m][k] * x_viejo[k];
				}
			}
			x[m] = factor/array[m][m];
		}
		for(int p = 0; p < TAM; p++)
		{
			x_viejo[p] = x[p];
		}
		
		for(int ii = 0; ii < TAM; ii++)
		{
			residuo[ii] = 0;
			for(int jj = 0; jj < TAM; jj++)
			{
				residuo[ii] += array[ii][jj] * x[jj];
			}
			residuo[ii] -= resultados[ii];
			norma_residuo += pow(residuo[ii], 2);
		}
		norma_residuo = pow(norma_residuo, 0.5);

	}
	
	for(int s = 0; s < TAM; s++)
	{
		for(int t = 0; t < TAM; t++)
		{
			printf("%0.2lf\t", array[s][t]);
		}
		printf("|\t%0.2lf\n", resultados[s]);
	}
	printf("\nIteraciones: %d\n", iteraciones);
	for(int u = 0; u < TAM; u++)
	{
		printf("x%d: %0.2lf\t", u + 1, x[u]);
	}
	printf("\nError: %0.10lf", norma_residuo);
	
	return 0;
}

