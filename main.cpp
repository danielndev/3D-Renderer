#include<iostream>
#include<SDL.h>
#include<vector>
#include<array>
#include<algorithm>
#include<thread>
#include "Camera.h";
#include "Renderer.h"
#include "Object.h"
#include"PlayerController.h"
#include"WorldController.h"
#include"Matrix.h"

void renderLoop(Renderer* renderer, WorldController* wController, Camera* camera) {
	//while (wController->running) {
		SDL_SetRenderDrawColor(renderer->getRenderer(), 255, 255, 255, 255);
		SDL_RenderClear(renderer->getRenderer());
		std::vector<Object> objects = wController->getObjects();
		std::vector<std::vector<std::array<float, 3>>> sortedTriangles;
		std::vector<std::vector<std::array<float, 3>>> addedTriangles;

		

		float  yaw = camera->getRotation()[1];
		float pitch = camera->getRotation()[0];
		renderer->setRotation(yaw, pitch);

		for (int i = 0; i < objects.size(); i++) {
			//obj.renderFaces(renderer);
			addedTriangles = renderer->sortTriangles(objects[i].getTriangles());
			sortedTriangles.insert(sortedTriangles.end(), addedTriangles.begin(), addedTriangles.end());
		}

		std::sort(sortedTriangles.begin(), sortedTriangles.end(), [](std::vector<std::array<float, 3>>  t1, std::vector<std::array<float, 3>>  t2) {
			float z1 = (t1[0][2] + t1[1][2] + t1[2][2]) / 3;
			float z2 = (t2[0][2] + t2[1][2] + t2[2][2]) / 3;
			return z1 < z2;
			});
		for (int i = 0; i < sortedTriangles.size(); i++) {
			renderer->renderTriangle(sortedTriangles[i]);
		}

		SDL_RenderPresent(renderer->getRenderer());
	//}

}

void logicLoop(WorldController* wController, PlayerController* pController, const Uint8* keyState) {
	//while (wController->running) {

		pController->handleInput(keyState);

		wController->handleLogic();
		
	
		
	//}
}

int main(int argc, char *argv[]) {
	if (SDL_Init(SDL_INIT_EVERYTHING) < 0) {
		std::cout << "STL could not initialise! SDL Error " << SDL_GetError() << std::endl;
	}
	const Uint8* keyState = SDL_GetKeyboardState(NULL);
	int w = 1920;
	int h = 1080;

	const int fps = 60;

	int framesElapsed = 0;
	SDL_Window* window = SDL_CreateWindow("Physics Engine", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, w, h, 0);


	Camera camera;
	Renderer renderer(&camera, window);
	WorldController* wController = new WorldController();


	PlayerController pController(&camera, wController, window);
	
	
	
	/*while (wController->running) {
		
		renderLoop(renderer, wController, camera);
		
		SDL_Delay(30);
		std::cout << framesElapsed++ << std::endl;
	}
	*/
	
	//std::thread graphics(renderLoop, &renderer, wController, &camera);
	//logicLoop(wController, &pController);

	//std::thread logic(logicLoop, wController, &pController, keyState);

	while (wController->running) {
		Uint64 start = SDL_GetPerformanceCounter();
		renderLoop(&renderer, wController, &camera);
		logicLoop(wController, &pController, keyState);

		Uint64 end = SDL_GetPerformanceCounter();
		float elapsedMS = (end - start) / (float)SDL_GetPerformanceFrequency() * 1000.0f;
		// Cap to 60 FPS
		if (1000 / fps - elapsedMS > 0) {
			SDL_Delay(floor(1000 / fps - elapsedMS));
		}
	}
	
	/*SDL_DestroyWindow(window);
	SDL_Quit();*/

	char str[256];
	std::cin.get(str, 256);
	return EXIT_SUCCESS;
}






