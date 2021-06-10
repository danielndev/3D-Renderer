#include "Object.h"
#include <iostream>
#include<vector>
#include<array>
#include<SDL.h>
#include<fstream>
#include<strstream>
#include "SDL2_gfxPrimitives.h"
#include "Triangle.h"
#include<string>
Object::Object(float x, float y, float z, float s, std::string filename) {
	//Generate cube for testing purposes;
	setPosition(x, y, z);


	loadObject(filename, s);
	//generateCube(0, 0, 0);
}

void Object::loadObject(std::string filename, float scale) {
	std::ifstream f;
	std::vector < std::array<float, 3>> vertices;
	std::vector < std::array<float, 3>> normals;
	f.open(filename);
	char output[100];
	

	if (f.is_open()) {
		while (!f.eof()) {
			f.getline(output, 100);
			std::strstream line;
			line << output;
			
			char j;
			if (output[0] == 'v') {
				if (output[1] == 'n') {
					std::array<float, 3> normal;
					line >> j >> j >> normal[0] >> normal[1] >> normal[2];
					normals.push_back(normal);
					
				}
				else {
					std::array<float, 3> vertex;
					line >> j >> vertex[0] >> vertex[1] >> vertex[2];
					vertices.push_back({ vertex[0] * scale + position[0], vertex[1] * scale + position[1], vertex[2] * scale + position[2] });
				}
	
			}
			if (output[0] == 'f') {
				std::array<float, 3> vertexOrder;
				int normalIndex;
				line >> j >> vertexOrder[0] >> j >> j >> normalIndex >> vertexOrder[1] >> j >> j >> normalIndex >> vertexOrder[2];
				//std::cout << vertexOrder[0] - 1 << vertexOrder[1] - 1 << vertexOrder[2] - 1 << normalIndex << std::endl;
				Triangle t({
					vertices[vertexOrder[0] - 1],
					vertices[vertexOrder[1] - 1],
					vertices[vertexOrder[2] - 1]
					});

		
				t.addNormal(normals[normalIndex - 1]);
				
				triangles.push_back(t);
			}
		}
	}

	f.close();
}

void Object::generateCube(float x, float y, float z) {
	std::vector<Triangle> t;
	float scale = 0.1;

	Triangle t1({
		{ 0 * scale + position[0] , 0 * scale + position[1], 0 * scale + position[2] },
		{ 0 * scale + position[0], 1 * scale + position[1], 0 * scale + position[2] },
		{ 1 * scale + position[0], 1 * scale + position[1], 0 * scale + position[2] }
		});

	Triangle t2({
		{ 0 * scale + position[0] , 0 * scale + position[1], 0 * scale + position[2] },
		{ 1 * scale + position[0], 1 * scale + position[1], 0 * scale + position[2] },
		{ 1 * scale + position[0], 0 * scale + position[1], 0 * scale + position[2] }
		});

	Triangle t3({
		{ 1 * scale + position[0], 0 * scale + position[1], 0 * scale + position[2] },
		{ 1 * scale + position[0], 1 * scale + position[1], 0 * scale + position[2] },
		{ 1 * scale + position[0], 1 * scale + position[1], 1 * scale + position[2] }
		});

	Triangle t4({
		{ 1 * scale + position[0], 0 * scale + position[1], 0 * scale + position[2] },
		{ 1 * scale + position[0], 1 * scale + position[1], 1 * scale + position[2] },
		{ 1 * scale + position[0], 0 * scale + position[1], 1 * scale + position[2] }
		
		});

	Triangle t5({
		{ 1 * scale + position[0], 0 * scale + position[1], 1 * scale + position[2] } ,
		{ 1 * scale + position[0], 1 * scale + position[1] , 1 * scale + position[2] },
		{ 0 * scale + position[0], 1 * scale + position[1], 1 * scale + position[2] }
		});

	Triangle t6({
		{ 1 * scale + position[0], 0 * scale + position[1], 1 * scale + position[2] },
		{ 0 * scale + position[0], 1 * scale + position[1], 1 * scale + position[2] },
		{ 0 * scale + position[0], 0 * scale + position[1], 1 * scale + position[2] }
		
		});

	Triangle t7({
		{ 0 * scale + position[0], 0 * scale + position[1], 1 * scale + position[2] } ,
		{ 0 * scale + position[0], 1 * scale + position[1], 1 * scale + position[2] },
		{ 0 * scale + position[0], 1 * scale + position[1], 0 * scale + position[2] }
		});

	Triangle t8({
		{ 0 * scale + position[0], 0 * scale + position[1], 1 * scale + position[2] },
		{ 0 * scale + position[0], 1 * scale + position[1], 0 * scale + position[2] },
		{ 0 * scale + position[0], 0 * scale + position[1] , 0 * scale + position[2] }
		
		});

	Triangle t9({
		{ 0 * scale + position[0], 1 * scale + position[1], 0 * scale + position[2] } ,
		{ 1 * scale + position[0], 1 * scale + position[1] , 1 * scale + position[2] },
		{ 0 * scale + position[0], 1 * scale + position[1] , 1 * scale + position[2] }
		});

	Triangle t10({
		{ 0 * scale + position[0], 1 * scale + position[1], 0 * scale + position[2] },
		
		{ 1 * scale + position[0], 1 * scale + position[1] , 0 * scale + position[2] },
		{ 1 * scale + position[0], 1 * scale + position[1] , 1 * scale + position[2] },
		
		});

	Triangle t11({
		{ 0 * scale + position[0], 0 * scale + position[1], 0 * scale + position[2] },
		{ 1 * scale + position[0], 0 * scale + position[1], 1 * scale + position[2] },
		{ 0 * scale + position[0], 0 * scale + position[1], 1 * scale + position[2] }
		
		});

	Triangle t12({
		{ 0 * scale + position[0], 0 * scale + position[1], 0 * scale + position[2] },
		{ 1 * scale + position[0], 0 * scale + position[1], 0 * scale + position[2] },
		{ 1 * scale + position[0], 0 * scale + position[1] , 1 * scale + position[2] }
		
		
		});

	t.push_back(t1);
	t.push_back(t2);
	t.push_back(t3);
	t.push_back(t4);
	t.push_back(t5);
	t.push_back(t6);
	t.push_back(t7);
	t.push_back(t8);
	t.push_back(t9);
	t.push_back(t10);
	t.push_back(t11);
	t.push_back(t12);

	triangles = t;

}

float* Object::getPosition() {
	return position;
}

std::vector<std::array<float, 3>> Object::getVertices() {
	return vertices;
}

void Object::renderTriangles(Renderer r) {
	SDL_SetRenderDrawColor(r.getRenderer(), 0, 0, 255, 255);

}

void Object::setPosition(float x, float y, float z) {
	position[0] = x;
	position[1] = y;
	position[2] = z;
}

std::vector<Triangle> Object::getTriangles() {
	return triangles;
}
