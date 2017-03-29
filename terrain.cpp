#include "terrain.hpp"

Terrain::Terrain(int h, int w, Point pmn, Point pmx){
	
	size = h*w;
	pmin = pmn;
	pmax = pmx;
	int modcoef = w-h;
	double xgap = abs(pmax.x-pmin.x)/(double)w;
	double ygap = abs(pmax.y-pmin.y)/(double)h;
	Color clr = Color(1, 0, 1);
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
			double coef = j+modcoef;
			Point p1 = Point((double)pmin.x+col*xgap, (double)pmin.y+(w-coef-1)*ygap, pmin.z);
			Point p2 = Point((double)pmin.x+(col+1)*xgap, (double)pmin.y+(w-coef)*ygap, pmin.z);
			Brick n = Brick(id, p1, p2);
			if(p2.x >= pp.x && p2.y >= pp.y) pp =p2;
			if (i%w == 0)
			{
				if(col == 0 && j > 1 ) {
					n.initMesh(clr, false, false, true, true);
					printf("%s\n", "innnnn");
				}
				else n.initMesh(clr, true, false, true, true);
			}
			else if (i%w == w-1)
			{
				n.initMesh(clr, true, true, false, false);
			}
			else n.initMesh(clr, true, false, true);
			bricks.push_back(n);
		}else{	
			id = i+w-1;
			for (double k = 0; k < w; ++k)
			{
				double coef = j+modcoef;
				
				Point p1 = Point((double)pmin.x+k*xgap, (double)pmin.y+(w-coef-1)*ygap, pmin.z);
				Point p2 = Point((double)pmin.x+(k+1)*xgap, (double)pmin.y+(w-coef)*ygap, pmin.z);
				Brick n = Brick(id, p1, p2);
				if(p2.x >= pp.x && p2.y >= pp.y) pp =p2;
				if (k == w-1)
				{
					n.initMesh(clr, false, true, true);
				}
				else if(k==0) {
					n.initMesh(clr, true, false, false, true);
				}

				else n.initMesh(clr, true, false, true);
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

Brick & Terrain::getBrickOn(const Point & p){
	for (unsigned int i = 0; i < bricks.size(); ++i)
	{
		if(bricks[i].isIn(p)) return bricks[i];
	}
	return bricks[0];
}

int Terrain::whosAhead(const Point& p1, const Point& p2){
	Brick a = getBrickOn(p1);
	Brick b = getBrickOn(p2);
	if (a.getPosition() > b.getPosition())
	{
		// p1 ahead
		return 1;
	}else if (a.getPosition() < b.getPosition())
	{
		return 2;
	}else{
		if (a.getDistance(p1) < a.getDistance(p2))
		{
			return 1;
		}else if(a.getDistance(p1) > a.getDistance(p2)){
			return 2;
		}
		return 0;
	}
}

std::vector<Brick> Terrain::getBricks(){
	return bricks;
}