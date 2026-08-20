
#include <iostream>
#include <math.h>

#define TAM 3 //cantidad de datos
using namespace std;


double Pn(double x_prima, double coeficientes[TAM]);
void Gauss(double array[TAM][TAM], double resultados[TAM], double coeficientes[TAM], double x[TAM], double y[TAM]);

int main(int argc, char *argv[]) {
	
	double x[TAM] = {0}, y[TAM] = {0}, array[TAM][TAM] = {0}, resultados[TAM] = {0}, coeficientes[TAM] = {0};
	double x_prima = 0;
	
	x_prima = 90;
	
	x[0] = 0;
	x[1] = 60;
	x[2] = 100;
	y[0] = 1;
	y[1] = 4;
	y[2] = 10;



	Gauss(array, resultados, coeficientes, x, y);
	
	printf("Y_prima: %0.6lf", Pn(x_prima, coeficientes));
	
	
	
	return 0;
}


double Pn(double x_prima, double coeficientes[TAM])
{
	double sumatoria = 0;
	
	for(int i = 0; i < TAM; i++)
	{
		sumatoria += coeficientes[i] * pow(x_prima, i);
	}
	
	return sumatoria;
}


void Gauss(double array[TAM][TAM], double resultados[TAM], double coeficientes[TAM], double x[TAM], double y[TAM])
{
	double pivote = 0, factor = 0, determinante = 1, mayor = 0, temp = 0, suma_cocientes = 0;
	int posicion_mayor = 0, cambio_filas = 1;
	
	for(int i = 0; i < TAM; i++)
	{
		for(int j = 0; j < TAM; j++)
		{
			array[i][j] = pow(x[i], j);
		}
		resultados[i] = y[i];
	}
	
	
	
	for(int i = 0; i < TAM; i++)
	{
		int fila_pivote = i;
		double mayor2 = fabs(array[i][i]);
		for(int z = i + 1; z < TAM; z++)
		{
			if(fabs(array[z][i]) > mayor2)
			{
				mayor2 = fabs(array[z][i]);
				fila_pivote = z;
			}
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
		if(determinante == 0)
		{
			printf("No tiene solucion unica");
			exit(1);
		}
	}
	determinante *= cambio_filas;
	
	
	
	for(int ii = TAM - 1; ii >= 0; ii--)
	{
		suma_cocientes = 0;
		for(int jj = TAM - 1; jj > ii; jj--)
		{
			suma_cocientes += array[ii][jj] * coeficientes[jj];
		}
		coeficientes[ii] = (resultados[ii] - suma_cocientes) / array[ii][ii];
	}
	
	for(int s = 0; s < TAM; s++)
	{
		for(int q = 0; q < TAM; q++)
		{
			printf("%0.2lf\t", array[s][q]);
		}
		printf("|\t%0.2lf\n", resultados[s]);
	}
	printf("\nDeterminante: %0.5lf\n", determinante);
	
	
	printf("Pn: ");
	for(int c = 0; c < TAM; c++)
	{
		printf("%0.2lf x^%d \t", coeficientes[c], c);
	}
}


