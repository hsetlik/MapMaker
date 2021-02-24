//
//  main.cpp
//  MapMaker
//
//  Created by Hayden Setlik on 2/23/21.
// 
#include "Window.hpp"
AppWindow* window = nullptr;

Uint32 frameStart;
int frameDelta;

int main(int argc, const char * argv[])
{
    window = new AppWindow("SDL Window", 600, 600, wWidth, wHeight, false);
    while(window->running())
    {
        frameStart = SDL_GetTicks();
        window->handleEvents();
        window->update();
        window->render();
        frameDelta = SDL_GetTicks() - frameStart;
        if(frameMs > frameDelta)
            SDL_Delay(frameMs - frameDelta);
    }
    window->clean();
    return 0;
}
