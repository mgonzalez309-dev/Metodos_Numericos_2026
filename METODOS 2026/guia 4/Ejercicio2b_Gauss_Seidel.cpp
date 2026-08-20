#include <iostream>
#include <math.h>
using namespace std;

#define TAM 4
int main(int argc, char *argv[]) {
	
	double array[TAM][TAM], resultados[TAM], x[TAM];
	double factor = 0, mayor = 0, temp = 0, suma_cocientes = 0, x_viejo, error = 5;
	int posicion_mayor = 0, iteraciones = 0;
	
	
	array[0][0] = 5;
	array[0][1] = 7;
	array[0][2] = 6;
	array[0][3] = 5;
	resultados[0] = 23;
	x[0] = 0;
	array[1][0] = 7;
	array[1][1] = 10;
	array[1][2] = 8;
	array[1][3] = 7;
	resultados[1] = 32;
	x[1] = 0;
	array[2][0] = 6;
	array[2][1] = 8;
	array[2][2] = 10;
	array[2][3] = 9;
	resultados[2] = 33;
	x[2] = 0;
	array[3][0] = 5;
	array[3][1] = 7;
	array[3][2] = 9;
	array[3][3] = 10;
	resultados[3] = 31;
	x[3] = 0;
	
	
	
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
	
	
	while(error > pow(10, -11) && (iteraciones < 10000))
	{
		iteraciones++;
		error = 0;
		for(int m = 0; m < TAM; m++)
		{
			factor = resultados[m];
			for(int k = 0; k < TAM; k++)
			{
				if(m != k)
				{
					factor -= array[m][k] * x[k];
				}
			}
			x_viejo = x[m];
			x[m] = factor/array[m][m];
			error += pow(x[m] - x_viejo, 2);
		}
		error = pow(error, 0.5);
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
	printf("\nError: %0.10lf", error);
	
	return 0;
}

