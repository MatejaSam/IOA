#include <iostream>
#include <stdio.h>
using namespace std;

int main() {


	for (int x1 = 1; x1 < 709; x1++) {
		for (int x2 = x1; x2 < 709; x2++) {
			for (int x3 = x2; x3 < 709; x3++) {

				int x4 = 711 - x1 - x2 - x3;

				long long int proizvod = x1 * x2 * x3 * x4;

				if (proizvod == 711e6) {
					if (x1 <= x2 && x2 <= x3 && x3<= x4) {
						cout << "{";
						cout << float(x1) / float(100);
						cout << " , ";
						cout << float(x2) / float(100);
						cout << " , ";
						cout << float(x3) / float(100);
						cout << " , ";
						cout << float(x4) / float(100);
						cout << "}";
						cout << endl;
					}
				}


			}
		}
	}

	return 0;
}