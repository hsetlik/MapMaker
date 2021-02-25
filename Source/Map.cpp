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

    auto* water1Surface = IMG_Load("/Users/hayden/Desktop/Programming/SDL_Projects/MapMaker/pngs/water1.png");
    water1Png = SDL_CreateTextureFromSurface(rend, water1Surface);
    SDL_FreeSurface(water1Surface);
    
    auto* water2Surface = IMG_Load("/Users/hayden/Desktop/Programming/SDL_Projects/MapMaker/pngs/water2.png");
    water2Png = SDL_CreateTextureFromSurface(rend, water2Surface);
    SDL_FreeSurface(water2Surface);
    
    auto* water3Surface = IMG_Load("/Users/hayden/Desktop/Programming/SDL_Projects/MapMaker/pngs/water3.png");
    water3Png = SDL_CreateTextureFromSurface(rend, water3Surface);
    SDL_FreeSurface(water3Surface);
    
    auto* water4Surface = IMG_Load("/Users/hayden/Desktop/Programming/SDL_Projects/MapMaker/pngs/water4.png");
    water4Png = SDL_CreateTextureFromSurface(rend, water4Surface);
    SDL_FreeSurface(water4Surface);
    
    currentWater = water1Png;
}
int rows = 75;
int columns = 87;
MapHolder::MapHolder(PngSet* set, SDL_Renderer* r, SDL_Window* w) : pngs(set), zoomLevel(1.3f), rend(r), window(w)
{
    globalYOffset = -50;
    globalXOffset = -50;
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
            temp.push_back(Tile((TileType)(i % 5), x, y, r, q));
            ++i;
        }
        tileGrid.push_back(temp);
    }
    
    mapLimits.x = 0;
    mapLimits.y = 0;
    mapLimits.h = 4000;
    mapLimits.w = 4000;
    
    int wWidth = 0;
    int wHeight = 0;
    SDL_GetWindowSize(window, &wWidth, &wHeight);
    
    wRect.h = wHeight;
    wRect.w = wWidth;
    wRect.x = 0;
    wRect.y = 0;
}

bool MapHolder::rectFullyContained(SDL_Rect *a, SDL_Rect *b)
{
    bool xAllowed = a->x >= b->x;
    bool yAllowed = a->y >= b->y;
    bool wAllowed = a->w <= b->w;
    bool hAllowed = a->h <= b->h;
    if(xAllowed && yAllowed && wAllowed && hAllowed)
        return true;
    else
        return false;
}

void MapHolder::handleMouseMove(SDL_MouseMotionEvent *e)
{
    if(e->state == SDL_BUTTON_LMASK)
    {
        globalXOffset += e->xrel;
        globalYOffset += e->yrel;
        if(globalYOffset > -50)
            globalYOffset = -50;
        if(globalXOffset > -50)
            globalXOffset = -50;
        if(globalXOffset < -1294)
            globalXOffset = -1294;
        if(globalYOffset < -2438)
            globalYOffset = -2438;
    }
}
double depth = 0.02f;
void MapHolder::setView(SDL_MouseWheelEvent *e)
{
    if(zoomLevel + e->y * (depth * zoomLevel) > 0.0)
        zoomLevel += e->y * (depth * zoomLevel);
    if(zoomLevel < 0.44f)
        zoomLevel = 0.44f;
    wRect.h = 1000 / zoomLevel;
    wRect.w = wRect.h * 1.7;
    SDL_RenderSetScale(rend, zoomLevel, zoomLevel);
}
void MapHolder::ensureContained(SDL_Rect *a, SDL_Rect *b)
{
    if(!rectFullyContained(a, b))
    {
        if(a->h > b->h)
            a->h = b->h;
        if(a->w > b->w)
            a->w = b->w;
        if(a->x <= b->x)
            a->x = b->x;
        if(a->y <= b->y)
            a->y = b->y;
        auto xDiff = (b->x + b->w) - (a->x + a->w);
        if(xDiff < 0)
            a->x += xDiff;
        auto yDiff = (b->y + b->h) - (a->y + a->h);
        if(yDiff < 0)
            a->y += yDiff;
    }
}
void MapHolder::clock()
{
    pngs->clockWater();
}

void MapHolder::renderTiles()
{
    for(int x = 0; x < tileGrid.size(); ++x)
    {
        auto vec = tileGrid[x];
        for(int y = 0; y < vec.size(); ++y)
        {
            vec[y].offset(globalXOffset, globalYOffset);
            if(SDL_HasIntersection(&vec[y].bounds, &wRect))  //only rendering tiles which are visible in the window
                SDL_RenderCopy(rend, pngs->forType(vec[y].type), NULL, &vec[y].bounds);
        }
    }
}
