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

//update this class to load any new PNGs for overlays/more tile types, etc;
class PngSet
{
public:
    PngSet(SDL_Renderer* rend);
    ~PngSet() {}
     SDL_Texture* grassPng;
     SDL_Texture* sandPng;
     SDL_Texture* dirtPng;
     SDL_Texture* waterPng;
};

class MapHolder
{
public:
    MapHolder(PngSet* assets);
    ~MapHolder() {}
    //call at the end of every frame to update stuff
    void clock();
    void renderTiles(SDL_Renderer* rend);
    PngSet* pngs;
    double zoomLevel; //1.0 means the width of each tile is 80px, < 1 means each tile is smaller
    std::vector<std::vector<Tile>> tileGrid;
};

#endif
