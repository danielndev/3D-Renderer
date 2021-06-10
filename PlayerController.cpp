#define _USE_MATH_DEFINES

#include <vector>
#include <SDL.h>
#include "Camera.h"
#include "PlayerController.h"
#include <math.h>
#include <iostream>
#include "WorldController.h"
#include "Matrix.h";
PlayerController::PlayerController(Camera* c, WorldController* wC, SDL_Window* w) {
    window = w;
	pCamera = c;
    worldController = wC;
    SDL_PollEvent(&event);
    previousMousePos[0] = event.motion.x;
    previousMousePos[1] = event.motion.y;

    //c.setPosition(100, 100, 0);
}

void PlayerController::handleInput(const Uint8* keyState) {
    float dx = 0;
    float dz = 0;
    float rx = 0;
    float ry = 0;
    float sensitivity = 1;
    float speed = 0.05;

    int xMouse;
    int yMouse;

    SDL_GetGlobalMouseState(&xMouse, &yMouse);
    //std::cout << previousMousePos[0] - xMouse << ":" << previousMousePos[1] - event.motion.y << std::endl;

    rx += sensitivity * (previousMousePos[0] - xMouse) / 1000;
    ry -= sensitivity * (previousMousePos[1] - yMouse) / 1000;

    
 
    if(SDL_WindowFlags(SDL_WINDOW_MOUSE_FOCUS)) {
        SDL_ShowCursor(SDL_DISABLE);
        SDL_WarpMouseInWindow(window, 800 / 2, 600 / 2);
        SDL_GetGlobalMouseState(&xMouse, &yMouse);
        previousMousePos[0] = xMouse;
        previousMousePos[1] = yMouse;
    }
    else {
        SDL_ShowCursor(SDL_ENABLE);
    }
  

    
    
    
    if (keyState[SDL_SCANCODE_W]) {
        dz = 1;
    }
    if (keyState[SDL_SCANCODE_S]) {
        dz = -1;
    }
    if (keyState[SDL_SCANCODE_A]) {
        dx = -1;
    }
    if (keyState[SDL_SCANCODE_D]) {
        dx = 1;
    }

    while (SDL_PollEvent(&event)) {
        if (event.type == SDL_WINDOWEVENT) {
            switch (event.window.event) {
            case SDL_WINDOWEVENT_CLOSE:   // exit game
                worldController->running = false;
                break;

            default:
                break;
            }
        }
    }



    move(dx * speed, dz * speed);
    rotate(rx, ry);
}

void PlayerController::move(float dx, float dz) {
    
    if (dx != 0 || dz != 0) {

        
        //std::cout << cameraPosition[0] << " : " << cameraPosition[1] << " : " << cameraPosition[2] << std::endl;
        float* cameraPosition = pCamera -> getPosition();
        float yRot = pCamera -> getRotation()[1];

        float yaw = pCamera -> getRotation()[1];
        float pitch = pCamera -> getRotation()[0];

        Matrix rotation({
        {cos(yaw), -sin(yaw), 0},
        {sin(yaw), cos(yaw), 0},
        {0, 0, 0}
        });

        std::array<float, 3> moveDirection = { -dx, -dz,  0 };

        std::array<float, 3> rotatedDirection = rotation.vectorMultiply(moveDirection);
        
        /*float* worldPosition = worldController->getPosition();
        worldController->updateWorldPosition(worldPosition[0] + rotatedDirection[0], worldPosition[1], worldPosition[2]  + rotatedDirection[1]);*/
        pCamera->setPosition(cameraPosition[0] + rotatedDirection[0], cameraPosition[1], cameraPosition[2] + rotatedDirection[1]);
    }
    

    //std::cout << "Moved" << std::endl;

}

void PlayerController::rotate(float rx, float ry) {
    
    if (rx != 0 || ry != 0) {
        float* cameraRotation = pCamera -> getRotation();

        float yaw = pCamera->getRotation()[1];
        float pitch = pCamera->getRotation()[0];

        Matrix rotation({
        {cos(yaw), -sin(yaw), 0},
        {sin(yaw), cos(yaw), 0},
         {0, 0, 0}
        });

        std::array<float, 3> rotateDirection = { -ry, 0,  0 };

        std::array<float, 3> rotatedDirection = rotation.vectorMultiply(rotateDirection);
        pCamera -> setRotation(cameraRotation[0] + ry, cameraRotation[1] + rx, cameraRotation[2] + rotateDirection[1]);

 
    }


    //std::cout << "Moved" << std::endl;

}