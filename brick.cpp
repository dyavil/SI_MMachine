#include "brick.hpp"

int Brick::getPosition(){
	return position;
}


void Brick::initMesh(const Color clr, const Color clr2, const bool top, const bool right, const bool bottom, const bool left){
	tempm = Mesh(GL_TRIANGLES);
	
	float r = ((float) rand() / (RAND_MAX));
	float r1 = ((float) rand() / (RAND_MAX));
	float r2 = ((float) rand() / (RAND_MAX));
	tempm.color(clr2);
	pobj1 = pmax;
	pobj2 = Point(pmax.x, pmin.y, 0);
	/*unsigned int a = tempm.vertex(pmin);
	unsigned int b = tempm.vertex(pmax);
	unsigned int c = tempm.vertex(pmin.x, pmax.y, 0);
	unsigned int d = tempm.vertex(pmax.x, pmin.y, 0);
	tempm.triangle(a, b, c);
	tempm.triangle(a, d, b);*/

	/////////////////////////////////////////////

	float diffy = pmax.y - pmin.y;
	float diffx = pmax.x - pmin.x;
	float side_weight_y = diffy/(float)12;
	float side_weight_x = diffx/(float)12;

	

	//arrete haute

	tempm.normal(0, 1, 0);
	unsigned int ah1 = tempm.vertex(pmin.x, pmax.y-side_weight_y, 0);
	if (top)
	{
		r = ((float)rand() / (RAND_MAX));
		r1 = ((float)rand() / (RAND_MAX));
		r2 = ((float)rand() / (RAND_MAX));
		tempm.normal(r, r1, r2);
	}else tempm.normal(1, 1, 1); 
	unsigned int ah2 = tempm.vertex(pmax);
	if(top)
	{
		r = ((float)rand() / (RAND_MAX));
		r1 = ((float)rand() / (RAND_MAX));
		r2 = ((float)rand() / (RAND_MAX));
		tempm.normal(r, r1, r2);
	}else tempm.normal(0, 1, 1);
	unsigned int ah3 = tempm.vertex(pmin.x, pmax.y, 0);
	
	tempm.normal(1, 0, 1);
	unsigned int ah4 = tempm.vertex(pmax.x, pmax.y-side_weight_y, 0);
	tempm.triangle(ah1, ah2, ah3);
	tempm.triangle(ah1, ah4, ah2);
	topBox = CollideBox(Point(pmin.x, pmax.y-side_weight_y, 0), pmax);

	//arrete basse
	if (bottom)
	{
		r = ((float)rand() / (RAND_MAX));
		r1 = ((float)rand() / (RAND_MAX));
		r2 = ((float)rand() / (RAND_MAX));
		tempm.normal(r, r1, r2);
	}else tempm.normal(1, 0, 1);
	unsigned int ab1 = tempm.vertex(pmin);
	tempm.normal(0, 1, 1);
	unsigned int ab2 = tempm.vertex(pmax.x, pmin.y+side_weight_y, 0);
	tempm.normal(1, 1, 1);
	unsigned int ab3 = tempm.vertex(pmin.x, pmin.y+side_weight_y, 0);
	if (bottom)
	{
		r = ((float)rand() / (RAND_MAX));
		r1 = ((float)rand() / (RAND_MAX));
		r2 = ((float)rand() / (RAND_MAX));
		tempm.normal(r, r1, r2);
	}else tempm.normal(0, 1, 0);
	unsigned int ab4 = tempm.vertex(pmax.x, pmin.y, 0);
	tempm.triangle(ab1, ab2, ab3);
	tempm.triangle(ab1, ab4, ab2);
	bottomBox = CollideBox(pmin, Point(pmax.x, pmin.y+side_weight_y, 0));
	
	

	//arrete droite
	tempm.normal(1, 1, 1);
	unsigned int ad1 = tempm.vertex(pmax.x-side_weight_x, pmin.y, 0);
	if (right)
	{
		r = ((float)rand() / (RAND_MAX));
		r1 = ((float)rand() / (RAND_MAX));
		r2 = ((float)rand() / (RAND_MAX));
		tempm.normal(r, r1, r2);
	}
	else tempm.normal(0, 1, 0);
	unsigned int ad2 = tempm.vertex(pmax);
	tempm.normal(1, 0, 1);
	unsigned int ad3 = tempm.vertex(pmax.x-side_weight_x, pmax.y, 0);
	if (right)
	{
		r = ((float)rand() / (RAND_MAX));
		r1 = ((float)rand() / (RAND_MAX));
		r2 = ((float)rand() / (RAND_MAX));
		tempm.normal(r, r1, r2);
	}
	else tempm.normal(0, 1, 1);
	unsigned int ad4 = tempm.vertex(pmax.x, pmin.y, 0);
	tempm.triangle(ad1, ad2, ad3);
	tempm.triangle(ad1, ad4, ad2);
	rightBox = CollideBox(Point(pmax.x-side_weight_x, pmin.y, 0), pmax);

	


	//arrete gauche
	if (left)
	{
		r = ((float)rand() / (RAND_MAX));
		r1 = ((float)rand() / (RAND_MAX));
		r2 = ((float)rand() / (RAND_MAX));
		tempm.normal(r, r1, r2);
	}
	else tempm.normal(0, 1, 1);
	unsigned int ag1 = tempm.vertex(pmin);
	tempm.normal(1, 0, 1);
	unsigned int ag2 = tempm.vertex(pmin.x+side_weight_x, pmax.y, 0);
	if (left)
	{
		r = ((float)rand() / (RAND_MAX));
		r1 = ((float)rand() / (RAND_MAX));
		r2 = ((float)rand() / (RAND_MAX));
		tempm.normal(r, r1, r2);
	}
	else tempm.normal(0, 1, 0);
	unsigned int ag3 = tempm.vertex(pmin.x, pmax.y, 0);
	tempm.normal(1, 1, 1);
	unsigned int ag4 = tempm.vertex(pmin.x+side_weight_x, pmin.y, 0);
	tempm.triangle(ag1, ag2, ag3);
	tempm.triangle(ag1, ag4, ag2);
	leftBox = CollideBox(pmin, Point(pmin.x+side_weight_x, pmax.y, 0));
	

	//center
	tempm.normal(0, 1, 1);
	unsigned int a = tempm.vertex(pmin.x+side_weight_x, pmin.y+side_weight_y, 0);
	tempm.normal(1, 0, 1);
	unsigned int b = tempm.vertex(pmax.x-side_weight_x, pmax.y-side_weight_y, 0);
	tempm.normal(0, 1, 0);
	unsigned int c = tempm.vertex(pmin.x+side_weight_x, pmax.y-side_weight_y, 0);
	tempm.normal(1, 1, 1);
	unsigned int d = tempm.vertex(pmax.x-side_weight_x, pmin.y+side_weight_y, 0);
	tempm.triangle(a, b, c);
	tempm.triangle(a, d, b);

	//////////////////////////////////////////////
	topB = false;
	rightB = false;
	bottomB = false;
	leftB = false;

	if (top)
	{
		topB = true;
		tempm.color(ah1, clr);
		tempm.color(ah2, clr);
		tempm.color(ah3, clr);
		tempm.color(ah4, clr);	
	}
	if (right)
	{
		rightB = true;
		tempm.color(ad1, clr);
		tempm.color(ad2, clr);
		tempm.color(ad3, clr);
		tempm.color(ad4, clr);
	}
	if (bottom)
	{
		bottomB = true;
		tempm.color(ab1, clr);
		tempm.color(ab2, clr);
		tempm.color(ab3, clr);
		tempm.color(ab4, clr);
	}
	if (left)
	{
		leftB = true;
		tempm.color(ag1, clr);
		tempm.color(ag2, clr);
		tempm.color(ag3, clr);
		tempm.color(ag4, clr);
	}
	
}

float Brick::getDistance(const Point & p){
	const float l2 = distance2(pobj1, pobj2);  
	if (l2 == 0.0) return distance(p, pobj1);   

	const float t = std::max((float)0.0, std::min((float)1.0, dot(p - pobj1, pobj2 - pobj1) / l2));
	const Point projection = pobj1 + t * (pobj2 - pobj1);
	return distance(p, projection);
}

bool Brick::isIn(const Point & p){
	if (p.x < pmax.x && p.x >= pmin.x && p.y <= pmax.y && p.y > pmin.y)
	{
		//std::cout << "inn " << std::endl;
		return true;
	}
	return false;
}

int Brick::collideSide(CollideBox & box){

	if (topB)
	{
		if(topBox.collide(box)){
			//std::cout << box.getPmin() << std::endl;
			return 1;
		} 
	}
	if (rightB)
	{
		if(rightBox.collide(box)) return 2;
	}
	if (bottomB)
	{
		if(bottomBox.collide(box)) return 3;
	}
	if (leftB)
	{
		if(leftBox.collide(box)) return 4;
	}
	return 0;
}