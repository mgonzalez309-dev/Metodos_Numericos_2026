#include <iostream>
#include <math.h>
#include <fstream>
#include <cstdlib>

#define TAM 5
using namespace std;


double fx(double x);
double Pn(double x_prima, double x[TAM + 1], double y[TAM + 1]);

int main(int argc, char *argv[]) {
	
	double x[TAM + 1], y[TAM + 1];
	double x_prima = 0, y_prima;
	
	x_prima = 500;
	
	x[0] = -260.15;
	x[1] = -200;
	x[2] = -100;				
	x[3] = 0;
	x[4] = 100;
	x[5] = 300;
	y[0] = 0.1;
	y[1] = 0.45;
	y[2] = 0.699;
	y[3] = 0.87;
	y[4] = 0.941;
	y[5] = 1.04;
	
	
	y_prima = Pn(x_prima, x, y);
	printf("Y_prima: %0.3lf", y_prima);
	
	ofstream dataFile("data.txt");
	
	for (int i = 0; i <= TAM; i++) {
		dataFile << x[i] << " " << y[i] << endl;
	}
	
	dataFile << x_prima << " " << y_prima << endl;
	
	dataFile.close();
	
	ofstream gnuplotScript("plot_script.gp");
	gnuplotScript << "set title 'Interpolación de Lagrange'\n";
	gnuplotScript << "set xlabel 'Temperatura [C]'\n";
	gnuplotScript << "set ylabel 'Calor específico [kJ/kg°C]'\n";
	gnuplotScript << "set grid\n";
	gnuplotScript << "plot 'data.txt' using 1:2 with linespoints title 'Puntos y valor interpolado'\n";
	gnuplotScript.close();
	
	// Ejecutar gnuplot
	// system("gnuplot -p plot_script.gp"); // opcional, requiere gnuplot instalado
	
	return 0;
}


double Pn(double x_prima, double x[TAM + 1], double y[TAM + 1])
{
	double productoria = 1, sumatoria = 0;
	
	for(int k = 0; k <= TAM; k++)
	{
		for(int i = 0; i <= TAM; i++)
		{
			if(i != k)
			{
				productoria *= (x_prima - x[i])/(x[k] - x[i]);
			}
		}
		sumatoria += (y[k] * productoria); 
		productoria = 1;
	}
	
	return sumatoria;
}
