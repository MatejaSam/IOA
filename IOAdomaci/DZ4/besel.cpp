#include <cmath>
#include <iostream>
#include <math.h>
#include <iomanip>

using namespace std;


double f(int n,double x) {
	double pi = 3.141592653589793;
	double f = sqrt(pi / (2 * x)) * std::sph_bessel(n, x);
	return f;
}




int main()
{	
	int i = 0;
	cout << "Za red funckije n = 1" << endl << endl;
	do {
		double interval[8] = { 4.0,6.0,6.0,8.0,5.0,7.0,7.0,10.0};
		double interval1[8] = { 4.0,6.0,6.0,8.0,5.0,7.0,7.0,10.0 };
		int n[2] = { 1,2 };
		
		
		do {

			double a = interval[i];
			double b = interval[i + 1];

			double m = 0.5*(a + b);

			if (f(n[i / 4], a)*f(n[i / 4], m) > 0)interval[i] = m;
			else interval[i + 1] = m;


		} while (abs(interval[i] - interval[i + 1]) > 0.000000000001);

		

		cout << fixed;
		cout << setprecision(12);
		cout << "x = "<<((interval[i] + interval[i+1]) / 2)<<endl;
		if(i==2)cout <<endl<<endl<< "Za red funckije n = 2" << endl << endl;


	i+=2;
	} while (i<8);

	return 0;

}
