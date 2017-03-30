#ifndef _MMACHINE_CBOX_HPP_
#define _MMACHINE_CBOX_HPP_

#include "vec.h"
#include "mat.h"
#include <stdlib.h> 

class CollideBox{
public: 
	CollideBox(){};
	CollideBox(Point p1, Point p2):pmin(p1), pmax(p2){};
	~CollideBox(){};

	bool collide(CollideBox & box) const;
	void update(Vector v){pmin = pmin + v ; pmax = pmax + v;}
	Point & getPmin(){return pmin;}
	Point & getPmax(){return pmax;}

private:
	Point pmin;
	Point pmax;
};



#endif