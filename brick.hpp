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
    //constructeur de brick, avec ses points extremes, son indice de position, son arrete objectif et ses bords
    Brick(int p, Point pn, Point px, const bool top, const bool right, const bool bottom, const bool left, const std::string objective = "right", const bool isend = false);
    ~Brick(){};
    //retourne la position d'une brick, plus elle est élevé plus elle est prohe de la fin du circuit
    int getPosition();
    void setPosition(Point pmn, Point pmx);
    //méthode séparée du constructeur pour initilisé une brick
    void initMesh(const bool top = false, const bool right = false, const bool bottom = false, const bool left = false);
    Mesh & getMesh(){return tempm;}
    std::vector<Mesh> & getBorders(){return borders;};
    std::vector<Transform> & getTransforms(){return transforms;};

    //renvoie la distance entre p et l'arrete objectif
    float getDistance(const Point & p);
    //renvoie true si le point est dans la brick
    bool isIn(const Point & p);
    //renvoie true si la brick appartient à la ligne d'arrivée
    bool getIsEnd(){return isEnd;};

    //test de collision entre les bords et la box en parametre
    //l'entier retourné dépend du bord touché
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
    bool isEnd;
    CollideBox topBox;
    CollideBox rightBox;
    CollideBox bottomBox;
    CollideBox leftBox;


} ;



#endif
