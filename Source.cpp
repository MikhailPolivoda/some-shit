#include <iostream>
#include <vector>
#include <cmath>

using namespace std;

const int N = 5;
const double dx = 0.01;

vector<double> tridiagonal_matrix_algorithm(const vector<double>& y, const vector<double>& h) { //метод прогонки
	vector<vector<double>> matrixa; // матрица системы уравнений
	matrixa.assign(N - 2, vector<double>(N - 2));
	vector<double>matrixb(N - 2); // столбец свободных членов
	double temp = 0.0;
	vector<double> a(N - 2); 
	vector<double> B(N - 2); 
	vector<double> C(N - 2);
	// создание трехдиагональной матрицы
	for (size_t i = 0; i < N - 2; ++i) {
		if (i != N - 3) {
			matrixa[i][i] = 2 * (h[i]+h[i + 1]);
			matrixa[i][i + 1] = h[i + 1] ;
			matrixa[i + 1][i] = h[i + 1];
		}
		else {
			matrixa[i][i] = 2 * (h[i] + h[i + 1]);
		}
		matrixb[i] = 3 * (((y[i + 2] - y[i + 1]) / h[i + 1]) - ((y[i + 1] - y[i]) / h[i]));
	}
	// прямой ход
	temp = matrixa[0][0];
	a[0] = -matrixa[0][1] / temp;
	B[0] = matrixb[0] / temp;
	for (int i = 1; i < N - 3; i++) {
		temp = matrixa[i][i] + matrixa[i][i - 1] * a[i - 1];
		a[i] = -matrixa[i][i + 1] / temp;
		B[i] = (matrixb[i] - matrixa[i][i - 1] * B[i - 1]) / temp;
	}
	// обратный ход
	C[N-3] = (matrixb[N-3] - matrixa[N-3][N-3 - 1] * B[N-3 - 1]) / (matrixa[N-3][N-3] + matrixa[N-3][N-3 - 1] * a[N-3 - 1]);
	for (int i = N-3 - 1; i >= 0; i--) {
		C[i] = a[i] * C[i + 1] + B[i];
	}

	return C;
}


double SpliceFunction(double x, double a, double b, double c, double d){

	return a + (b * x) + (c * (x * x)) + (d * (x * x * x));
}

int main() {
	vector<double>x;
	vector<double>y;
	vector<double> h;
	int number = 0;
	for (size_t i = 0; i < N; ++i) {
		cin >> number;
		x.push_back(number);
	}

	for (size_t i = 0; i < N; ++i) {
		if (x[i] != x[N-1]) {
			h.push_back(x[i + 1] - x[i]);
		}
		cin >> number;
		y.push_back(number);
	}

	vector <double> c = tridiagonal_matrix_algorithm(y, h);

	c.resize(N);
	for (size_t i = N - 2; i > 0; --i) {
		c[i] = c[i - 1];
	}
	c[0] = 0;
	

	vector <double> a = y;
	vector <double> b(N - 1);
	vector <double> d(N - 1);

	//нахождение b и d коэффициентов
	for (size_t i = 0; i < N - 1; ++i) {
		b[i] = ((y[i + 1] - y[i]) / h[i]) - (c[i + 1] + (2 * c[i])) * (h[i] / 3);
		d[i] = (c[i + 1] - c[i]) / (3 * h[i]);
	}
	// вектора для построения графиков
	vector<double>x1;
	vector<double>y1;
	vector<double>x2;
	vector<double>y2;
	vector<double>x3;
	vector<double>y3;
	vector<double>x4;
	vector<double>y4;

	for (size_t index = 0; index < x.size() - 1; ++index) {
		if (index == 0) {
			for (double i = x[index]; i < x[index + 1]; i += dx) {
				x1.push_back(i);
				y1.push_back(SpliceFunction(i, a[index], b[index], c[index], d[index]));
			}
		}

		if (index == 1) {
			for (double i = x[index]; i < x[index + 1]; i += dx) {
				x2.push_back(i);
				y2.push_back(SpliceFunction(i, a[index], b[index], c[index], d[index]));
			}
		}

		if (index == 2) {
			for (double i = x[index]; i < x[index + 1]; i += dx) {
				x3.push_back(i);
				y3.push_back(SpliceFunction(i, a[index], b[index], c[index], d[index]));
			}
		}

		if (index == 3) {
			for (double i = x[index]; i < x[index + 1]; i += dx) {
				x4.push_back(i);
				y4.push_back(SpliceFunction(i, a[index], b[index], c[index], d[index]));
			}
		}
	}
	
	return 0;
}
