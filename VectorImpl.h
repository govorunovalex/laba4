#pragma once
#include "Vector.h"


template<typename DataType, typename DimType>
void Vector<DataType, DimType>::quickSort(DataType* data, DimType len) {
	DimType const lenD = len;
	DataType pivot = 0;
	DimType ind = lenD / 2;
	DimType i, j = 0, k = 0;
	if (lenD > 1) {
		DataType* L = new DataType[lenD];
		DataType* R = new DataType[lenD];
		pivot = data[ind];
		for (i = 0; i < lenD; i++) {
			if (i != ind) {
				if (data[i] < pivot) {
					L[j] = data[i];
					j++;
				}
				else {
					R[k] = data[i];
					k++;
				}
			}
		}
		quickSort(L, j);
		quickSort(R, k);
		for (int cnt = 0; cnt < lenD; cnt++) {
			if (cnt < j) {
				data[cnt] = L[cnt];;
			}
			else if (cnt == j) {
				data[cnt] = pivot;
			}
			else {
				data[cnt] = R[cnt - (j + 1)];
			}
		}
		delete[] L;
		delete[] R;
	}
}


template<typename DataType, typename DimType>
Vector<DataType, DimType>::Vector() {
	data = nullptr;
	dim = 0;
}


template<typename DataType, typename DimType>
Vector<DataType, DimType>::Vector(DimType new_dim) :dim(new_dim) {
	data = new DataType[dim];
}

template<typename DataType, typename DimType>
Vector<DataType, DimType>::Vector(DataType new_data[], DimType new_dim) : dim(new_dim) {
	data = new DataType[dim];

	for (DimType i = 0; i < dim; ++i) {
		data[i] = new_data[i];
	}
}

template<typename DataType, typename DimType>
Vector<DataType, DimType>::Vector(const Vector& other) :dim(other.dim) {
	data = new DataType[dim];

	for (DimType i = 0; i < dim; ++i) {
		data[i] = other.data[i];
	}
}
template<typename DataType, typename DimType>
Vector<DataType, DimType>::~Vector() {
	delete[] data;
}
template<typename DataType, typename DimType>
DataType* Vector<DataType, DimType>::getData() {
	return data;
}

template<typename DataType, typename DimType>
DimType Vector<DataType, DimType>::getDimension() const {
	return dim;
}

template <typename DataType, typename DimType>
DimType Vector<DataType, DimType>::countOf(DataType toFind) const {
	DimType count = 0;
	for (DimType i = 0; i < dim; ++i) {
		if (toFind == data[i]) ++count;
	}
	return count;
}

template<typename DataType, typename DimType>
DataType* Vector<DataType, DimType>::returnAppearence(DataType toFind) const
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
Vector<DataType, DimType> Vector<DataType, DimType>::operator+(const Vector& other) {
	Vector result(data, dim);
	for (DimType i = 0; i < dim; ++i) {
		result.data[i] += other.data[i];
	}
	return result;
}
template<typename DataType, typename DimType>
Vector<DataType, DimType> Vector<DataType, DimType>::operator-(const Vector& other) {
	Vector result(data, dim);
	for (DimType i = 0; i < dim; ++i) {
		result.data[i] -= other.data[i];
	}
	return result;
}

template<typename DataType, typename DimType>
DataType Vector<DataType, DimType>::operator*(const Vector<DataType, DimType>& other) {
	DataType result = 0;
	for (DimType i = 0; i < dim; ++i) {
		result += data[i] * other.data[i];
	}
	return result;
}

template<typename DataType, typename DimType>
Vector<DataType, DimType>& Vector<DataType, DimType>::operator=(const Vector& other) {
	delete[] data;
	dim = other.dim;
	data = new DataType[dim];
	for (DimType i = 0; i < dim; ++i) {
		data[i] = other.data[i];
	}
	return *this;
}
template<typename DataType, typename DimType>
bool Vector<DataType, DimType>::operator==(const Vector& other) const {
	for (DimType i = 0; i < dim; ++i) {
		if (data[i] - other.data[i] > EPSILON ||
			data[i] - other.data[i] < -EPSILON) {
			return false;
		}
	}
	return true;
}

template<typename DataType, typename DimType>
DataType& Vector<DataType, DimType>::operator[](int i) const {
	return data[i];
}


template<typename DataType, typename DimType>
void Vector<DataType, DimType>::bubbleSort()
{
	DataType tmp = 0;
	for (DimType i = 0; i < dim; i++) {
		for (DimType j = (dim - 1); j >= (i + 1); j--) {
			if (data[j] < data[j - 1]) {
				tmp = data[j];
				data[j] = data[j - 1];
				data[j - 1] = tmp;
			}
		}
	}
}

template<typename DataType, typename DimType>
void Vector<DataType, DimType>::insertionSort()
{
	DataType key = 0;
	DimType i = 0;
	for (DimType j = 1; j < dim; j++) {
		key = data[j];
		i = j - 1;
		while (i >= 0 && data[i] > key) {
			data[i + 1] = data[i];
			i = i - 1;
			data[i + 1] = key;
		}
	}
}

template<typename DataType, typename DimType>
void Vector<DataType, DimType>::quickSort() {
	quickSort(data, dim);
}
