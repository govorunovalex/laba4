#pragma once
#include "Matrix.h"
#include "Vector.h"



template<typename DataType, typename DimType>
typename Vector<DataType, DimType> operator*(Vector<DataType, DimType>& vec, const Matrix<DataType, DimType>& matr) {
	Vector<DataType, DimType> result(matr.getCols());
	for (DimType i = 0; i < matr.getCols(); ++i) {
		result[i] = 0;
		for (DimType j = 0; j < vec.getDimension(); ++j) {
			result[i] += vec.getData()[j] * matr[j][i];
		}
	}
	return result;
}

template<typename DataType, typename DimType>
Vector<DataType, DimType> operator*(Matrix<DataType, DimType>& matr, const Vector<DataType, DimType>& vec)
{
	Vector<DataType, DimType> result(matr.getRows());
	for (DimType i = 0; i < matr.getRows(); ++i) {
		result[i] = 0;
		for (DimType j = 0; j < vec.getDimension(); ++j) {
			result[i] += vec[j] * matr.getData()[i][j];
		}
	}
	return result;
}