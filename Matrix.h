#pragma once
#include <iostream>
#include "Vector.h"

template<typename DataType, typename DimType>
class Matrix {
	const double EPSILON = 0.000001;
	DataType** data;
	DimType rows, cols;
public:
	Matrix();
	Matrix(DimType rows, DimType cols);
	Matrix(DataType** new_data, DimType rows, DimType cols);
	Matrix(DataType** new_data, DimType rows, DimType cols, DimType ex_rows, DimType ex_cols);
	Matrix(const Matrix& other);
	~Matrix();
	DataType** getData();
	DimType getRows() const;
	DimType getCols() const;
	DimType countOf(DataType toFind) const;
	DataType* returnAppearence(DataType toFind) const;
	Matrix trans() const;
	DataType det() const;
	Matrix revese() const;
	Matrix operator+(const Matrix& other);
	Matrix operator-(const Matrix& other);
	Matrix operator*(const Matrix& other);
	Matrix operator/(const Matrix& other);
	Matrix& operator=(const Matrix& other);
	bool operator==(const Matrix& other) const;
	const DataType* operator[](int i) const;
	friend std::ostream& operator<<(std::ostream& stream, const Matrix<DataType, DimType>& matr)
	{
		stream << "Matrix with rows: " << matr.rows << " and cols: " << matr.cols << " with components:\n";
		for (DimType i = 0; i < matr.rows; ++i) {
			for (DimType j = 0; j < matr.cols; ++j) {
				stream << matr.data[i][j] << '\t';
			}
			stream << std::endl;
		}
		return stream;
	}
	friend std::istream& operator>>(std::istream& stream, Matrix<DataType, DimType>& matr)
	{
		for (DimType i = 0; i < matr.rows; ++i) {
			for (DimType j = 0; j < matr.cols; ++j) {
				stream >> matr.data[i][j];
			}
		}
		return stream;
	}

	DataType* operator[](int i);


};

