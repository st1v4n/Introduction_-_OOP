#include "Matrix.h"
#include <iostream>
void createMatrix(int** matrix, int rows, int cols) {
	for (int i = 0; i < rows; i++) {
		matrix[i] = new int[cols];
	}
}
void Matrix::initMatrix() {
	for (int i = 0; i < rows; i++) {
		for (int j = 0; j < cols; j++) {
			std::cin >> matrix[i][j];
		}
	}

}
void Matrix::free() {
	if (matrix == nullptr)return;
	for (int i = 0; i < rows; i++) {
		delete[] matrix[i];
	}
	delete[] matrix;
}
void Matrix::copyFrom(const Matrix& other) {
	this -> matrix = new int*[other.rows];
	this->rows = other.rows;
	this->cols = other.cols;
	createMatrix(matrix, this->rows, this->cols);
	for (int i = 0; i < other.rows; i++) {
		for (int j = 0; j < other.cols; j++) {
			matrix[i][j] = other.matrix[i][j];
		}
	}
}

Matrix::Matrix(const Matrix& other)
{
	copyFrom(other);
}

Matrix& Matrix::operator=(const Matrix& other)
{
	if (this != &other) {
		free();
		copyFrom(other);
	}
	return *this;
}

Matrix::~Matrix()
{
	free();
}

Matrix::Matrix(int rows, int cols)
{
	this->rows = rows;
	this->cols = cols;
	this->matrix = new int*[rows];
	createMatrix(matrix, this->rows, this->cols);
}

Matrix& Matrix::operator+=(const Matrix& other)
{
	if (rows != other.rows || cols != other.cols)return *this;
	for (int i = 0; i < rows; i++) {
		for (int j = 0; j < cols; j++) {
			matrix[i][j] += other.matrix[i][j];
		}
	}
	return *this;
}

Matrix& Matrix::operator-=(const Matrix& other)
{
	if (rows != other.rows || cols != other.cols)return *this;
	for (int i = 0; i < rows; i++) {
		for (int j = 0; j < cols; j++) {
			matrix[i][j] -= other.matrix[i][j];
		}
	}
	return *this;
}

Matrix& Matrix::operator*=(int number)
{
	for (int i = 0; i < rows; i++) {
		for (int j = 0; j < cols; j++) {
			matrix[i][j] *= number;
		}
	}
	return *this;
}

int* Matrix::operator[](int index) const
{
	return matrix[index];
}

std::ostream& operator<<(std::ostream& os, const Matrix& myMatrix)
{
	for (int i = 0; i < myMatrix.rows; i++) {
		for (int j = 0; j < myMatrix.cols; j++) {
			os << myMatrix.matrix[i][j] << ' ';
		}
		std::cout << std::endl;
	}
	return os;
}

Matrix operator+(const Matrix& matrix1, const Matrix& matrix2)
{
	Matrix result;
	result = matrix1;
	result += matrix2;
	return result;
}

Matrix operator-(const Matrix& matrix1, const Matrix& matrix2)
{
	Matrix result;
	result = matrix1;
	result -= matrix2;
	return result;
}

Matrix operator*(const Matrix& myMatrix, int number)
{
	Matrix result(myMatrix);
	result *= number;
	return result;
}

bool operator==(const Matrix& matrix1, const Matrix& matrix2)
{
	if (matrix1.rows != matrix2.rows || matrix1.cols != matrix2.cols)return false;
	for (int i = 0; i < matrix1.rows; i++) {
		for (int j = 0; j < matrix1.cols; j++) {
			if (matrix1.matrix[i][j] != matrix2.matrix[i][j])return false;
		}
	}
		return true;
}

bool operator!=(const Matrix& matrix1, const Matrix& matrix2)
{
	return !(matrix1 == matrix2);
}
