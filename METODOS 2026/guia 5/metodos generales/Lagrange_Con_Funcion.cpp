
#include <iostream>
#include <math.h>

#define TAM 8 // a medida que toma grados mas altos, los errores se van reduciendo considerablemente
using namespace std;


double fx(double x);
double Pn(double x_prima, double x[TAM + 1], double y[TAM + 1]);

int main(int argc, char *argv[]) {
	
	double x[TAM + 1], y[TAM + 1];
	double x_prima = 0, error = 0;
	
	x_prima = 1.3;
	
	x[0] = 0;
	x[1] = 1;
	x[2] = 2;
	x[3] = 3;
	x[4] = 4;
	x[5] = 5;
	x[6] = 6;
	x[7] = 7;
	x[8] = 8;
	y[0] = fx(x[0]);
	y[1] = fx(x[1]);
	y[2] = fx(x[2]);
	y[3] = fx(x[3]);
	y[4] = fx(x[4]);
	y[5] = fx(x[5]);
	y[6] = fx(x[6]);
	y[7] = fx(x[7]);
	y[8] = fx(x[8]);
	
	
	printf("Y_prima: %0.3lf", Pn(x_prima, x, y));
	
	error = fabs(fx(x_prima) - Pn(x_prima, x, y));
	
	printf("\nError: %0.6lf", error);
	
	
	
	return 0;
}


double fx(double x)
{
	return (exp(-pow(x, 2))); 
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



