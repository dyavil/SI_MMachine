#include "brick.hpp"

int Brick::getPosition(){
	return position;
}


void Brick::initMesh(const Color clr, const bool top, const bool right, const bool bottom, const bool left){
	tempm = Mesh(GL_TRIANGLES);
	
	/*double r = ((double) rand() / (RAND_MAX));
	double r1 = ((double) rand() / (RAND_MAX));
	double r2 = ((double) rand() / (RAND_MAX));*/
	tempm.color(Color(1, 1, 1));
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
	float side_weight_y = diffy/(float)5;
	float side_weight_x = diffx/(float)5;

	

	//arrete haute
	unsigned int ah1 = tempm.vertex(pmin.x, pmax.y-side_weight_y, 0);
	unsigned int ah2 = tempm.vertex(pmax);
	unsigned int ah3 = tempm.vertex(pmin.x, pmax.y, 0);
	unsigned int ah4 = tempm.vertex(pmax.x, pmax.y-side_weight_y, 0);
	tempm.triangle(ah1, ah2, ah3);
	tempm.triangle(ah1, ah4, ah2);

	//arrete basse
	unsigned int ab1 = tempm.vertex(pmin);
	unsigned int ab2 = tempm.vertex(pmax.x, pmin.y+side_weight_y, 0);
	unsigned int ab3 = tempm.vertex(pmin.x, pmin.y+side_weight_y, 0);
	unsigned int ab4 = tempm.vertex(pmax.x, pmin.y, 0);
	tempm.triangle(ab1, ab2, ab3);
	tempm.triangle(ab1, ab4, ab2);
	
	

	//arrete droite
	unsigned int ad1 = tempm.vertex(pmax.x-side_weight_x, pmin.y, 0);
	unsigned int ad2 = tempm.vertex(pmax);
	unsigned int ad3 = tempm.vertex(pmax.x-side_weight_x, pmax.y, 0);
	unsigned int ad4 = tempm.vertex(pmax.x, pmin.y, 0);
	tempm.triangle(ad1, ad2, ad3);
	tempm.triangle(ad1, ad4, ad2);
	

	


	//arrete gauche
	unsigned int ag1 = tempm.vertex(pmin);
	unsigned int ag2 = tempm.vertex(pmin.x+side_weight_x, pmax.y, 0);
	unsigned int ag3 = tempm.vertex(pmin.x, pmax.y, 0);
	unsigned int ag4 = tempm.vertex(pmin.x+side_weight_x, pmin.y, 0);
	tempm.triangle(ag1, ag2, ag3);
	tempm.triangle(ag1, ag4, ag2);
	

	//center
	unsigned int a = tempm.vertex(pmin.x+side_weight_x, pmin.y+side_weight_y, 0);
	unsigned int b = tempm.vertex(pmax.x-side_weight_x, pmax.y-side_weight_y, 0);
	unsigned int c = tempm.vertex(pmin.x+side_weight_x, pmax.y-side_weight_y, 0);
	unsigned int d = tempm.vertex(pmax.x-side_weight_x, pmin.y+side_weight_y, 0);
	tempm.triangle(a, b, c);
	tempm.triangle(a, d, b);

	//////////////////////////////////////////////


	if (top)
	{
		tempm.color(ah1, clr);
		tempm.color(ah2, clr);
		tempm.color(ah3, clr);
		tempm.color(ah4, clr);	
	}
	if (right)
	{
		tempm.color(ad1, clr);
		tempm.color(ad2, clr);
		tempm.color(ad3, clr);
		tempm.color(ad4, clr);
	}
	if (bottom)
	{
		tempm.color(ab1, clr);
		tempm.color(ab2, clr);
		tempm.color(ab3, clr);
		tempm.color(ab4, clr);
	}
	if (left)
	{
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