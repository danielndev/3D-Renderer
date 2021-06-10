#include <vector>
#include <array>
#include<string>
#include "Renderer.h"
#include "Matrix.h"
#include "Triangle.h"
#ifndef Object_H
#define Object_H


class Object {
private:
	Matrix mTool;
	std::vector<std::array<float, 3>> vertices;

	std::vector<Triangle> triangles;
	float position[3];
	float rotation[3];
public:
	Object(float x, float y, float z, float s, std::string filename);
	void loadObject(std::string filename, float scale);
	void generateCube(float x, float y, float z);
	float* getPosition();
	std::vector<std::array<float, 3>> getVertices();
	void renderFaces(Renderer r);
	void setPosition(float x, float y, float z);
	std::vector<Triangle> getTriangles();
	void rotate(std::vector<std::array<float, 3>> rMatrix);
	int clipAll(std::array<float, 3> planeNormal, std::array<float, 3> planePosition);

	void renderTriangles(Renderer r);
};


#endif
