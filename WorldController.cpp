#include <vector>
#include <array>
#include <string>
#include "WorldController.h";
#include "Object.h";
#include "Camera.h";

WorldController::WorldController() {
	int dimension = 2 ;
	/*
	for (int i = 0; i < dimension; i ++) {
		for (int j = 0; j < dimension; j++) {
			createObject(i * 0.4, 0.2, j * 0.4, 0.1, "sphere.obj");
		}
	}
	*/

	createObject(0.5, -0.1,1 + 0.1, 0.2, "sphere.obj");
	//createObject(2, 0, 2, 0.1, "cube.obj");
}

void WorldController::handleLogic() {
	for (int i = 0; i < worldObjects.size(); i++) {
		worldObjects[i].setPosition(worldObjects[i].getPosition()[0] + 0.1, worldObjects[i].getPosition()[1], worldObjects[i].getPosition()[2]);
	}

}

void WorldController::createObject(float x, float y, float z, float s, std::string filename) {
	Object obj(x, y, z, s, filename);
	worldObjects.push_back(obj);
}


std::vector<Object> WorldController::getObjects() {
	return worldObjects;
}

void WorldController::setObjects(std::vector<Object> newObjs) {
	worldObjects = newObjs;
}


float* WorldController::getPosition() {
	return position;
}