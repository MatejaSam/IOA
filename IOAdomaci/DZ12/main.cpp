#include<stdio.h>
#include<time.h>
#include<iostream>
#include<bitset>

using namespace std;

int kroskorelacija(int nulti, int prvi) {
	bitset<32> X0 = nulti;
	bitset<32> X1 = prvi;
	int iste = 0;
	int razlicite = 0;

	for (int i = 30; i >= 0; i--) {
		if (X0[i] == X1[i]) iste++;
		else razlicite++;}

	return (iste - razlicite);}




void algoritam(int* raspored,int k) {

	bitset<32>X0global = 1351452275;
	bitset<32>Xglobal = 0;
	
	for (int i = 0; i < k; i++) {
		Xglobal[raspored[i] - 1] = 1;}

		bitset<32>X0 = X0global;
		bitset<32>X = Xglobal;


		for (int m = 0; m < 31; m++) {
			int kor = kroskorelacija((int)(Xglobal.to_ullong()), (int)(X0.to_ullong()));
			int ar = kroskorelacija((int)(Xglobal.to_ullong()), (int)(X.to_ullong()));
			if (m == 0)ar = 0;

			bool flag = true;
			if (!(kor > -4 && kor < 6))flag = false;
			if (!(ar > -18 && ar < 12))flag = false;

			if (flag == false)break;
			else {
				if (m == 30) { cout << "Pronadjen broj "; cout << (int)(Xglobal.to_ullong()); cout << " ";
				for (int i = 30; i >= 0; i--)cout << Xglobal[i] << " ";

				printf("\n"); }
				int p1 = X0[0];
				int p2 = X[0];

				X0 = ((int)(X0.to_ullong()) >> 1);
				X = ((int)(X.to_ullong()) >> 1);
				X0[30] = p1;
				X[30] = p2;
			}
		}



}



int main() {
	int i, j;
	int n = 31;
	int k = 15;
	bool b;
	int *P = new int[k];
	int cnt = 0;

	for (i = 0; i < k; i++)
		P[i] = i + 1;
	
	
	do {
		
		algoritam(P, k);

		b = false;
		for (i = k - 1; i >= 0; i--) {
			if (P[i] < n - k + 1 + i) {
				P[i]++;
				for (j = i + 1; j < k; j++)
					P[j] = P[j - 1] + 1;
				b = true;
				break;
			}
		}

	} while (b);

	if (P != NULL) delete[] P;
}