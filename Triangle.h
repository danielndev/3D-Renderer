#include <vector>
#include <array>
#ifndef TRIANGLE_H
#define TRIANGLE_H

class Triangle {
private:
	std::vector<std::array<float, 3>> vertices;
	std::array<float, 3 > normal;
	std::array<float, 3> position;
public:
	Triangle(std::vector<std::array<float, 3>> v);
	std::vector<std::array<float, 3>> getVertices(); 
	void addNormal(std::array<float, 3> n);
	std::array<float, 3> getNormal();
	std::array<float, 3> getPosition();
};

#endif