//==1.1	Kao racunanuje brzine izvrsavanja racunara-glupost
#include<stdio.h>
#include<time.h>
#include<iostream>

using namespace std;

double F(double a, double b) {
	return a + b;
}
int main(void) {
	double x, eval;
	double max = 7e7;//promenjeno sa 7e9

	time_t t1, t2;
	time(&t1);

	for (int x = 0; x < max; x = x + 1.0)
		eval = F(x, x);

	time(&t2);

	printf("%5.5e\n", (t2 - t1) / max);

	system("pause");
	return 0;
}
//-----------------------------------------------------------
//==1.2	Realni broj racunanje
#include<stdio.h>
#include<iostream>
#include<complex>


using namespace std;

void main() {

	complex<double> i;
	i.real(0.0);
	i.imag(1.0);

	complex<double> z1, z2, add, prod, div;
	double re, im;

	printf("Unesi prvi broj (realno, imaginarno: \n");
	scanf_s("%lf %lf", &re, &im);

	z1.real(re);
	z1.imag(im);

	printf("Unesi drugi broj (realno, imaginarno: \n");
	scanf_s("%lf %lf", &re, &im);

	z2.real(re);
	z2.imag(im);

	add = z1 + z2;
	prod = z1 * z2;
	div = z1 / z2;

	printf("zbir : (%.2f %.2f )\n", real(add), imag(add));
	printf("proizvodi : (%.2f %.2f )\n", real(prod), imag(prod));
	printf("kolicnik : (%.2f %.2f )\n", real(div), imag(div));

	system("pause");
}
//-----------------------------------------------------------
//==1.3	Rad sa fajlovima - Ispis Rozenbrok
#include<stdio.h>
#include<iostream>
#include<fstream>

using namespace std;

double fun(double x1, double x2) {
	return pow((1.0 - x1), 2) + 100.0*pow((x1 - x2 * x2), 2.0);
}

void main() {
	ofstream file;
	file.open("Rozenbrok.txt");
	for (double x1 = -2.0; x1 <= 2.0; x1 += 0.01) {
		for (double x2 = -2.0; x2 <= 2.0; x2 += 0.01) {
			double y = fun(x1, x2);
			//printf(out, "%.5f %.5f %.5f\n", x1, x2, y);
			file << x1 << " " << x2 << " " << y << " ";
		}
	}
	file.close();
	system("pause");
}
//-----------------------------------------------------------
//PDF IOA2
//==2.1 Varijacije sa ponavljanjem
#include<stdio.h>
#include<iostream>

using namespace std;

void variations_with_repetition(int n, int k) {
	//k-duzinan niza
	//n-do kog broja
	int q;
	int *P = new int[k];
	for (int i = 0; i < k; i++)
		P[i] = 0;

	do {
		for (int i = 0; i < k; i++)
			printf("%5d ", P[i] + 1);
		printf("\n");

		q = k - 1;
		while (q >= 0) {
			P[q]++;
			if (P[q] == n) {
				P[q] = 0;
				q--;
			}
			else break;
		}
	} while (q >= 0);
	delete[] P;
}
int main() {


	variations_with_repetition(10, 3);

	system("pause");
}
//-----------------------------------------------------------
//==3.2 Random broj
#include <random>
#include <iostream>
#include<stdio.h>


void combinations_without_repetition(int n, int k) {
	int i, j;
	bool b;
	int *P = new int[k];

	for (i = 0; i < k; i++)
		P[i] = i + 1;


	do {
		for (i = 0; i < k; i++)
			printf("%3d ", P[i]);
		printf("\n");
		b = false;
		for (i = k - 1; i >= 0; i--) {
			if (P[i] < n - k + 1 + i) {
				P[i]++;
				for (j = i+1; j < k; j++)
					P[j] = P[j - 1] + 1;
				b = true;
				break;
			}
		}

	} while (b);

	if (P != NULL) delete[] P;
}



int main() {

	combinations_without_repetition(5, 5);
	system("pause");

}
//-----------------------------------------------------------
//==2.3 Niz permutacija sa mogucnoscu uzimanja svake pojedinacno
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
void Permutacije() {
	int N = 5;//opseg brojeva tj do kog broja
	int* P = new int[N];

	int pom = 0;


	for (int i = 0; i < N; i++)
		P[i] = i + 1;
	do {
		for (int i = 0; i < N; i++)
			cout << P[i];
		cout << endl;
		pom++;
	} while (next_premutation(N, P));
	delete[] P;

	cout << endl;
	cout << "Broj permutacija";
	cout << pom;

}

int main() {


	Permutacije();

	system("pause");
}
//-----------------------------------------------------------
//Iz IOA PDF 3
//==3.1 Pravljenje stabla 
//fali sta da se promeni

#include <stdio.h>
#include <iostream>

using namespace std;
void SequenceToSpaningTree(int*P, int len, int *T) {

	int i, j, q = 0;
	int n = len + 2;
	int * V = new int[n];

	for (i = 0; i < n; i++)
		V[i] = 0;
	for (i = 0; i < len; i++)
		V[P[i] - 1] += 1;
	for (i = 0; i < len; i++) {
		for (j = 0; j < n; j++) {

			if (V[j] == 0) {
				V[j] = -1;
				T[q++] = j + 1;
				T[q++] = P[i];
				V[P[i] - 1] --;
				break;
			}
		}
	}
	j = 0;
	for (i = 0; i < n; i++) {
		if (V[i] == 0 && j == 0) {
			T[q++] = i + 1;
			j++;
		}
		else if (V[i] == 0 && j == 1) {
			T[q++] = i + 1;
			break;
		}

	}
	delete[] V;

}
void Stablo() {
	int P[] = { 1,2,2 };
	int len = sizeof(P) / sizeof(P[0]);

	int *T = new int[2 * (len + 1)];
	SequenceToSpaningTree(P, len, T);

	for (int i = 0; i < 2 * (len + 1); i++) {
		cout << " " << T[i];
		if ((i + 1) % 2 == 0 && i < 2 * len)
			cout << " - ";
	}
	cout << endl;

	delete[] T;
}
void main() {

	Stablo();

	system("pause");
}
//-----------------------------------------------------------
//==3.2 Particija prirodnih brojeva
#include <random>
#include <iostream>
#include<stdio.h>

bool next_partition(int *p, int n) {
	int k, i;
	int q = 0;
	if (p[0] == 0) {
		p[0] = n;
		return true;
	}
	else {
		for (int i = 0; i < n; i++) {
			if (p[i] != 0)k = i;
			else break;
		}
	}
	while (k >= 0 && p[k] == 1) {
		q++; k--;
	}
	if (k < 0)return false;
	p[k]--;
	q++;

	while (q > p[k]) {
		p[k + 1] = p[k];
		q = q - p[k];
		k++;
	}
	p[k + 1] = q;
	k++;
	for (i = k + 1; i < n; i++)
		p[i] = 0;

	return true;
}
void drvier_next_partition(void) {
	int n = 7;
	int *p = new int[n];

	for (int i = 0; i < n; i++) {
		p[i] = 0;
	}

	while (next_partition(p, n)) {
		for (int i = 0; i < n && p[i]>0; i++)
			printf("%2d ", p[i]);
		printf("\n");
	}
	delete[]p;
}


int main() {
	drvier_next_partition();

	system("pause");

}
//-----------------------------------------------------------
//==3.2 Particija prirodnih brojeva
#include <random>
#include <iostream>
#include<stdio.h>

bool next_partition_of_set(int *a, int n) {
	int  j;
	int* b = new int[n];

	for (j = 0; j < n; j++) {
		b[j] = j == 0 ? 0 : std::max(b[j - 1], a[j - 1] + 1);
	}
	for (j = n - 1; j >= 0; j--) {
		if (a[j] < b[j]) {
			a[j]++;
			break;
		}
		else a[j] = 0;
	}
	if (j == -1) {
		return false;
	}
	delete[] b;
	return true;
}
void driver_next_partition_of_set() {
	int n = 4;
	int * a = new int[n];
	int i;
	for (i = 0; i < n; i++) {
		a[i] = 0;
	}
	do {
		for (i = 0; i < n; i++)
			printf("%2d ", a[i]);
			printf("\n");
	} while (next_partition_of_set(a, n));

	delete[] a;
}

int main() {
	driver_next_partition_of_set();

	system("pause");

}
//-----------------------------------------------------------
//random
#include <random>
#include <iostream>

int main(){
    std::random_device rd;
    std::mt19937 mt(rd());

    std::uniform_real_distribution<double> random_float(1.0,10.0);

    for(int i=0;i<16;++i)
        std::cout << random_float(mt)<<"\n";


        std::uniform_real_distribution<int> random_int(1,5);

    for(int i=0;i<16;++i)
        std::cout << random_float(mt)<<"\n";
    
}

//-----------------------------------------------------------
//IOA4============
//==4.0
#include <random>
#include <iostream>
#include<stdio.h>
#include<time.h>
using namespace std;
void driver_random_variation(void) {
	srand((unsigned int)time(NULL));

	int n = 10;
	int k = 4;
	int s = 15;

	int *r = new int[k];

	for (int i = 0; i < s; i++) {
		for (int j = 0; j < s; j++) {
			r[j] = radnom_int(0, n - 1);
			printf("%2d ", r[j]);
		}
		printf("\n");
	}
	delete[] r;
}
void driver_random_vector(void) {
	srand((unsigned int)time(NULL));

	double xmin = -1.0;
	double xmax = +1.0;
	int k = 4;
	int s = 15;

	double * r = new double[k];

	for (int i = 0; i < s; i++) {
		for (int j = 0; j < k; j++) {
			r[j] = radnom_float(xmin, xmax);
			printf("%2.3f ", r[j]);
		}
		printf("\n");
	}
	delete[] r;
}
int main() {
	driver_random_vector();

	system("pause");

}
//-----------------------------------------------------------
//==4.1 
#include <random>
#include <iostream>
#include<stdio.h>
#include<time.h>
using namespace std;
void random_combination(int n, int k, int*P) {
	if (k < n) return;

	int i, j, r, c;
	int *Q = new int[n];

	for (i = 0; i < k; i++)
		Q[i] = 0;
	for (i = 0; i < k; i++) {
		r = random_int(0, n - 1 - i);
		c = 0;
		for (j = 0; j < n; j++) {
			if (Q[i] == 0) {
				if (r == c) {
					Q[j]++; break;
				}
				c++;
			}
		}
	}
	c = 0;
	for (i = 0; i < n; i++) {
		if (Q[i] == 1) {
			P[c] = i + 1;
			c++;
		}
	}
	delete[] Q;
}
void driver_random_combination(void) {

	int n = 5;
	int k = 3;
	int *P = new int[k];
	for (int i = 0; i < 100; i++) {
		random_combination(n, k, P);
		for (i = 0; i < k; i++)
			printf("%2d ", P[i]);
		printf("\n");
	}
	delete[] P;
}
int main() {
	driver_random_combination();

	system("pause");

}
//-----------------------------------------------------------
//4.2-------------------
//random permutatuin
#include <random>
#include <iostream>
#include<stdio.h>
#include<time.h>
using namespace std;


void random_permutation(int n, int*p) {
	int i, j, s;
	for (i = n - 1; i > 0; i--) {
		j = random_int(0, i);
		if (i != j) {
			s = p[i];
			p[i] = p[j];
			p[j] = s;
		}
	}
}
void drvier_next_permutation(void) {
	int n = 3;
	int * p = new int[n];
	int * s = new int[n];
	int T = 1000;

	for (int i = 0; i < n; i++) {
		p[i] = i + 1;
		s[i] = 0;
	}

	for (int i = 0; i < T; i++) {
		random_permutation(n, p);

		for (int j = 0; j < n; j++)
			printf("%2d ", p[j]);
		printf("\n");

		s[p[0] - 1]++;
	}
	for (int j = 0; i < n; i++)
		printf("%2.5f \n ", s[i] * 1.0 / T);

	delete[] p;
	delete[] s;

}
int main() {
	drvier_next_permutation();

	system("pause");

}
