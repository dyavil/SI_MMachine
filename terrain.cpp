#include "terrain.hpp"

Terrain::Terrain(int h, int w, Point pmn, Point pmx){
	
	size = h*w;
	pmin = pmn;
	pmax = pmx;
	double xgap = abs(pmax.x-pmin.x)/(double)w;
	double ygap = abs(pmax.y-pmin.y)/(double)h;

	int j = 0;
	Point pp = Point(0, 0, 0);
	for (int i = 0; i < size; ++i)
	{
		int id;
		double col;
		if(i!= 0 && i%w == 0) {
			j++;
			col = -1;
		}
		if(j != 0) col ++;
		else col = i;

		
		if(j%2 == 0){
			id = i;
			double coef = j;
			Point p1 = Point((double)pmin.x+col*xgap, (double)pmin.y+(w-coef)*ygap, pmin.z);
			Point p2 = Point((double)pmin.x+(col+1)*xgap, (double)pmin.y+(w-coef+1)*ygap, pmin.z);
			Brick n = Brick(id, p1, p2);
			if(p2.x >= pp.x && p2.y >= pp.y) pp =p2;
			n.initMesh();
			bricks.push_back(n);
		}else{
			id = i+w-1;
			for (double k = 0; k < w; ++k)
			{
				double coef = j;
				Point p1 = Point((double)pmin.x+k*xgap, (double)pmin.y+(w-coef)*ygap, pmin.z);
				Point p2 = Point((double)pmin.x+(k+1)*xgap, (double)pmin.y+(w-coef+1)*ygap, pmin.z);
				Brick n = Brick(id, p1, p2);
				if(p2.x >= pp.x && p2.y >= pp.y) pp =p2;
				n.initMesh();
				bricks.push_back(n);
				id--;
			}
			i+=w-1;
		}
		
		
	}
	//std::cout << pmax << pp << std::endl;
	mesh = Mesh(GL_TRIANGLES);
	
	int a = mesh.vertex(pmin);
	int b = mesh.vertex(pmax);
	int c = mesh.vertex(pmin.x, pmax.y, pmin.z);
	int d = mesh.vertex(pmax.x, pmin.y, pmin.z);
	mesh.triangle(a, b, c);
	mesh.triangle(a, d, b);
}


void Terrain::project(const Point& from, Point& to, Vector& n) const {
  to.z = 0 ;
  n = Vector(0.f, 0.f, 1.f) ;
}

std::vector<Brick> Terrain::getBricks(){
	return bricks;
}