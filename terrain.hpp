#ifndef _MMACHINE_TERRAIN_HPP_
#define _MMACHINE_TERRAIN_HPP_

#include "vec.h"
#include "mat.h"
#include "mesh.h"
#include "image.h"
#include "orbiter.h"
#include "brick.hpp"
#include <iostream>
#include <stdlib.h> 

class Terrain {
public:
    Terrain(){};
    Terrain(int h, int w, Point pmn, Point pmx);
    ~Terrain(){};
    Mesh getMesh() {return mesh;}
    std::vector<Brick> getBricks();
    Brick getBrickOn(Point pmin, Point pmax);
    int getSize(){return size;}

private:
    Mesh mesh;
    int size;
    std::vector<Brick> bricks;
    Point pmin;
    Point pmax;
} ;



#endif
