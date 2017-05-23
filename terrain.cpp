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
	float r = ((float)rand() / (RAND_MAX));
	float r1 = ((float)rand() / (RAND_MAX));
	float r2 = ((float)rand() / (RAND_MAX));
	Color clr2 = Color(r, r1, r2);
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
					n.initMesh(clr, clr2, false, false, true, true);
					printf("%s\n", "innnnn");
				}
				else n.initMesh(clr, clr2, true, false, true, true);
			}
			else if (i%w == w-1)
			{
				n.initMesh(clr, clr2, true, true, false, false);
			}
			else n.initMesh(clr, clr2, true, false, true);
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
					n.initMesh(clr, clr2, false, true, true);
				}
				else if(k==0) {
					n.initMesh(clr, clr2, true, false, false, true);
				}

				else n.initMesh(clr, clr2, true, false, true);
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

Terrain::Terrain(int nb, Point pmn, Point pmx){
	size = 12*12;
	pmin = pmn;
	pmax = pmx;
	double xgap = abs(pmax.x-pmin.x)/(double)12;
	double ygap = abs(pmax.y-pmin.y)/(double)12;
	if (nb == 1)
	{
		Point p1, p2;
		//
		p1 = Point((double)pmin.x+0*xgap, (double)pmin.y+11*ygap, pmin.z);
		p2 = Point((double)pmin.x+1*xgap, (double)pmin.y+12*ygap, pmin.z);
		Brick n = Brick(0, p1, p2);
		n.initMesh(Color(1, 1, 1), Color(1, 1, 1), true, false, true, false);
		bricks.push_back(n);

		p1 = Point((double)pmin.x+1*xgap, (double)pmin.y+11*ygap, pmin.z);
		p2 = Point((double)pmin.x+2*xgap, (double)pmin.y+12*ygap, pmin.z);
		Brick n2 = Brick(1, p1, p2);
		n2.initMesh(Color(1, 1, 1), Color(1, 1, 1), true, false, true, false);
		bricks.push_back(n2);

		p1 = Point((double)pmin.x+2*xgap, (double)pmin.y+11*ygap, pmin.z);
		p2 = Point((double)pmin.x+3*xgap, (double)pmin.y+12*ygap, pmin.z);
		Brick n3 = Brick(2, p1, p2);
		n3.initMesh(Color(1, 1, 1), Color(1, 1, 1), true, false, false, false);
		bricks.push_back(n3); 

		p1 = Point((double)pmin.x+3*xgap, (double)pmin.y+11*ygap, pmin.z);
		p2 = Point((double)pmin.x+4*xgap, (double)pmin.y+12*ygap, pmin.z);
		Brick n4 = Brick(3, p1, p2);
		n4.initMesh(Color(1, 1, 1), Color(1, 1, 1), true, true, false, false);
		bricks.push_back(n4);

		//
		p1 = Point((double)pmin.x+3*xgap, (double)pmin.y+10*ygap, pmin.z);
		p2 = Point((double)pmin.x+4*xgap, (double)pmin.y+11*ygap, pmin.z);
		Brick n5 = Brick(4, p1, p2);
		n5.initMesh(Color(1, 1, 1), Color(1, 1, 1), false, true, false, false);
		bricks.push_back(n5);

		p1 = Point((double)pmin.x+2*xgap, (double)pmin.y+10*ygap, pmin.z);
		p2 = Point((double)pmin.x+3*xgap, (double)pmin.y+11*ygap, pmin.z);
		Brick n6 = Brick(4, p1, p2);
		n6.initMesh(Color(1, 1, 1), Color(1, 1, 1), false, false, false, true);
		bricks.push_back(n6);

		//
		p1 = Point((double)pmin.x+3*xgap, (double)pmin.y+9*ygap, pmin.z);
		p2 = Point((double)pmin.x+4*xgap, (double)pmin.y+10*ygap, pmin.z);
		Brick n7 = Brick(5, p1, p2);
		n7.initMesh(Color(1, 1, 1), Color(1, 1, 1), false, true, true, false);
		bricks.push_back(n7);

		p1 = Point((double)pmin.x+2*xgap, (double)pmin.y+9*ygap, pmin.z);
		p2 = Point((double)pmin.x+3*xgap, (double)pmin.y+10*ygap, pmin.z);
		Brick n8 = Brick(5, p1, p2);
		n8.initMesh(Color(1, 1, 1), Color(1, 1, 1), false, false, false, false);
		bricks.push_back(n8);


		p1 = Point((double)pmin.x+1*xgap, (double)pmin.y+9*ygap, pmin.z);
		p2 = Point((double)pmin.x+2*xgap, (double)pmin.y+10*ygap, pmin.z);
		Brick n9 = Brick(5, p1, p2);
		n9.initMesh(Color(1, 1, 1), Color(1, 1, 1), true, false, false, true);
		bricks.push_back(n9);

		//
		p1 = Point((double)pmin.x+2*xgap, (double)pmin.y+8*ygap, pmin.z);
		p2 = Point((double)pmin.x+3*xgap, (double)pmin.y+9*ygap, pmin.z);
		Brick n10 = Brick(6, p1, p2);
		n10.initMesh(Color(1, 1, 1), Color(1, 1, 1), false, true, false, false);
		bricks.push_back(n10);

		p1 = Point((double)pmin.x+1*xgap, (double)pmin.y+8*ygap, pmin.z);
		p2 = Point((double)pmin.x+2*xgap, (double)pmin.y+9*ygap, pmin.z);
		Brick n11 = Brick(6, p1, p2);
		n11.initMesh(Color(1, 1, 1), Color(1, 1, 1), false, false, false, true);
		bricks.push_back(n11);

		//
		p1 = Point((double)pmin.x+1*xgap, (double)pmin.y+7*ygap, pmin.z);
		p2 = Point((double)pmin.x+2*xgap, (double)pmin.y+8*ygap, pmin.z);
		Brick n12 = Brick(7, p1, p2);
		n12.initMesh(Color(1, 1, 1), Color(1, 1, 1), false, false, true, true);
		bricks.push_back(n12);

		p1 = Point((double)pmin.x+2*xgap, (double)pmin.y+7*ygap, pmin.z);
		p2 = Point((double)pmin.x+3*xgap, (double)pmin.y+8*ygap, pmin.z);
		Brick n13 = Brick(8, p1, p2);
		n13.initMesh(Color(1, 1, 1), Color(1, 1, 1), false, false, false, false);
		bricks.push_back(n13);
	}
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

std::vector<Brick> & Terrain::getBricks(){
	return bricks;
}