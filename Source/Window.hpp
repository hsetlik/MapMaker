//
//  Window.hpp
//  MapMaker
//
//  Created by Hayden Setlik on 2/23/21.
//

#ifndef Window_hpp
#define Window_hpp
#pragma once
#include "Map.hpp"
//adjust window size here
const int wWidth = 1700;
const int wHeight = 1000;

const int framesPerSecond = 30;
const int frameMs = floor(1000 / framesPerSecond);

class AppWindow
{
public:
    AppWindow(const char* title, int xpos, int ypos, int width, int height, bool fullscreen);
    ~AppWindow() {}
    void handleEvents();
    void update();
    void render();
    void clean();
    bool running() {return isRunning;}
private:
    bool isRunning;
    SDL_Window* window;
    SDL_Renderer* renderer;
    PngSet* allPngs;
    MapHolder* ownedMap;
};
#endif 
