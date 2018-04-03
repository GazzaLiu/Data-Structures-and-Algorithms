#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <algorithm>
#include <new>
#include "matrix.h"
#include <iostream>

Matrix::Matrix(const int& r, const int& c) //constructor
{
	// construct size
	row = r;
	col = c;
	// construct array
	array = new double* [r];
	for (int i = 0; i < r; i++) {
		array[i] = new double[c];
	}
}

Matrix::Matrix(const Matrix& rhs) //copy constructor
{
	// assign size
	row = rhs.row;
	col = rhs.col;
	// allocate new array
	array = new double* [row];
	for (int i = 0; i < row; i++) {
		array[i] = new double[col];
		// assign array elements
		for (int j = 0; j < col; j++) {
			array[i][j] = rhs.array[i][j];
		}
	}
}

Matrix::~Matrix() //destructor
{
	for(int i = 0; i < row; i++) {
		delete [] array[i];
	}
	delete [] array;
}

double* & Matrix::operator [](const int& idx) const	// Enable the use of A[i][j] instead of A.array[i][j]
{
	return array[idx];
}

Matrix Matrix::operator =(const Matrix& rhs) // assignment operator
{
	if (this != &rhs) {
		// delete old array
		for(int i = 0; i < row; i++) {
			delete [] array[i];
		}
		delete [] array;
		// assign size
		row = rhs.row;
		col = rhs.col;
		// allocate new array
		array = new double* [row];
		for (int i = 0; i < row; i++) {
			array[i] = new double[col];
			// assign array elements
			for (int j = 0; j < col; j++) {
				array[i][j] = rhs.array[i][j];
			}
		}
	}
	// return modified object
	return *this;
}

Matrix Matrix::operator -() const
{
	Matrix temp(row, col);
	for (int i = 0; i < row; i++) {
		for (int j = 0; j < col; j++) {
			temp[i][j] = array[i][j] * -1;
		}
	}
	return temp;
}

Matrix Matrix::operator +() const
{
	Matrix temp(row, col);
	for (int i = 0; i < row; i++) {
		for (int j = 0; j < col; j++) {
			temp[i][j] = array[i][j];
		}
	}
	return temp;
}

Matrix Matrix::operator -(const Matrix& rhs) const
{
	// skip check size
	Matrix temp(row, col);
	for (int i = 0; i < row; i++) {
		for (int j = 0; j < col; j++) {
			temp[i][j] = array[i][j] - rhs[i][j];
		}
	}
	return temp;
}

Matrix Matrix::operator +(const Matrix& rhs) const
{
	// skip check size
	Matrix temp(row, col);
	for (int i = 0; i < row; i++) {
		for (int j = 0; j < col; j++) {
			temp[i][j] = array[i][j] + rhs[i][j];
		}
	}
	return temp;
}

Matrix Matrix::operator *(const Matrix& rhs) const
{
	// assume the matrices to be multiplied are of compatible dimensions
	double tempSum = 0;
	Matrix temp(row, rhs.col);
	for (int i = 0; i < row; i++) {
		for (int j = 0; j < rhs.col; j++) {
			tempSum = 0;
			for (int k = 0; k < col; k++) {
				tempSum += array[i][k] * rhs[k][j];
			}
			temp[i][j] = tempSum;
		}
	}
	return temp;
}

Matrix Matrix::operator /(const Matrix& rhs) const
{
	// assume the inverse of the matrix always exists
	Matrix temp(rhs.row, rhs.col);
	temp = *this * rhs.inverse();
	return temp;
}

Matrix Matrix::inverse() const
{
	// assume the inverse of the matrix always exists
	int currentRow = 0;
	Matrix originMatrix(*this);
	Matrix inverseMatrix(row, col);

	// assign identity matrix
	for (int i = 0; i < row; i++) {
		for (int j = 0; j < col; j++) {
			if (i == j) {
				inverseMatrix[i][j] = 1;
				
			}
			else {
				inverseMatrix[i][j] = 0;
			}
		}
	}

	//originMatrix.print();
	//inverseMatrix.print();

	// Gauss-Jordan elimination method
	while (currentRow < row) {
		//originMatrix.print();
		//inverseMatrix.print();
		// select denominator
		double denominator = originMatrix[currentRow][currentRow];
		// if denominator is zero
		if (denominator == 0) {
			//std::cout << "denominator is zero, reselect" << std::endl;
			int saveRow = 0;
			while (originMatrix[saveRow][currentRow] == 0) {
				// assume it must find row
				saveRow++;
			}
			for (int i = 0; i < row; i++) {
				originMatrix[currentRow][i] += originMatrix[saveRow][i];
				inverseMatrix[currentRow][i] += inverseMatrix[saveRow][i];
			}
			denominator = originMatrix[currentRow][currentRow];
			//std::cout << denominator << std::endl;
		}
		//std::cout << "denominator: " << denominator << std::endl;
		for (int j = 0; j < row; j++) {
			originMatrix[currentRow][j] /= denominator;
			inverseMatrix[currentRow][j] /= denominator;
		}
		for (int j = 0; j < row; j++) {
			if (j == currentRow) {
				continue;
			}
			else {
				double multiplier = -originMatrix[j][currentRow];
				for (int k = 0; k < row; k++) {
					originMatrix[j][k] += multiplier * originMatrix[currentRow][k];
					inverseMatrix[j][k] += multiplier * inverseMatrix[currentRow][k];
				}
			}
		}
		currentRow++;
	}
	return inverseMatrix;
}

void Matrix::read(const char* fn)
{
	int r, c;
	FILE *fp = fopen(fn, "r");
	if(fp == NULL){
		printf("read file [%s] error\n", fn);
		exit(0);
	}
	fscanf(fp, "%d%d", &r, &c);
	Matrix tmp(r, c);
	for(int i = 0 ; i < r ; i++)
		for(int j = 0 ; j < c ; j++)
			fscanf(fp, "%lf", &tmp.array[i][j]);
	fclose(fp);
	*this = tmp;
}

void Matrix::write(const char* fn)
{
	FILE *fp = fopen(fn, "w");
	if(fp == NULL){
		printf("write file [%s] error\n", fn);
		exit(0);
	}
	fprintf(fp, "%d %d\n", row, col);
	for(int i = 0 ; i < row ; i++)
		for(int j = 0 ; j < col ; j++)
			fprintf(fp, "%lf%c", array[i][j], " \n"[j==col-1]);
	fclose(fp);
}

void Matrix::print() const
{
	for(int i = 0 ; i < row ; i++)
		for(int j = 0 ; j < col ; j++)
			printf("%lf%c", array[i][j], " \n"[j==col-1]);
}