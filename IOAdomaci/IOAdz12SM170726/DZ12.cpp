#include<stdio.h>
#include<iostream>

using namespace std;

int binaryToDecimal(int *Ar) {
	int dec_value = 0;
	int base = 1;
	//duzina -1
	for (int i = 30; i >= 0; i--) {
		int last_digit = Ar[i];
		dec_value += last_digit * base;
		base = base * 2;
	}
	return dec_value;
}
int* sift(int *P) {
	int  i, temp;
	temp = P[31 - 1];
	for (i = 31 - 1; i >= 0; i--) {
		P[i + 1] = P[i];
	}
	P[0] = temp;
	return P;
}
bool Autokorelacija(int *X) {
	int *A = new int[31];
	for (int i = 0; i < 31; i++) {
		A[i] = X[i];
	}
	int l = 0;
	bool UOpsegu=false;
	while (UOpsegu!=true && l<31) {
		A = sift(A);
		l++;
		int brRaz = 0;
		int brIst = 0;
		for (int i = 0; i < 31; i++) {
			if (A[i] == X[i]) {
				brIst++;
			}
			else {
				brRaz++;
			}
		}
		int Rez = brIst - brRaz;
		if (Rez<6 && Rez>-4) {
			UOpsegu = true;
		}
		else {
			UOpsegu = false;
		}
	}
	return UOpsegu;
}
bool Kroskorelacija(int *A) {
	//Pocetni dobijeni niz
	int X[31] = { 1,0,1,0, 0,0,0,1, 0,0,0,1, 1,0,1,1, 0,0,0,0, 1,1,0,0, 1,1,1,0, 0,1,1 };
	int *X0 = new int[31];
	int *B = new int[31];
	for (int i = 0; i < 31; i++) {
		X0[i] = X[i];
	}
	int l = 0;
	bool UOpsegu = false;
	while (UOpsegu != true && l < 31) {
		B = sift(X0);
		l++;
		int brRaz = 0;
		int brIst = 0;
		for (int i = 0; i < 31; i++) {
			if (A[i] == B[i]) {
				brIst++;
			}
			else {
				brRaz++;
			}
		}
		int Rez = brIst - brRaz;
		if (Rez<6 && Rez>-4) {
			UOpsegu = true;
		}
		else {
			UOpsegu = false;
		}
}
	return UOpsegu;
}
int* ispis(int *P) {
	int *B = new int[31];
	for (int i = 0; i < 31; i++) {
		B[i] = 0;
	}
	for (int i = 0; i < 15; i++) {
		B[P[i] - 1] = 1;
	}
	//for (int i = 0; i < 31; i++) {
		//if (i % 31 == 0)printf("\n");
		//printf("%3d", B[i]);
	//}
	return B;
}
int main() {
	int n = 31;
	int k = 15;
	int i, j;
	bool b;
	int *Cilj = new int[31];
	int *P = new int[k];
	for (i = 0; i < k; i++)
		P[i] = i + 1;
	std::cout << endl << "Pocinjem sa racunanjem svih kombinacija :" << endl;
	do {
		int *Z = new int[31];
		Z = ispis(P);
		bool prvi = false;
		bool drugi = false;

		prvi = Kroskorelacija(Z);
		drugi = Autokorelacija(Z);

		if (prvi == true && drugi == true) {
			for (int i = 0; i < 31; i++) {
				Cilj[i] = Z[i];
			//	std::cout << Z[i] << " ";
			}
			//std::cout << endl;
		}

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
	std::cout << endl << "Ciljni rezulta je " << endl;
	for (int i = 0; i < 31; i++) {
		std::cout << Cilj[i] << " ";
	}
	std::cout << endl;
	std::cout << endl << "Ciljni decimalan je" << endl;
	std::cout << binaryToDecimal(Cilj);

	std::system("pause");
	return 0;
}