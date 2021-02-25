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
#include <algorithm>
const int HEX_WIDTH = 80;
const int HEX_RAD = 40;
const int HEX_HEIGHT = sqrt(3.0) * HEX_RAD;



enum TileType {
    grassland,
    desert,
    ocean,
    beach,
    dirt
};


class Tile
{
public:
    Tile(TileType t, int x, int y, int r, int c) : xCenter(x), yCenter(y), type(t), row(r), column(c)
    {
        int middleRow = 38;
        int middleColumn = 44;
        bounds.x = xCenter;
        bounds.y = yCenter;
        bounds.w = HEX_WIDTH;
        bounds.h = HEX_WIDTH;
        
        auto eqR = r - middleRow;
        auto eqC = c - middleColumn;
        
        xCube = eqC;
        zCube = eqR - (eqC + (eqC & 1)) / 2;
        yCube = -xCube - zCube;
    }
    void offset(Sint32 x, Sint32 y);
    ~Tile() {}
    int xCenter;
    int yCenter;
    void scale(double _scale);
    TileType type;
    SDL_Rect bounds;
    int row;
    int column;
    int xCube, zCube, yCube;
};


#endif /* HexTile_hpp */

