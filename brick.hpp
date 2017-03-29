#ifndef _MMACHINE_BRICK_HPP_
#define _MMACHINE_BRICK_HPP_

#include "vec.h"
#include "mat.h"
#include "mesh.h"
#include "image.h"
#include "orbiter.h"
#include <iostream>
#include <stdlib.h> 

class Brick {
public:
    Brick(int p, Point pn, Point px):position(p), pmin(pn), pmax(px){}
    ~Brick(){};
    int getPosition();
    void setPosition(Point pmn, Point pmx);
    void initMesh();
    Mesh getMesh(){return tempm;}
    

private:
    int position;
    Point pmin;
    Point pmax;
    Mesh tempm;
} ;



#endif
