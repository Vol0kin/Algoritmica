#include <iostream>
#include <cstdlib>
#include <ctime>
#include <cmath>

double exponenciacionSecuencial(double x, int n) {
	double result = 1;

	for (int i = 0; i < n; i++)
		result *= x;
	
	return result;
}

double exponenciacionDyV(double x, int n) {
	if (n == 0)
		return 1;
	else if (n == 1)
		return x;
	else {
		if (n % 2 == 0)
			return exponenciacionDyV(x*x, n / 2);
		else
			return x*exponenciacionDyV(x*x, (n-1) / 2);
	}
}

//#define EXP_SEC
#define EXP_DYV
//#define EXP_POW

int main(int argc, char *argv[]) {
	if (argc != 3) {
		std::cerr << "Error, se esperaban 2 argumentos: x, n de forma que x^n" << std::endl;
		return -1;
	}

	int n;
	double x, result, t1, t2, t_total;

	x = atof(argv[1]);
	n = atoi(argv[2]);
	
	t1 = clock();

	#ifdef EXP_SEC
	result = exponenciacionSecuencial(x, n);
	#endif
	#ifdef EXP_DYV
	result = exponenciacionDyV(x, n);
	#endif
	#ifdef EXP_POW
	result = pow(x, n);
	#endif
	
	t2 = clock();

	t_total = (double) (t2 - t1) / (CLOCKS_PER_SEC);

	std::cout << n << ' ' << t_total << std::endl;
	//std::cout << result << std::endl;

	return 0;
}