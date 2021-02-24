//
//  Map.cpp
//  MapMaker
//
//  Created by Hayden Setlik on 2/23/21.
//

#include "Map.hpp"

PngSet::PngSet(SDL_Renderer* rend)
{
    auto* grassSurface = IMG_Load("/Users/hayden/Desktop/Programming/SDL_Projects/MapMaker/pngs/grass.png");
    grassPng = SDL_CreateTextureFromSurface(rend, grassSurface);
    SDL_FreeSurface(grassSurface);

    auto* sandSurface = IMG_Load("/Users/hayden/Desktop/Programming/SDL_Projects/MapMaker/pngs/sand.png");
    sandPng = SDL_CreateTextureFromSurface(rend, sandSurface);
    SDL_FreeSurface(sandSurface);

    auto* dirtSurface = IMG_Load("/Users/hayden/Desktop/Programming/SDL_Projects/MapMaker/pngs/dirt.png");
    dirtPng = SDL_CreateTextureFromSurface(rend, dirtSurface);
    SDL_FreeSurface(dirtSurface);

    auto* waterSurface = IMG_Load("/Users/hayden/Desktop/Programming/SDL_Projects/MapMaker/pngs/water.png");
    waterPng = SDL_CreateTextureFromSurface(rend, waterSurface);
    SDL_FreeSurface(waterSurface);
}
int rows = 15;
int columns = 35;
MapHolder::MapHolder(PngSet* set) : pngs(set)
{
    int i = 0;
    for(int q = 0; q < columns; ++q)
    {
        std::vector<Tile> temp;
        int x = q * (HEX_WIDTH * 3/4);
        for(int r = 0; r < rows; ++r)
        {
            int y = r * HEX_HEIGHT;
            if(q % 2 == 0)
                y += HEX_HEIGHT / 2;
            temp.push_back(Tile((TileType)(i % 4), x, y));
            ++i;
        }
        tileGrid.push_back(temp);
    }
}


void MapHolder::clock()
{
    
}

void MapHolder::renderTiles(SDL_Renderer *rend)
{
    for(int x = 0; x < tileGrid.size(); ++x)
    {
        auto vec = tileGrid[x];
        for(int y = 0; y < vec.size(); ++y)
        {
            SDL_RenderCopy(rend, pngs->forType(vec[y].type), NULL, &vec[y].bounds);
        }
    }
}
