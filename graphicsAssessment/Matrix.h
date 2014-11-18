#pragma once
class Matrix
{
public:
	Matrix(int rows, int columns, double *data);
	Matrix(int rows, int columns);
	~Matrix();

private:
	void checkBounds(int i, int j);
	//void checkBounds(int i, int j, int rows, int columns);
	
	
	

protected:
	double* data;
	int columns;
	int rows;

public:
	int Rows();
	int Columns();
	double get(int i, int j);
	void Matrix::set(double value, int i, int j);

	void toString();

	static void copySection(int i, int j, int dI, int dJ, Matrix* base, Matrix* target);

	double* getArray();

	Matrix subMatrix(int startI, int startJ, int rows, int columns);

	double mean();
	
};

