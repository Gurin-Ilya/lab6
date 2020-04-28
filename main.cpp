#include <iostream>
#include <cmath>
#include <fstream>

using namespace std;

double f(double x1, double x2) {	
	return (-((-pow(x1, 2) / 3) - (x1 * x2 / 6) + (127 * x1 / 6) - (pow(x2, 2) / 3) + (91 * x2 / 6) - (239 / 2)));// -f
}

double slidingWindowX1(double x, double xconst, double h = 1) {
	while (true) {
		if ((f(x - h, xconst) > f(x, xconst)) && (f(x + h, xconst) > f(x, xconst)))
			return x;
		else if (f(x - h, xconst) > f(x + h, xconst))
			x = x + h / 2;
		else
			x = x - h / 2;
	}
}
double slidingWindowX2(double x, double xconst, double h = 1) {
	while (true) {
		if ((f(xconst, x - h) > f(xconst, x)) && (f(xconst, x + h) > f(xconst, x)))
			return x;
		else if (f(xconst, x -h) > f(xconst, x +h))
			x = x + h / 2;
		else
			x = x - h / 2;
	}
}

double quadraticInterpolationX1(double xmin, double xconst, double h = 1, double eps = 0.01) {
	double F;
	double fmin;
	double x1, x2, x3, X;
	int k = 1;
	do {
		if (k == 1) {
			fmin = f(xmin, xconst);
			x3 = xmin + h;
			x1 = xmin - h;
			x2 = xmin;
		}
		//Сужение интервала
		else {
			if (x2 > X) {
				x3 = x2;
			}
			else if (x2 == X) {
			}
			else {
				x1 = x2;
			}
			xmin = X;
		}
		double f1 = f(x1, xconst);
		double f2 = f(x2, xconst);
		double f3 = f(x3, xconst);
		double a1 = (f2 - f1) / (x2 - x1);
		double a2 = ((f3 - f1) / (x3 - x1) - a1) / (x3 - x2);
		X = ((x2 + x1) / 2) - a1 / (2 * a2);
		/*
		X = ((((pow(x2, 2) - pow(x3, 2)) * fmin) +
			((pow(x3, 2) - pow(xmin, 2)) * f2) +
			((pow(xmin, 2) - pow(x2, 2)) * f3)) /
			((x2 - x3) * fmin + (x3 - xmin) * f2 + (xmin - x2) * f3));//avarage x
		*/
		F = f(X, xconst);
		k++;
	} while ((abs(fmin - F) > eps) && (k < 25));
	if (k == 25)
		cout << "k = 25" << endl;
	return X;
}

double quadraticInterpolationX2(double xmin, double xconst, double h = 1, double eps = 0.01) {
	double F;
	double fmin;
	double x1, x2, x3, X;
	int k = 1;
	do {
		if (k == 1) {
			fmin = f(xconst,xmin);
			x3 = xmin + h;
			x1 = xmin - h;
			x2 = xmin;
		}
		//Сужение интервала
		else {
			if (x2 > X) {
				x3 = x2;
			}
			else if (x2 == X) {
			}
			else {
				x1 = x2;
			}
			xmin = X;
		}
		double f1 = f(xconst,x1);
		double f2 = f(xconst,x2);
		double f3 = f(xconst,x3);
		double a1 = (f2 - f1) / (x2 - x1);
		double a2 = ((f3 - f1) / (x3 - x1) - a1) / (x3 - x2);
		X = ((x2 + x1) / 2) - a1 / (2 * a2);
		F = f(xconst,X);
		k++;
	} while ((abs(fmin - F) > eps) && (k < 25));
	if (k == 25)
		cout << "k = 25" << endl;
	return X;
}


int main()
{
	ofstream fout;
	ofstream fout1;
	fout.open("Track.txt");
	cout << "Coordinate descent method:" << endl;
	double epsF = 0.001;
	double epsX = 0.01;
	double x1 = 9, x2 = 25;
	fout << x1 << "\t" << x2 << endl;

	//cout << x1 << "\t" << x2 << endl;
	//cout << "f(x1,x2) = " << (-f(x1, x2)) << endl << endl;

	double temp1, temp2;
	int i = 0;
	do {
		temp1 = x1;
		temp2 = x2;
		x1 = quadraticInterpolationX1(slidingWindowX1(x1, x2), x2);
		fout << x1 << "\t" << x2 << endl;

		//cout << x1 << "\t" << x2 << endl;
		//cout << "f(x1,x2) = " << (-f(x1, x2)) << endl << endl;
		
		x2 = quadraticInterpolationX2(slidingWindowX2(x2, x1), x1);

		//cout << x1 << "\t" << x2 << endl;
		//cout << "f(x1,x2) = " << (-f(x1, x2)) << endl << endl;

		fout << x1 << "\t" << x2 << endl;
		i++;
	} while (((abs(f(x1, x2) - f(temp1, temp2)) > epsF) || (abs(x1 - temp1) > epsX) || (abs(x2 - temp2) > epsX)) && (i < 30));
	cout << "iterations = " << i<<endl;
	cout << "x1 = " << x1<<endl;
	cout << "x2 = " << x2 << endl;
	fout.close();
	fout1.close();
	return 0;
}
