#include <vector>
#include <SDL.h>
#include "Camera.h"
#include "WorldController.h"
#ifndef Player_H
#define Player_H

class PlayerController {
private:
	SDL_Event event;
	SDL_Window* window;
	Camera* pCamera;
	WorldController* worldController;
	float previousMousePos[2];
public:
	PlayerController(Camera* c, WorldController* wC, SDL_Window* w);
	void handleInput(const Uint8* keyState);
	void move(float dx, float dz);
	void rotate(float rx, float ry);
};


#endif