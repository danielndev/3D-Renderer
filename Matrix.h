#include <vector>
#include <array>
#ifndef MATRIX_H
#define MATRIX_H

class Matrix {
private:

public:
	std::vector<std::vector<float>> matrix;
	Matrix(std::vector<std::vector<float>> m = { {} });
	Matrix matrixMultiply(Matrix m);
	std::array<float, 3> vectorMultiply(std::array<float, 3>v);
	std::array<float, 3> vector3CrossProduct(std::array<float, 3> v1, std::array<float, 3> v2);
	float dotProduct(std::array<float, 3> v1, std::array<float, 3> v2);
	std::array<float, 3> vectorAdd(std::array<float, 3> v1, std::array<float, 3> v2);
	std::array<float, 3> vectorMinus(std::array<float, 3> v1, std::array<float, 3> v2);
	std::array<float, 3> scalerMultiply(std::array<float, 3> v, float x);
	float vectorMagnitude(std::array<float, 3> v);
	std::array<float, 3> vectorNormalize(std::array<float, 3> v);
};

#endif