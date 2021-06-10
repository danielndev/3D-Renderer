#include <vector>
#include <array>
#include "Object.h";
#include "Camera.h";

#ifndef WORLDCONTROLLER_H
#define WORLDCONTROLLER_H

class WorldController {
private:
	std::vector<Object> worldObjects;
	Camera playerCamera;
	float position[3] = { 0, 0, 0 };
	
public:
	bool running = true;
	WorldController();
	void handleLogic();
	void createObject(float x, float y, float z, float s, std::string filename);
	void updateWorldPosition(float x, float y, float z);
	std::vector<Object> getObjects();
	float* getPosition();
	void updateWorldRotation(std::vector<std::array<float, 3>> rMatrix);
	void rotateAboutX(float a);
	void rotateAboutY(float a);
	void rotateAboutZ(float a);
	void setObjects(std::vector<Object> newObjs);
};

#endif
