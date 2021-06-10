#define _USE_MATH_DEFINES

#include "Camera.h";
#include<cmath>;
#include<math.h>;
#include<iostream>;
#include <vector>;

Camera::Camera() {
	fov = M_PI_2;
	setPosition(0, 0.2, 0);
}

float* Camera::getPosition() {
	return position;
}

float* Camera::getRotation() {
	return rotation;
}

std::vector<std::array<float, 3>> Camera::multiplyMatrices(std::vector<std::array<float, 3>> a, std::vector<std::array<float, 3>> b) {
	std::vector<std::array<float, 3>> outputMatrix = { {0, 0, 0}, {0, 0, 0}, {0,0,0} };
	for (int i = 0; i < a.size(); i++) {
		
		for (int j = 0; j < b[i].size(); j++) {
			for (int k = 0; k < b[i].size(); k++) {
				outputMatrix[i][j] += a[i][k] * b[k][j];
			}
		}
	}

	//printMatrix(outputMatrix);
	return outputMatrix;
}

void Camera::setRotation(float x, float y, float z) {
	rotation[0] = x;
	rotation[1] = y;
	rotation[2] = z;
}

void Camera::setPosition(float x, float y, float z) {
	position[0] = x;
	position[1] = y;
	position[2] = z;

	std::cout << "Moved" << std::endl;
}
