//
//  Map.h
//  MapMaker
//
//  Created by Hayden Setlik on 2/23/21.
//
#ifndef Map_hpp
#define Map_hpp
#pragma once
#include "HexTile.hpp"

const int WATER_SPEED = 10;

//update this class to load any new PNGs for overlays/more tile types, etc;
class PngSet
{
public:
    PngSet(SDL_Renderer* rend);
    ~PngSet() {}
     SDL_Texture* grassPng;
     SDL_Texture* sandPng;
     SDL_Texture* dirtPng;
     SDL_Texture* water1Png;
     SDL_Texture* water2Png;
     SDL_Texture* water3Png;
     SDL_Texture* water4Png;
     SDL_Texture* currentWater;
     SDL_Texture* forType(TileType t)
    {
        switch(t)
        {
            case grassland:
                return grassPng;
            case beach:
                return sandPng;
            case desert:
                return sandPng;
            case ocean:
                return currentWater;
            case dirt:
                return dirtPng;
        }
    }
    void clockWater()
    {
        ++waterCounter;
        if(waterCounter % WATER_SPEED == 0)
            incPhase();
    }
    void incPhase()
    {
        switch(waterPhase)
        {
            case 1:
                waterPhase = 2;
                currentWater = water2Png;
                break;
            case 2:
                waterPhase = 3;
                currentWater = water3Png;
                break;
            case 3:
                waterPhase = 4;
                currentWater = water4Png;
                break;
            case 4:
                waterPhase = 5;
                currentWater = water3Png;
                break;
            case 5:
                waterPhase = 6;
                currentWater = water2Png;
                break;
            case 6:
                waterPhase = 1;
                currentWater = water1Png;
                break;
        }
    }
    Uint32 waterCounter = 0;
    int waterPhase = 1;
};


class MapHolder
{
public:
    MapHolder(PngSet* assets, SDL_Renderer* r, SDL_Window* w);
    ~MapHolder() {}
    //call at the end of every frame to update stuff
    void clock();
    void setView(SDL_MouseWheelEvent* e);
    void handleMouseMove(SDL_MouseMotionEvent* e);
    void renderTiles();
    bool rectFullyContained(SDL_Rect* a, SDL_Rect* b);
    void ensureContained(SDL_Rect* a, SDL_Rect* b);
    PngSet* pngs;
    double zoomLevel; //1.0 means the width of each tile is 80px, < 1 means each tile is smaller, >1 is larger, etc;
    SDL_Rect mapLimits;
    std::vector<std::vector<Tile>> tileGrid;
    SDL_Renderer* rend;
    SDL_Window* window;
    SDL_Rect wRect;
    Sint32 globalXOffset;
    Sint32 globalYOffset;
};

#endif
