//
//  Window.cpp
//  MapMaker
//
//  Created by Hayden Setlik on 2/23/21.
//

#include "Window.hpp"

AppWindow::AppWindow(const char* title, int xpos, int ypos, int width, int height, bool fullscreen)
{
    int flags = 0;
        if(fullscreen){
            flags = SDL_WINDOW_FULLSCREEN;
        }
        if(SDL_Init(SDL_INIT_EVERYTHING) == 0){
            IMG_Init(IMG_INIT_PNG);
            printf("SDL_Img initialized\n");
            //verifies that SDL started up correctly
            printf("SDL Initialized\n");
            window = SDL_CreateWindow(title, xpos, ypos, width, height, flags);
            if(window){
                //SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
                printf("Window Created\n");
            }
            renderer = SDL_CreateRenderer(window, -1, 0);
            if(renderer){
                SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
                printf("Renderer Created\n");
            }
            isRunning = true;
            allPngs = new PngSet(renderer);
            printf("Images Loaded\n");
            ownedMap = new MapHolder(allPngs);
        }
}

void AppWindow::handleEvents()
{
    SDL_Event event;
        SDL_PollEvent(&event);
        switch (event.type) {
            case SDL_QUIT:
                isRunning = false;
                break;
            case SDL_MOUSEBUTTONDOWN:
                //do stuff when the mouse is clicked
                break;
            // check for more events with more case statements here
            default:
                break;
        }
}

void AppWindow::update()
{
    //update logic in here
    ownedMap->clock();
}

void AppWindow::render()
{
    SDL_RenderClear(renderer);
    //TODO: renderTiles doesn't do anything yet
    ownedMap->renderTiles(renderer);
    SDL_RenderPresent(renderer);
}

void AppWindow::clean()
{
    SDL_DestroyWindow(window);
    SDL_DestroyRenderer(renderer);
    delete allPngs;
    IMG_Quit();
    SDL_Quit();
    printf("App Cleaned\n");
}

