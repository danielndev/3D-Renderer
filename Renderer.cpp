#include "Renderer.h"
#include <iostream>
#include "SDL2_gfxPrimitives.h"
#include <math.h>
#include <algorithm>
#include "Camera.h"
#include "Matrix.h";
#include "Triangle.h"

Renderer::Renderer(Camera* camera, SDL_Window* w){
	window = w;
	renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
	c = camera;

	if (!renderer) {
		std::cout << "Failed to create renderer: " << SDL_GetError() << std::endl;
	}

	SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
	SDL_RenderClear(renderer);
	SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);

	srand(time(NULL));
	SDL_RenderPresent(renderer);
}

std::vector<std::vector<std::array<float, 3>>> Renderer::sortTriangles(std::vector<Triangle> triangles) {
	std::vector<std::vector<std::array<float, 3>>> translatedTriangles;
	float* cameraPosition = c->getPosition();
	for (int i = 0; i < triangles.size(); i++) {
		std::vector< std::array<float, 3>> rotatedPoints;
		for (int j = 0; j < triangles[i].getVertices().size(); j++) {
			//rotatedPoints.push_back({ triangles[i].getVertices()[j][0] - cameraPosition[0], triangles[i].getVertices()[j][1] - cameraPosition[1], triangles[i].getVertices()[j][2] - cameraPosition[2] });

			rotatedPoints.push_back(rotatePoint({ triangles[i].getVertices()[j][0], triangles[i].getVertices()[j][1], triangles[i].getVertices()[j][2] }));
		}

		if (shouldRender(rotatedPoints) && planeClip({ 0, 0, 1 }, { 0, 0, -0.01 }, rotatedPoints) == 1) {
			translatedTriangles.push_back(rotatedPoints);
		}
	}
	return translatedTriangles;
}



void Renderer::renderTriangle(std::vector<std::array<float, 3>> points) {
	std::vector< std::array<float, 2>> projectedPoints;
	
		for (int i = 0; i < points.size(); i++) {
			projectedPoints.push_back(projectPoint(points[i]));
		}

		float lightColourR = 200;
		float lightColourG = 200;
		float lightColourB = 200;
		float lightIntensity = calculateLight({0 , -1, 0 }, points);
		
		filledTrigonRGBA(renderer, 
			projectedPoints[0][0], projectedPoints[0][1],
			projectedPoints[1][0], projectedPoints[1][1],
			projectedPoints[2][0], projectedPoints[2][1],
			lightIntensity * lightColourR, lightIntensity * lightColourG, lightIntensity * lightColourB, 255
		);

		
	
}

bool Renderer::shouldRender(std::vector< std::array<float, 3>> points) {
	//Decides whether to draw the triangle or not;
	std::array<float, 3> triangleNormal = mTool.vector3CrossProduct(mTool.vectorMinus(points[1], points[0]), mTool.vectorMinus(points[2], points[0]));
	if (mTool.dotProduct(mTool.vectorNormalize(triangleNormal), points[0]) < 0) {
		return true;
	}

	return true;
}

void Renderer::setRotation(float yaw, float pitch) {
	rotationYaw = Matrix({
		{cos(yaw), 0, sin(yaw)},
		{ 0, 1, 0 },
		{ -sin(yaw), 0, cos(yaw)}
		}
	);

	rotationPitch = Matrix({
		{1, 0, 0},
		{ 0, cos(pitch), -sin(pitch)},
		{ 0, sin(pitch), cos(pitch)}
		}
	);
}

std::array<float,3> Renderer::rotatePoint(std::array<float, 3> v) {
	//translate point first
	std::array<float, 3> translated = { v[0] - c->getPosition()[0], v[1] - c->getPosition()[1] , v[2] - c->getPosition()[2] };

	std::array<float, 3> rotatedYaw = rotationYaw.vectorMultiply(translated);
	std::array<float, 3> rotated = rotationPitch.vectorMultiply(rotatedYaw);

	return rotated;
}

std::array<float, 2> Renderer::projectPoint(std::array<float, 3> v) {
	float near = 0.1;
	float far = 1000;
	float fov = M_PI_2;
	float aspectRatio = 1920 / 1080;
	float e = 1 / tanf(fov / 2);


	Matrix projection({
	{aspectRatio * e, 0, 0, 0},
	{0, e, 0, 0},
	{0, 0, far / (far - near), 1},
	{0, 0, -near * far / (far - near), 0}
		}
	);
	std::array<float, 3> projected;
	
	projected[0] = v[0] * projection.matrix[0][0] + v[1] * projection.matrix[1][0] + v[2] * projection.matrix[2][0] + projection.matrix[3][0];
	projected[1] = v[0] * projection.matrix[0][1] + v[1] * projection.matrix[1][1] + v[2] * projection.matrix[2][1] + projection.matrix[3][1];
	projected[2] = v[0] * projection.matrix[0][2] + v[1] * projection.matrix[1][2] + v[2] * projection.matrix[2][2] + projection.matrix[3][2];
	float w = v[0] * projection.matrix[0][3] + v[1] * projection.matrix[1][3] + v[2] * projection.matrix[2][3] + projection.matrix[3][3];

	if (w != 0) {
		projected[0] /= w;
		projected[1] /= w;
		projected[2] /= w;
	}

	std::array<float, 2> output = { (projected[0] + 1) * 1920 / 2, (projected[1] + 1) * 1080 / 2};


	return output;
}

SDL_Window* Renderer :: getWindow() {
	return window;
}

SDL_Renderer* Renderer :: getRenderer() {
	return renderer;
}

void Renderer::renderLoop() {
	
}

int Renderer::planeClip(std::array<float, 3> planeNormal, std::array<float, 3> planePosition, std::vector< std::array<float, 3>> points) {
	float d = -mTool.dotProduct(mTool.vectorNormalize(planeNormal), planePosition);


	float t1 = (-d - mTool.dotProduct(planeNormal, points[0])) / mTool.dotProduct(planeNormal, mTool.vectorMinus(points[1], points[0]));
	float t2 = (d - mTool.dotProduct(planeNormal, points[1])) / mTool.dotProduct(planeNormal, mTool.vectorMinus(points[2], points[1]));
	float t3 = (d - mTool.dotProduct(planeNormal, points[2])) / mTool.dotProduct(planeNormal, mTool.vectorMinus(points[0], points[2]));

	std::array<float, 3> intersection1 = mTool.vectorAdd(points[0], mTool.scalerMultiply(mTool.vectorMinus(points[1], points[0]), t1));
	std::array<float, 3> intersection2 = mTool.vectorAdd(points[1], mTool.scalerMultiply(mTool.vectorMinus(points[2], points[1]), t2));
	std::array<float, 3> intersection3 = mTool.vectorAdd(points[2], mTool.scalerMultiply(mTool.vectorMinus(points[0], points[2]), t3));
	//std::array<float, 3> normalVector = mTool.vector3CrossProduct(mTool.vectorMinus(f.vertices[0], f.vertices[1]), mTool.vectorMinus(f.vertices[2], f.vertices[3]));
	
	std::vector< std::array<float, 3>> output;
	if (mTool.dotProduct(planeNormal, points[0]) - mTool.dotProduct(planeNormal, planePosition) >= 0) {
		return 0;
	}

	if (mTool.dotProduct(planeNormal, points[1]) - mTool.dotProduct(planeNormal, planePosition) >= 0) {
		return 0;
	}

	if (mTool.dotProduct(planeNormal, points[2]) - mTool.dotProduct(planeNormal, planePosition) >= 0) {
		return 0;
	}
	


	return 1;
}

float Renderer::calculateLight(std::array<float, 3> lightDirection, std::vector<std::array<float, 3>> vertices) {
	float maxLight = 0.8;
	float minLight = 0.05;

	
	std::array<float, 3> triangleNormal = mTool.vector3CrossProduct(mTool.vectorMinus(vertices[1], vertices[0]), mTool.vectorMinus(vertices[2], vertices[0]));
	triangleNormal = mTool.vectorNormalize(triangleNormal);
	float output = (mTool.dotProduct(triangleNormal, lightDirection) + 1) / 2;
	if (output > maxLight) {
		output = maxLight;
	}
	else if (output < minLight) {
		output = minLight;
	}
	

	return output;
}

//Handles clip with viewers screen;



