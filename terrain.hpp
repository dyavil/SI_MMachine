#ifndef _MMACHINE_TERRAIN_HPP_
#define _MMACHINE_TERRAIN_HPP_

#include "vec.h"
#include "mat.h"
#include <cmath>
#include "mesh.h"
#include "image.h"
#include "orbiter.h"
#include "brick.hpp"
#include <iostream>
#include <stdlib.h>
#include <fstream>
#include <string>

class Terrain {
public:
    Terrain(){};
    Terrain(int nb, Point pmn, Point pmx);
    Terrain(int h, int w, Point pmn, Point pmx);
    Terrain(std::string fileName);
    ~Terrain(){};
    Mesh & getMesh() {return mesh;}
    std::vector<Brick> & getBricks();
    int getSize(){return size;}
    void project(const Point& from, Point& to, Vector& n) const;
    Brick & getBrickOn(const Point& p);
    int whosAhead(const Point& p1, const Point& p2);
    Point & getPmin(){return pmin;};
    Point & getPmax(){return pmax;};
    Point & getSpawn(){return spawnPoint;};

private:
    Mesh mesh;
    int size;
    std::vector<Brick> bricks;
    Point pmin;
    Point pmax;
    Point spawnPoint;
} ;



#endif
