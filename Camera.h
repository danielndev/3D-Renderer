#include <vector>
#include <array>
#ifndef CAMERA_H
#define CAMERA_H

class Camera {
	

private:
	float position[3];
	float rotation[3];
	std::vector<std::array<float, 3>> rotationMatrix = { { 1, 0, 0 }  , { 0, 1, 0 } , { 0, 0, 1 } };

public:
	
	float fov;
	Camera();
	float* getPosition();
	float* getRotation();

	float* getOrientations();
	std::vector<std::array<float, 3>> multiplyMatrices(std::vector<std::array<float, 3>> a, std::vector<std::array<float, 3>> b);
	void setPosition(float x, float y, float z);
	void setRotation(float x, float y, float z);
};

#endif
