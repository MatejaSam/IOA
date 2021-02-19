#include <stdio.h>
#include <iostream>

using namespace std;
int next_premutation(const int N, int *P) {
	int s;
	int * first = &P[0];
	int * last = &P[N - 1];
	int * k = last - 1;
	int * l = last;
	while (k > first) {
		if (*k < *(k + 1)) {
			break;
		}
		k--;
	}
	if (*k > *(k + 1)) {
		return 0;
	}
	while (l > k) {
		if (*l > *k) {
			break;
		}
		l--;
	}
	s = *k;
	*k = *l;
	*l = s;

	first = k + 1;
	while (first < last) {
		s = *first;
		*first = *last;
		*last = s;

		first++;
		last--;
	}
	return 1;
}
//gotov deo za permutacije
//deo za spaning tree
void SequenceToSpaningTree(int*P, int len, int *T) {
	int i, j, q = 0;
	int n = len + 2;
	int * V = new int[n];

	for (i = 0; i < n; i++)
		V[i] = 0;
	for (i = 0; i < len; i++)
		V[P[i]] +=1 ;
	for (i = 0; i < len; i++) {
		for (j = 0; j < n; j++) {

			if (V[j] == 0) {
				V[j] = -1;
				T[q++] = j;
				T[q++] = P[i];
				V[P[i]] --;
				break;
			}
		}
	}
	j = 0;
	for (i = 0; i < n; i++) {
		if (V[i] == 0 && j == 0) {
			T[q++] = i ;
			j++;
		}
		else if (V[i] == 0 && j == 1) {
			T[q++] = i ;
			break;
		}
	}
	delete[] V;
}
void main() {
	//matrica sa gradovima
	int Gradovi[10][10] = {
		{ 0  ,  374 , 200,  223 , 108 , 178 , 252  ,285,  240 , 356} ,
		{ 374 , 0  ,  255,  166 , 433,  199 , 135,  95,  136,  17 } ,
		{200 , 255 , 0,    128, 277 , 821  ,180 , 160 , 131 , 247 } ,
		{223 , 166  ,128 , 0  ,  430, 47  , 52 ,  84 ,  40  , 155 } ,
		{108 , 433 , 277,  430 , 0 ,   453  ,478 , 344, 389 , 423 } ,
		{178 , 199 , 821,  47 ,  453,  0 ,   91 ,  110 , 64  , 181 } ,
		{ 252 , 135 , 180 , 52 ,  478,  91  , 0  ,  114 , 83  , 117} ,
		{285 , 95 ,  160 , 84 ,  344 , 110 , 114,  0  ,  47 ,  78} ,
		{ 240 , 136,  131,  40 ,  389 , 64  , 83 ,  47 ,  0 ,   118} ,
		{ 356 , 17  , 247,  155,  423,  181 , 117  ,78  , 118, 0} ,
	};
	int zbir = 0; int cilj = 2000;//apsolutno veliki brojk kako bi bilo inizijalizovanu za dalju razmenu u ifu
	int N = 10;
	int* P = new int[N];
	int *z = new int[N];
	for (int i = 0; i < N; i++)
		P[i] = i ;//+1
	do {
		cout << "Permutacije : ";
		for (int i = 0; i < N; i++)
			cout << P[i]<<",";
		//stablo*
		cout << " Stablo : ";
		int len = 8;// sizeof(P) / sizeof(P[0]);
		int *T = new int[2 * (len + 1)];
		SequenceToSpaningTree(P, len, T);

		int *Pom = new int[2 * (len + 1)];
		//niz za pracenje
		int *Dup = new int[N];
		for (int i = 0; i < N; i++)
			Dup[i] = 0;//da ga napravi novi sa pocetnim rastojanjima
		//------
		for (int i = 0; i < 2 * (len + 1); i++) {//
			cout << T[i] << ",";
			Pom[i] = T[i];

			Dup[T[i]]++;//povecanje za duplikate

			if ((i + 1) % 2 == 0 && i < 2 * len)
				cout << " | ";
		}
		cout << endl;
		//dodatak za niz
		cout << " Niz pocetnih cena gradova : ";
		for (int i =0; i < 2 * (len + 1)-1; i+=2) {//
			cout << Gradovi[Pom[i]][Pom[i+1]] << ";";
			if (Dup[i]>=4) {
				zbir += (Dup[i]*100)-3;
			}
			else {
				zbir += Gradovi[Pom[i]][Pom[i + 1]];
			}
			if (zbir < cilj) {
				cilj = zbir;
				//zamena za niz putanja
				for (int i = 0; i < N; i++) {
					z[i] = T[i];//pomocni niz
				}
			}
		}
		//kraj dodatka za niz
		//Stablo kraj***********************************************************
		cout << endl;
	} while (next_premutation(N, P));
	//ispis pravog niza da je nesto jednako
	cout << endl;
	cout << "Najbolja dobijena distanca (putanja)";
	for (int i = 0; i < N; i++) {
		cout << z[i]<<",";
	}
	cout << "Vrednost te putanje je : ";
	cout << cilj;
	system("pause");
}


