#include "brick.hpp"

int Brick::getPosition(){
	return position;
}


void Brick::initMesh(){
	tempm = Mesh(GL_TRIANGLES);
	
	double r = ((double) rand() / (RAND_MAX));
	double r1 = ((double) rand() / (RAND_MAX));
	double r2 = ((double) rand() / (RAND_MAX));
	tempm.color(Color(r1, r2, r));
	int a = tempm.vertex(pmin);
	int b = tempm.vertex(pmax);
	int c = tempm.vertex(pmin.x, pmax.y, 0);
	int d = tempm.vertex(pmax.x, pmin.y, 0);
	tempm.triangle(a, b, c);
	tempm.triangle(a, d, b);
}