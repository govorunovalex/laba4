#pragma once
#include <iostream>
#include "Matrix.h"


template<typename DataType, typename DimType>
class Vector {
	const double EPSILON = 0.000001;
	DataType* data;
	DimType dim;
	void quickSort(DataType* data, DimType len);
public:
	Vector();
	Vector(DimType new_dim);
	Vector(DataType new_data[], DimType new_dim);
	Vector(const Vector& other);
	~Vector();
	DataType* getData();
	DimType getDimension() const;
	DimType countOf(DataType toFind) const;
	DataType* returnAppearence(DataType toFind) const;
	Vector operator+(const Vector& other);
	Vector operator-(const Vector& other);
	DataType operator*(const Vector& other);
	Vector& operator=(const Vector& other);
	bool operator==(const Vector& other) const;
	DataType& operator[](int i) const;

	friend std::ostream& operator<<(std::ostream& stream, const Vector<DataType, DimType>& vec) {
		stream << "Vector dimension: " << vec.dim << " with components:";
		for (DimType i = 0; i < vec.dim; ++i) {
			stream << " " << vec.data[i];
		}
		stream << std::endl;
		return stream;
	}
	friend std::istream& operator>>(std::istream& stream, Vector<DataType, DimType>& vec) {	
		for (DimType i = 0; i < vec.dim; ++i) {
			stream >> vec.data[i];
		}
		return stream;
	}

	void bubbleSort();
	void insertionSort();
	void quickSort();

};

