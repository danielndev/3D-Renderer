#include <vector>
#include <array>
#include "Triangle.h"

Triangle::Triangle(std::vector<std::array<float, 3>> v) {
	vertices = v;
	position = { 0, 0, 0 };
	for (int i = 0; i < vertices.size(); i++) {
		position[0] += vertices[i][0];
		position[1] += vertices[i][1];
		position[2] += vertices[i][2];
	}

	position[0] /= vertices.size();
	position[1] /= vertices.size();
	position[2] /= vertices.size();
}

std::vector<std::array<float, 3>> Triangle::getVertices() {
	return vertices;
}

void Triangle::addNormal(std::array<float, 3> n) {
	normal = n;
}

std::array<float, 3> Triangle::getNormal() {
	return normal;
}

std::array<float, 3> Triangle::getPosition() {
	position = { 0, 0, 0 };
	for (int i = 0; i < vertices.size(); i++) {
		position[0] += vertices[i][0];
		position[1] += vertices[i][1];
		position[2] += vertices[i][2];
	}

	position[0] /= vertices.size();
	position[1] /= vertices.size();
	position[2] /= vertices.size();
	return position;
}