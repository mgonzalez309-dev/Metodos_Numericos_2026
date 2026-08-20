#include <iostream>
#include <math.h>

#define TAM 4 //cantidad de datos
#define K 3 //cantidad de incognitas
using namespace std;

double Sr(double a[K], double x[TAM], double y[TAM], double array[K][K], double resultados[K]);
double St(double y[TAM]);

int main(int argc, char *argv[]) {
	
	double x[TAM] = {0}, y[TAM] = {0}, a[K] = {0}, array[K][K] = {0}, resultados[K] = {0};
	double st = 0, sr = 0, r = 0, Ecm = 0;
	
	
	x[0] = 0.5;
	x[1] = 0.8;
	x[2] = 1.3;
	x[3] = 2;
	y[0] = -0.716;
	y[1] = -0.103;
	y[2] = 3.419;
	y[3] = 52.598;


	
	sr = Sr(a, x, y, array, resultados);
	st = St(y);
	r = pow(((st - sr) / st), 0.5); //Coeficiente de correlacion
	Ecm = pow(sr * pow(TAM, -1), 0.5);
	
	printf("\nPn: ");
	for(int i = 0; i < K; i++)
	{
		printf("%0.2lf*x^%d\t", a[i], i);
	}
	
	printf("\n\nEcm: %0.3lf\nR: %0.3lf", Ecm, r);
	
	
	
	return 0;
}


double Sr(double a[K], double x[TAM], double y[TAM], double array[K][K], double resultados[K])
{
	double pivote = 0, mayor = 0, temp = 0, suma_cocientes = 0, factor = 0, sr = 0;
	int posicion_mayor = 0;
	
	for(int l = 0; l < K; l++)
	{
		for(int m = 0; m < K; m++)
		{
			for(int z = 0; z < TAM; z++)
			{
				array[l][m] += pow(x[z], m + l);
			}
		}
		for(int i = 0; i < TAM; i++)
		{
			resultados[l] += y[i] * pow(x[i], l);
		}
	}
	
	for(int i = 0; i < K; i++)
	{
		int fila_pivote = i;
		double mayor2 = fabs(array[i][i]);
		for(int z = i + 1; z < K; z++)
		{
			if(fabs(array[z][i]) > mayor2)
			{
				mayor2 = fabs(array[z][i]);
				fila_pivote = z;
			}
		}
		if(fila_pivote != i)
		{
			for(int q = 0; q < K; q++)
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
		
		for(int j = i + 1; j < K; j++)
		{
			factor = -((array[j][i])/pivote);
			resultados[j] += resultados[i] * factor;
			for(int h = i; h < K; h++)
			{
				array[j][h] += factor * array[i][h];
			}
		}
	}
	
	
	for(int ii = K - 1; ii >= 0; ii--)
	{
		suma_cocientes = 0;
		for(int jj = K - 1; jj > ii; jj--)
		{
			suma_cocientes += array[ii][jj] * a[jj];
		}
		a[ii] = (resultados[ii] - suma_cocientes) / array[ii][ii];
	}
	
	
	for(int i = 0; i < TAM; i++)
	{
		// CORREGIDO: evaluar el polinomio COMPLETO de grado K-1,
		// no solo a[0] y a[1] (antes ignoraba a[2], a[3], etc. si K>2)
		double f_ajustado = 0;
		for(int p = 0; p < K; p++)
		{
			f_ajustado += a[p] * pow(x[i], p);
		}
		sr += pow(y[i] - f_ajustado, 2);
	}
	return sr;
}


double St(double y[TAM])
{
	double y_promedio = 0, st = 0;
	
	for(int i = 0; i < TAM; i++)
	{
		y_promedio += y[i];
	}
	y_promedio /= TAM;
	
	for(int j = 0; j < TAM; j++)
	{
		st += pow(y_promedio - y[j], 2);
	}
	
	return st;
}

