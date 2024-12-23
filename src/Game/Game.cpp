//
// Created by Konrad Kurzak on 05/10/2024.
//

#include "Game.h"
#include "../ECS/ECS.h"
#include "../Logger/Logger.h"
#include <iostream>
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <glm/glm.hpp>


Game::Game() {
    isRunning = false;
    Logger::Log("Game constructor called");
}


Game::~Game() {
    Logger::Log("Game destructor called");
}


void Game::Initialize() {

    if(SDL_Init(SDL_INIT_EVERYTHING) != 0) {
        Logger::Err("Error initializing SDL");
        return;
    }

    //setting up the screen size (display mode)
    SDL_DisplayMode display_mode;
    SDL_GetCurrentDisplayMode(0, &display_mode);
    winWidth = display_mode.w;
    winHeight = display_mode.h;


    window = SDL_CreateWindow(
    "Engine",
    SDL_WINDOWPOS_CENTERED,
    SDL_WINDOWPOS_CENTERED,
    winWidth,
    winHeight,
    SDL_WINDOW_RESIZABLE);
    if(!window) {
        Logger::Err("Error creating SDL window");
        return;
    }

    renderer = SDL_CreateRenderer(window, -1, 0);
    if(!renderer) {
        Logger::Err("Error creating SDL renderer");
        return;
    }

    SDL_SetWindowFullscreen(window, SDL_WINDOW_FULLSCREEN);

    isRunning = true;
}


void Game::Setup() {
    //TODO:
    //Entity tank = registry.CreateEntity();
    //tank.AddComponent<TransformComponent>();
    //tank.AddComponent<BoxColliderComponent>();
    //tank.AddComponent<SpriteComponent>(./assets/images/...);
}


void Game::Run() {

    Setup();

    while(isRunning) {
        ProcessInput();
        Update();
        Render();
    }
}


void Game::ProcessInput() {
    SDL_Event sdl_event;
    while(SDL_PollEvent(&sdl_event)){
        switch(sdl_event.type) {
            case SDL_QUIT:
                isRunning = false;
            break;
            case SDL_KEYDOWN:
                if(sdl_event.key.keysym.sym == SDLK_ESCAPE) {
                    isRunning = false;
                }
            break;
        }
    };
}


void Game::Update() {
    //if we are too fast, we have to waste some time to reach target time for each frame to take (MILLISECS_PER_FRAME)
    int timeToWait = MILLISECS_PER_FRAME - (SDL_GetTicks() - millisecsPrevFrame);
    if(timeToWait > 0 && timeToWait < MILLISECS_PER_FRAME){
        SDL_Delay(timeToWait);
    }

    //Difference in ticks from last frame, converted from milliseconds to seconds
    double deltaTime = (SDL_GetTicks() - millisecsPrevFrame) / 1000.0f;

    //store the current frame time
    millisecsPrevFrame = SDL_GetTicks();

    //TODO:
    //movementSystem.Update();
    //CollisionSystem.Update();
    //DamageSystem.Update();
}


void Game::Render() {
    SDL_SetRenderDrawColor(renderer, 21, 21, 21, 255);
    SDL_RenderClear(renderer);

    //TODO: Render game objects

    SDL_RenderPresent(renderer);
}


void Game::Destroy() {
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_Quit();
}




