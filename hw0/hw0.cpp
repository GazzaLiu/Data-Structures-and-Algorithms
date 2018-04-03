#include <iostream>
#include <fstream>
using namespace std;

double** getIdentityMatrix (int size) {
	double **matrix = new double* [size];
	for (int i = 0; i < size; i++) {
		matrix[i] = new double[size];
		for (int j = 0; j < size; j++) {
			if (i == j) {
				matrix[i][j] = 1;
			}
			else {
				matrix[i][j] = 0;
			}
		}
	}
	return matrix;
}

/*void printMatrix (double** matrix) {
	for (int i = 0; i < size; i++) {
		for (int j = 0; j < size; j++) {
			
		}
	}
}*/

int main () {
	int size;
	int currentRow = 0;

	fstream fin("./input/input_200.txt");
	if (!fin) { 
		cout << "Cannot read file.\n" << endl; 
		return 0;
	}

	fin >> size;

	double **originMatrix = new double* [size];
	double **inverseMatrix = getIdentityMatrix(size);
	double **matrix = new double* [size];

	for (int i = 0; i < size; i++) {
		matrix[i] = new double[size];
		originMatrix[i] = new double[size];
		for (int j = 0; j < size; j++) {
			fin >> originMatrix[i][j];
			matrix[i][j] = originMatrix[i][j];
		}
	}

	while (currentRow < size) {
		double denominator = matrix[currentRow][currentRow];
		cout << currentRow << '\t' << denominator << '\t';
		for (int j = 0; j < size; j++) {
			matrix[currentRow][j] /= denominator;
			inverseMatrix[currentRow][j] /= denominator;
		}
		for (int j = 0; j < size; j++) {
			if (j == currentRow) {
				continue;
			}
			else {
				double multiplier = -matrix[j][currentRow];
				for (int k = 0; k < size; k++) {
					matrix[j][k] += multiplier * matrix[currentRow][k];
					inverseMatrix[j][k] += multiplier * inverseMatrix[currentRow][k];
				}
			}
		}
		currentRow++;
	}

	/*for (int i = 0; i < size; i++) {
		for (int j = 0; j < size; j++) {
			cout << matrix[i][j] << '\t';
		}
		cout << '\n';
	}*/

	double error = 0;
	for (int i = 0; i < size; i++) {
		for (int j = 0; j < size; j++) {
			double sum = 0;
			for (int k = 0; k < size; k++) {
				sum += originMatrix[i][k] * inverseMatrix[k][j];
			}
			if (i == j) {
				sum -= 1;
			}
			if (sum < 0 ) {
				sum *= -1;
			}
			//cout << sum << '\n';
			if (sum > error) {
				error = sum;
			}
		}
	}

	cout << error;

	fin.close();
	return 0;
}

