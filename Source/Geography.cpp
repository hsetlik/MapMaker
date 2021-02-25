//
//  Geography.cpp
//  MapMaker
//
//  Created by Hayden Setlik on 2/25/21.
//

#include "Geography.hpp"

LandHandler::LandHandler(std::vector<std::vector<Tile>>* t) : tiles(t)
{
    for(auto& r : *tiles)
    {
        std::vector<Tile*> vec;
        for(auto& c : r)
        {
            vec.push_back(&c);
        }
        std::vector<Tile*> xVec = vec;
        std::vector<Tile*> zVec = vec;
        std::vector<Tile*> yVec = vec;
        
        std::sort(xVec.begin(), xVec.end(), []( const Tile* lhs, const Tile* rhs )
        {
            return lhs->xCube < rhs->xCube;
        });
        
        std::sort(zVec.begin(), zVec.end(), []( const Tile* lhs, const Tile* rhs )
        {
            return lhs->zCube < rhs->zCube;
        });
        
        std::sort(yVec.begin(), yVec.end(), []( const Tile* lhs, const Tile* rhs )
        {
            return lhs->yCube < rhs->yCube;
        });
        
        xAxis.push_back(xVec);
        zAxis.push_back(zVec);
        yAxis.push_back(yVec);
    }
}

void LandHandler::clock()
{
    
}

std::vector<Tile*> LandHandler::vecXZ(int x, int z)
{
    std::vector<Tile*> vec;
    for(auto outer : xAxis)
    {
        for(auto* inner : outer)
        {
            if(inner->xCube == x && inner->zCube == z)
                vec.push_back(inner);
        }
    }
    return vec;
}
std::vector<Tile*> LandHandler::vecXY(int x, int y)
{
    std::vector<Tile*> vec;
    for(auto outer : xAxis)
    {
        for(auto* inner : outer)
        {
            if(inner->xCube == x && inner->yCube == y)
                vec.push_back(inner);
        }
    }
    return vec;
}
std::vector<Tile*> LandHandler::vecZY(int z, int y)
{
    std::vector<Tile*> vec;
    for(auto outer : zAxis)
    {
        for(auto* inner : outer)
        {
            if(inner->zCube == z && inner->yCube == y)
                vec.push_back(inner);
        }
    }
    return vec;
}

Tile* LandHandler::withCubes(int x, int z, int y)
{
    Tile* t = nullptr;
    
    auto commonXZ = vecXZ(x, z);
    for(auto* test : commonXZ)
    {
        if(test->yCube == y)
            t = test;
    }
    return t;
}

