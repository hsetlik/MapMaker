//
//  HexTile.cpp
//  MapMaker
//
//  Created by Hayden Setlik on 2/23/21.
//

#include "HexTile.hpp"

void Tile::scale(double _scale)
{
    bounds.h = HEX_WIDTH * _scale;
    bounds.w = HEX_WIDTH * _scale;
}

void Tile::offset(Sint32 x, Sint32 y)
{
    bounds.x = xCenter + x;
    bounds.y = yCenter + y;
}
