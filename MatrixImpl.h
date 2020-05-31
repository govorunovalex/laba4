#pragma once

#include "Matrix.h"


template <typename DataType, typename DimType>
Matrix<DataType, DimType>::Matrix() {
	data = nullptr;
	rows = 0;
	cols = 0;
}

template <typename DataType, typename DimType>
Matrix<DataType, DimType>::Matrix(DimType rows, DimType cols) :rows(rows), cols(cols) {
	data = new DataType * [rows];

	for (DimType i = 0; i < rows; ++i) {
		data[i] = new DataType[cols];
	}
}

template <typename DataType, typename DimType>
Matrix<DataType, DimType>::Matrix(DataType** new_data, DimType rows, DimType cols) :rows(rows), cols(cols) {
	data = new DataType * [rows];

	for (DimType i = 0; i < rows; ++i) {
		data[i] = new DataType[cols];
		for (DimType j = 0; j < cols; ++j) {
			data[i][j] = new_data[i][j];
		}
	}
}

template<typename DataType, typename DimType>
Matrix<DataType, DimType>::Matrix(DataType** new_data, DimType rows, DimType cols, DimType ex_rows, DimType ex_cols) :rows(rows), cols(cols)
{
	data = new DataType * [rows + 1];

	for (DimType i = 0; i < rows + 1; ++i) {
		data[i] = new DataType[cols + 1];
		for (DimType j = 0; j < cols + 1; ++j) {
			data[i][j] = new_data[i][j];
		}
	}
	for (DimType i = ex_rows; i < rows; ++i) {
		for (DimType j = 0; j < cols + 1; ++j) {
			data[i][j] = data[i + 1][j];
		}
	}
	for (DimType i = 0; i < rows; ++i) {
		for (DimType j = ex_cols; j < cols; ++j) {
			data[i][j] = data[i][j+1];
		}
	}
}

template <typename DataType, typename DimType>
Matrix<DataType, DimType>::Matrix(const Matrix& other) :rows(other.rows), cols(other.cols) {
	data = new DataType * [rows];

	for (DimType i = 0; i < rows; ++i) {
		data[i] = new DataType[cols];
		for (DimType j = 0; j < cols; ++j) {
			data[i][j] = other.data[i][j];
		}
	}
}
template <typename DataType, typename DimType>
Matrix<DataType, DimType>::~Matrix() {
	for (DimType i = 0; i < rows; ++i) {
		delete[] data[i];
	}
	delete[] data;
}
template<typename DataType, typename DimType>
DataType** Matrix<DataType, DimType>::getData()
{
	return data;
}

template <typename DataType, typename DimType>
DimType Matrix<DataType, DimType>::getRows() const {
	return rows;
}
template <typename DataType, typename DimType>
DimType Matrix<DataType, DimType>::getCols() const {
	return cols;
}

template <typename DataType, typename DimType>
DimType Matrix<DataType, DimType>::countOf(DataType toFind) const {
	DimType count = 0;
	for (DimType i = 0; i < rows; ++i) {
		for (DimType j = 0; j < cols; ++j) {
			if (toFind == data[i][j]) ++count;
		}
	}
	return count;
}

template<typename DataType, typename DimType>
DataType* Matrix<DataType, DimType>::returnAppearence(DataType toFind) const
{
	DimType count = countOf(toFind);
	if (count == 0) return nullptr;
	DataType* result = new DataType[count];
	for (DimType i = 0; i < count; ++i) {
		result[i] = toFind;
	}
	return result;
}

template<typename DataType, typename DimType>
Matrix<DataType, DimType> Matrix<DataType, DimType>::trans() const
{
	Matrix<DataType, DimType> result(cols, rows);
	for (DimType i = 0; i < cols; ++i) {
		for (DimType j = 0; j < rows; ++j) {
			result.data[i][j] = data[j][i];
		}
	}
	return result;
}

template<typename DataType, typename DimType>
DataType Matrix<DataType, DimType>::det() const
{
	if (rows == cols) {
		if (rows == 2) {
			return data[0][0] * data[1][1] - data[1][0] * data[0][1];
		}
		else {
			DataType det = 0;
			Matrix<DataType, DimType>* additions;
			additions = new Matrix<DataType, DimType>[rows];
			for (DimType i = 0; i < rows; ++i) {
				additions[i] = Matrix<DataType, DimType>(data, rows - 1, cols - 1, i, 0);
				det += data[i][0] * additions[i].det();
			}
			return det;
		}
	}
	else {
		throw("det for not square matrix!");
	}
}
template<typename DataType, typename DimType>
inline Matrix<DataType, DimType> Matrix<DataType, DimType>::revese() const
{
	if (rows == cols) {
		DataType det = this->det();
		if (det == 0) {
			throw("reverse for matrix with det = 0!");
		}
		else {
			Matrix<DataType, DimType> result(rows, cols);
			Matrix<DataType, DimType>** additions;
			additions = new Matrix<DataType, DimType> * [rows];
			for (DimType i = 0; i < rows; ++i) {
				additions[i] = new Matrix<DataType, DimType>[cols];
				for (DimType j = 0; j < cols; ++j) {
					additions[i][j] = Matrix<DataType, DimType>(data, rows - 1, cols - 1, i, j);
					result.data[i][j] =  additions[i][j].det() / det;
				}
			}
			return result;
		}
	}
	else {
		throw("reverse for not square matrix!");

	}
}

template <typename DataType, typename DimType>
Matrix<DataType, DimType> Matrix<DataType, DimType>::operator+(const Matrix& other) {
	Matrix result(*this);
	for (DimType i = 0; i < rows; ++i) {
		for (DimType j = 0; j < other.cols; ++j) {
			result.data[i][j] += other.data[i][j];
		}
	}
	return result;
}

template <typename DataType, typename DimType>
Matrix<DataType, DimType> Matrix<DataType, DimType>::operator-(const Matrix& other) {
	Matrix result(*this);
	for (DimType i = 0; i < rows; ++i) {
		for (DimType j = 0; j < other.cols; ++j) {
			result[i][j] -= other.data[i][j];
		}
	}
	return result;
}

template <typename DataType, typename DimType>
Matrix<DataType, DimType> Matrix<DataType, DimType>::operator*(const Matrix& other) {
	// check for cols == other.rows ??
	Matrix result(rows, other.cols);
	for (DimType i = 0; i < rows; ++i) {
		for (DimType j = 0; j < other.cols; ++j) {
			result[i][j] = 0;
			for (DimType k = 0; k < cols; ++k) {
				result[i][j] += data[i][k] * other.data[k][j];
			}
		}
	}
	return result;
}

template<typename DataType, typename DimType>
Matrix<DataType, DimType> Matrix<DataType, DimType>::operator/(const Matrix& other)
{
	return (*this)*(other.revese());
}

template <typename DataType, typename DimType>
Matrix<DataType, DimType>& Matrix<DataType, DimType>::operator=(const Matrix& other) {
	for (DimType i = 0; i < rows; ++i) {
		delete[] data[i];
	}
	delete[] data;
	rows = other.rows;
	cols = other.cols;
	data = new DataType * [rows];
	for (DimType i = 0; i < rows; ++i) {
		data[i] = new DataType[cols];
		for (DimType j = 0; j < cols; ++j) {
			data[i][j] = other.data[i][j];
		}
	}
	return *this;
}
template <typename DataType, typename DimType>
bool  Matrix<DataType, DimType>::operator==(const Matrix& other) const {
	for (DimType i = 0; i < rows; ++i) {
		for (DimType j = 0; j < cols; ++j) {
			if (data[i][j] - other.data[i][j] > EPSILON ||
				data[i][j] - other.data[i][j] < -EPSILON) {
				return false;
			}
		}
	}
	return true;
}
template <typename DataType, typename DimType>
const DataType* Matrix<DataType, DimType>::operator[](int i) const {
	return data[i];
}

template <typename DataType, typename DimType>
DataType* Matrix<DataType, DimType>::operator[](int i) {
	return data[i];
}


