
#include <iostream>
#include <math.h>

#define TAM 2 //cantidad de sub_intervalos
using namespace std;

double Pn(double x_prima, double x[TAM + 1], double y[TAM + 1]);

int main(int argc, char *argv[]) {
	
	double x[TAM + 1], y[TAM + 1];
	double x_prima = 0;
	
	x_prima = 5;
	
	x[0] = 0;
	x[1] = 60;
	x[2] = 100;
	y[0] = 1;
	y[1] = 4;
	y[2] = 10;


	
	
	printf("Y_prima: %0.3lf", Pn(x_prima, x, y));
	
	
	return 0;
}


double Pn(double x_prima, double x[TAM + 1], double y[TAM + 1])
{
	double productoria = 1, sumatoria = 0;
	
	for(int k = 0; k <= TAM; k++)
	{
		productoria = 1;
		for(int i = 0; i <= TAM; i++)
		{
			if(i != k)
			{
				productoria *= (x_prima - x[i])/(x[k] - x[i]);
			}
		}
		sumatoria += (y[k] * productoria); 
	}
	
	return sumatoria;
}
