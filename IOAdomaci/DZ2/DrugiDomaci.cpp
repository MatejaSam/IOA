#include <stdio.h>
#include <iostream>
#include <algorithm>
#include <cstdlib>
#include <cmath>

using namespace std;


void inicijalizacija(int broj, double** rastojanja, double* x, double* y) {

	for (int i = 0; i < broj; i++) {
		for (int j = 0; j < broj; j++) {
			rastojanja[i][j] = 0;
		}
	}



	for (int i = 0; i < broj; i++) {
		for (int j = i+1; j < broj; j++) {

			if (i != j && rastojanja[i][j]==0) {
				double rx = (x[i] - x[j])*(x[i] - x[j]);
				double ry = (y[i] - y[j])*(y[i] - y[j]);
				rastojanja[i][j] = sqrt(rx + ry);
				rastojanja[j][i] = sqrt(rx + ry);}

		}
	}
}


double rastojanje(int broj, double** rastojanja,int *niz) {
	double ras = 0;

	for (int i = 0; i < broj-1; i++) {
		ras+= rastojanja[niz[i]][niz[i+1]];}

	return ras;
}

bool next_permutation(int N, int *P) {

	int s;
	int *first = &P[0];
	int *last = &P[N - 1];
	int *k = last - 1;
	int *l = last;

	while (k > first) {

		if (*k < *(k + 1)) break;
		
		k--;}

	if (*k > *(k + 1)) return 0;

	while (l > k) {

		if (*l > *k)break;
		
		l--;}

	s = *k;
	*k = *l;
	*l = s;

	first = k + 1;

	while (first < last) {
		s = *first;
		*first = *last;
		*last = s;

		first++;
		last--;}

	return l;
}


int main() {

	double x[12] = {62.0,57.5,51.7,67.9,57.7,54.2,46.0,34.7,45.7,34.7,28.4,33.4};
	double y[12] = {58.4,56.0,56.0,19.6,42.1,29.1,45.1,45.1,25.1,26.4,31.7,60.5};


	int broj= 0;
	double min = 0; 
	

	int niz[12] = { 0,1,2,3,4,5,6,7,8,9,10,11};
	int minniz[12] = { 0,1,2,3,4,5,6,7,8,9,10,11 };

	while (broj != 8 && broj != 12) {
		cout << "Unesite broj rupa 8 ili 12"<<endl;
		cin >> broj;
	};

	double** rastojanja = new double*[broj];
	for (int i = 0; i < broj; ++i)
		rastojanja[i] = new double[broj];

	inicijalizacija(broj, rastojanja, x, y);

	min=rastojanje(broj,rastojanja,niz);

	while (next_permutation(broj, niz)) {
		double ras= rastojanje(broj, rastojanja, niz);
		if (ras < min) {
			min = ras;
			for (int i = 0; i < broj; i++)minniz[i] = niz[i];
		}
	}


	cout << endl<< "Duzina najkraceg puta:  ";
	cout << min<<endl<<endl;

	cout << "Putanja:  ";
	for (int i = 0; i < broj; i++)printf("%4d", minniz[i]+1);
	cout << endl;

	delete []rastojanja;

	return 0;
}
