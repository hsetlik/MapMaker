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
int rows = 10;
int columns = 15;
MapHolder::MapHolder(PngSet* set) : pngs(set)
{
    for(int x = 0; x < columns; ++x)
    {
        std::vector<Tile> temp;
        for(int y = 0; y < rows; ++y)
        {
            int xPos = x * HEX_WIDTH;
            if(y % 2 ==0)
                xPos += (HEX_WIDTH / 2);
            int yPos = y * HEX_WIDTH;
            temp.push_back(Tile(grassland, xPos, yPos));
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
            SDL_RenderCopy(rend, pngs->grassPng, NULL, &vec[y].bounds);
        }
    }
}
