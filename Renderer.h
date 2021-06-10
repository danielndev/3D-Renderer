#define _USE_MATH_DEFINES

#include<SDL.h>
#include<vector>
#include<array>
#include<cmath>;
#include "Camera.h";
#include "Matrix.h";
#include "Triangle.h"
#ifndef RENDERER_H
#define RENDERER_H


class Renderer {
private:
	SDL_Window* window;
	SDL_Renderer* renderer;
	Camera* c;
	Matrix mTool;

	Matrix rotationYaw;

	Matrix rotationPitch;

public:
	Renderer(Camera* camera, SDL_Window* w);
	SDL_Window* getWindow();
	SDL_Renderer* getRenderer();
	std::array<float, 3> rotatePoint(std::array<float, 3> v);
	std::array<float, 2> projectPoint(std::array<float, 3> v);
	void setRotation(float yaw, float pitch);
	void renderLoop();
	int planeClip(std::array<float, 3> planeNormal, std::array<float, 3> planePosition, std::vector< std::array<float, 3>> points);
	std::array<float, 3> screenClip(std::array<float, 3> p1, std::array<float, 3> p2);
	std::vector<std::vector<std::array<float, 3>>> sortTriangles(std::vector<Triangle> triangles);

	void renderTriangle(std::vector< std::array<float, 3>> points);
	bool shouldRender(std::vector< std::array<float, 3>> points);
	float calculateLight(std::array<float, 3> lightDirection, std::vector<std::array<float, 3>> vertices);
};

#endif