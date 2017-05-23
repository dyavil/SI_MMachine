#ifndef _MMACHINE_BRICK_HPP_
#define _MMACHINE_BRICK_HPP_

#include "vec.h"
#include "mat.h"
#include "mesh.h"
#include "image.h"
#include "orbiter.h"
#include "wavefront.h"
#include <iostream>
#include <stdlib.h> 
#include <stdio.h>
#include <algorithm>
#include "collidebox.hpp"

class Brick {
public:
    Brick(){};
    Brick(int p, Point pn, Point px):position(p), pmin(pn), pmax(px){};
    ~Brick(){};
    int getPosition();
    void setPosition(Point pmn, Point pmx);
    void initMesh(const Color clr = Color(1, 1, 1), const Color clr2 = Color(1, 1, 1), const bool top = false, const bool right = false, const bool bottom = false, const bool left = false);
    Mesh & getMesh(){return tempm;}
    std::vector<Mesh> & getBorders(){return borders;};
    std::vector<Transform> & getTransforms(){return transforms;};
    float getDistance(const Point & p);
    bool isIn(const Point & p);
    int collideSide(CollideBox & box);
    

private:
    int position;
    Point pmin;
    Point pmax;
    Point pobj1;
    Point pobj2;
    Mesh tempm;
    std::vector<Transform> transforms;
    std::vector<Mesh> borders;
    bool topB;
    bool rightB;
    bool bottomB;
    bool leftB;
    CollideBox topBox;
    CollideBox rightBox;
    CollideBox bottomBox;
    CollideBox leftBox;


} ;



#endif
