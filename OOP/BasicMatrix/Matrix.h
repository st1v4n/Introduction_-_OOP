#pragma once
#include <iostream>
class Matrix {
	int rows = 2;
	int cols = 2;
	int** matrix = nullptr;
	void free();
	void copyFrom(const Matrix& other);
public:
	void initMatrix();
	Matrix() = default;
	Matrix(const Matrix& other);
	Matrix& operator=(const Matrix& other);
	~Matrix();
	Matrix(int rows, int cols);
	Matrix& operator+=(const Matrix& other);
	friend std::ostream& operator<<(std::ostream& os, const Matrix& myMatrix);
	friend Matrix operator+(const Matrix& matrix1, const Matrix& matrix2);
	Matrix& operator-=(const Matrix& other);
	friend Matrix operator-(const Matrix& matrix1, const Matrix& matrix2);
	Matrix& operator*=(int number);
	friend Matrix operator*(const Matrix& myMatrix, int number);
	friend bool operator==(const Matrix& matrix1, const Matrix& matrix2);
	friend bool operator!=(const Matrix& matrix1, const Matrix& matrix2);
	int* operator[](int index) const;
};
