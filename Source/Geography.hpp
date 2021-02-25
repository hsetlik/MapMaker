//
//  Geography.hpp
//  MapMaker
//
//  Created by Hayden Setlik on 2/25/21.
//

#ifndef Geography_hpp
#define Geography_hpp
#include "HexTile.hpp"

class LandHandler
{
public:
    LandHandler(std::vector<std::vector<Tile>>* t);
    ~LandHandler() {}
    void clock();
    std::vector<Tile*> vecXZ(int x, int z);
    std::vector<Tile*> vecXY(int x, int y);
    std::vector<Tile*> vecZY(int z, int y);
    Tile* withX(std::vector<Tile*> vec);
    Tile* withZ(std::vector<Tile*> vec);
    Tile* withY(std::vector<Tile*> vec);
    Tile* withCubes(int x, int z, int y);
    std::vector<std::vector<Tile>>* tiles;
    std::vector<std::vector<Tile*>> xAxis;
    std::vector<std::vector<Tile*>> zAxis;
    std::vector<std::vector<Tile*>> yAxis;
};
#endif /* Geography_hpp */
