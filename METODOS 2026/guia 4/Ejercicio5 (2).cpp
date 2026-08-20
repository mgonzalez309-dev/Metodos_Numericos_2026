#include <iostream>
#include <math.h>
using namespace std;

#define TAM 6
int main(int argc, char *argv[]) {
	
	double array[TAM][TAM], resultados[TAM], x[TAM];
	double factor = 0, mayor = 0, temp = 0, suma_cocientes = 0, x_viejo, error = 5, w = 0;
	int posicion_mayor = 0, iteraciones = 0;
	
	w = 1.1;
	array[0][0] = 3;
	array[0][1] = -2;
	array[0][2] = 1;
	array[0][3] = 0;
	array[0][4] = 0;
	array[0][5] = 0;
	resultados[0] = 10;
	x[0] = 0;
	array[1][0] = -2;
	array[1][1] = 4;
	array[1][2] = -2;
	array[1][3] = 1;
	array[1][4] = 0;
	array[1][5] = 0;
	resultados[1] = -8;
	x[1] = 0;
	array[2][0] = 1;
	array[2][1] = -2;
	array[2][2] = 4;
	array[2][3] = -2;
	array[2][4] = 1;
	array[2][5] = 0;
	resultados[2] = 10;
	x[2] = 0;
	array[3][0] = 0;
	array[3][1] = 1;
	array[3][2] = -2;
	array[3][3] = 4;
	array[3][4] = -2;
	array[3][5] = 1;
	resultados[3] = 10;
	x[3] = 0;
	array[4][0] = 0;
	array[4][1] = 0;
	array[4][2] = 1;
	array[4][3] = -2;
	array[4][4] = 4;
	array[4][5] = -2;
	resultados[4] = -8;
	x[4] = 0;
	array[5][0] = 0;
	array[5][1] = 0;
	array[5][2] = 0;
	array[5][3] = 1;
	array[5][4] = -2;
	array[5][5] = 3;
	resultados[5] = 10;
	x[5] = 0;
	
	
	
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
			x[m] = ((factor * w)/array[m][m]) + ((1 - w) * x_viejo);
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

