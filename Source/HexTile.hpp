//
//  HexTile.hpp
//  MapMaker
//
//  Created by Hayden Setlik on 2/23/21.
//
#ifndef HexTile_hpp
#define HexTile_hpp
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <stdio.h>
#include <iostream>
#include <vector>
const int HEX_WIDTH = 80;

enum TileType {
    grassland,
    desert,
    ocean,
    beach,
    dirt
};

//TODO: make this an abstract class and derive for different tile behaviors
class Tile
{
public:
    Tile(TileType t, int x, int y) : xCenter(x), yCenter(y), type(t)
    {
        bounds.x = xCenter - (HEX_WIDTH / 2);
        bounds.y = yCenter - (HEX_WIDTH / 2);
        bounds.w = HEX_WIDTH;
        bounds.h = HEX_WIDTH;
    }
    ~Tile() {}
    int xCenter;
    int yCenter;
    TileType type;
    SDL_Rect bounds;
};


#endif /* HexTile_hpp */
