#include <iostream>
#include "Matrix.h"


Matrix::Matrix(int rows, int columns, double *source)
{
	data = new double[rows*columns];
	this->rows = rows;
	this->columns = columns;
	for (int i = 0; i < rows*columns; i++)
		data[i] = source[i];

	//std::cout << "Call to: Matrix::Matrix(int rows, int columns, double *source)" << std::endl;
}

Matrix::Matrix(int rows, int columns)
{
	this->rows = rows;
	this->columns = columns;
	data = new double[rows*columns] { 0 };

	//std::cout << "Call to: Matrix::Matrix(int rows, int columns)" << std::endl;
}


Matrix::~Matrix()
{
	//std::cout << "Call to: Matrix::~Matrix()" << std::endl;
	//delete[] data;
}

int Matrix::Rows(){ return rows; }
int Matrix::Columns(){ return columns; }

double Matrix::get(int i, int j){
	checkBounds(i, j);
	return data[i * columns + j];
}

void Matrix::set(double value, int i, int j){
	checkBounds(i, j);
	data[i * columns + j] = value;
}

void Matrix::toString(){
	for (int i = 0; i < rows; i++){
		for (int j = 0; j < columns; j++){
			std::cout << get(i, j) << " ";
		}
		std::cout << std::endl;
	}
}

double* Matrix::getArray(){
	return data;
}

void Matrix::copySection(int i, int j, int dI, int dJ, Matrix* base, Matrix* target){
	for (int m = 0; m < 32; m++)
		for (int n = 0; n < 32; n++)
			target->set(base->get((i * 32) + m, (j * 32) + n), (dI * 32) + m, (dJ * 32) + n);
}

Matrix Matrix::subMatrix(int startI, int startJ, int rows, int columns){
	Matrix matrix = Matrix(rows, columns);
	for (int i = 0; i < rows; i++)
		for (int j = 0; j < columns; j++)
			matrix.set(get(startI + i, startJ + j), i, j);
	return matrix;
}

double Matrix::mean(){
	double mean = 0;
	for (int i = 0; i < Columns(); i++)
		for (int j = 0; j < Rows(); j++){
		mean += get(i, j);
		}
	mean /= Columns() * Rows();
	return mean;
}

void Matrix::checkBounds(int i, int j){
	if (i >= this->rows || j >= this->columns)
		throw std::runtime_error("subMatrix out of range");
}

/*void Matrix::checkBounds(int i, int j, int rows, int columns){
	//TODO not needed
	if ((i + rows) * (j + columns) > this->rows * this->columns)
		throw std::out_of_range("subMatrix out of range");
	if (i + rows >= this->rows || j + columns >= this->columns)
		throw std::runtime_error("subMatrix out of range");
}*/
