#include <vector>
#include <array>
#include <iostream>

#include "Matrix.h";

Matrix::Matrix(std::vector<std::vector<float>> m) {
	matrix = m;
}

std::array<float, 3> Matrix::vectorMultiply(std::array<float, 3> v) {
	std::array<float, 3> output;

	for (int i = 0; i < matrix.size(); i++) {
		output[i] = 0;
		for (int j = 0; j < v.size(); j++) {
			output[i] += v[j] * matrix[i][j];
		}
	}

	

	return output;
}



Matrix Matrix::matrixMultiply(Matrix m) {
	Matrix outputMatrix({ { 0, 0, 0 }, { 0, 0, 0 }, { 0, 0, 0 } });
	for (int i = 0; i < matrix.size(); i++) {
		for (int j = 0; j < m.matrix[i].size(); j++) {
			for (int k = 0; k < m.matrix[j].size(); k++) {
				outputMatrix.matrix[i][j] += matrix[i][k] * m.matrix[k][j];
			}
		}
	}

	return outputMatrix;
}


std::array<float, 3> Matrix::vector3CrossProduct(std::array<float, 3> v1, std::array<float, 3> v2) {
	std::array<float, 3> output;
	output[0] = v1[1] * v2[2] - v1[2] * v2[1];
	output[1] = v1[0] * v2[2] - v1[2] * v2[0];
	output[2] = v1[0] * v2[1] - v1[1] * v2[0];
	return output;
}

float Matrix::dotProduct(std::array<float, 3> v1, std::array<float, 3> v2) {
	float output = 0;
	for (int i = 0; i < v1.size(); i++) {
		output += v1[i] * v2[i];
	}

	return output;
}
std::array<float, 3> Matrix::scalerMultiply(std::array<float, 3> v, float x) {
	std::array<float, 3> output;
	for (int i = 0; i < v.size(); i++) {
		output[i] = x * v[i];
	}

	return output;
}

std::array<float, 3> Matrix::vectorAdd(std::array<float, 3> v1, std::array<float, 3> v2) {
	std::array<float, 3> output;
	for (int i = 0; i < v1.size(); i++) {
		output[i] = v1[i] + v2[i];
	}

	return output;
}

std::array<float, 3> Matrix::vectorMinus(std::array<float, 3> v1, std::array<float, 3> v2) {
	std::array<float, 3> output;
	for (int i = 0; i < v1.size(); i++) {
		output[i] = v1[i] - v2[i];
	}

	return output;
}

float Matrix::vectorMagnitude(std::array<float, 3> v) {
	float output = 0;
	for (int i = 0; i < v.size(); i++) {
		output += v[i] * v[i];
	}
	return sqrt(output);
}

std::array<float, 3> Matrix::vectorNormalize(std::array<float, 3> v) {
	std::array<float, 3> output = v;
	float magnitude = vectorMagnitude(v);
	if (magnitude == 0) {
		return v;
	}
	for (int i = 0; i < v.size(); i++) {
		output[i] /= magnitude;
	}

	return output;
}