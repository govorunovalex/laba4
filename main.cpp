#include "Vector.h"
#include "Matrix.h"
#include "VectorImpl.h"
#include "MatrixImpl.h"
#include "MixImpl.h"

int main() {

	float data_for_vec[] = { 6.f, 1.f,2.f,3.f };
	Vector<float, int> v0;
	Vector<float, int> v1(data_for_vec, 4);
	Vector<float, int> v2(v1);
	v0 = v2;

	std::cout << "second component of v0 is: " << v0[1] << std::endl;
	std::cout << "v0 is equal v1: " << (v0 == v1) << std::endl;
	std::cout << "v0 is:\n" << v0;

	v0.bubbleSort();
	v1.insertionSort();
	v2.quickSort();
	std::cout << "Results after sort:\n";
	std::cout << "v0 is equal v1: " << (v0 == v1) << std::endl;
	std::cout << "v1 is equal v2: " << (v1 == v2) << std::endl;

	const int n = 4, m = 4;
	float** data = new float* [n];
	for (int i = 0; i < n; ++i) {
		data[i] = new float[m];
		for (int j = 0; j < m; ++j) {
			data[i][j] = ( i == j )?1:0;
		}
	}

	Matrix<float, int> m0;
	Matrix<float, int> m1(data, n, m);
	Matrix<float, int> m2(m1);
	m0 = m2;
	std::cout << "[1][2] component of m0 is: " << m0[1][2] << std::endl;
	std::cout << "m0 is equal m1: " << (m0 == m1) << std::endl;

	std::cout << "m0 is:\n" << m0;
	std::cout << "m0 T is:\n" << m0.trans();
	std::cout << "det m0  is:\n" << m0.det();
	std::cout << "reverse m0  is:\n" << m0.revese();
	std::cout << "m0 / m0 is:\n" << m0 / m0;

	std::cout << "Mix operations:\n";
	std::cout << "v0 *  m0:\n" << v0 * m0;

	float data_for_vec4[] = { 1.f,2.f,3.f,4.f };
	Vector<float, int> v4(data_for_vec4, 4);
	std::cout << "temporary v4 is:\n" << v4;

	std::cout << "m0 * v4:\n" << m0 * v4;

	for (int i = 0; i < n; ++i) delete[] data[i];
	delete[] data;

	return 0;
}

