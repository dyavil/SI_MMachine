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
    Brick(int p, Point pn, Point px, const bool top, const bool right, const bool bottom, const bool left, const std::string objective = "right");
    ~Brick(){};
    int getPosition();
    void setPosition(Point pmn, Point pmx);
    void initMesh(const bool top = false, const bool right = false, const bool bottom = false, const bool left = false);
    Mesh & getMesh(){return tempm;}
    std::vector<Mesh> & getBorders(){return borders;};
    std::vector<Transform> & getTransforms(){return transforms;};
    float getDistance(const Point & p);
    bool isIn(const Point & p);
    int collideSide(CollideBox & box);
    

private:
    void setObjective(std::string border);
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
