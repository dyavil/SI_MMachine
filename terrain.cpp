#include "terrain.hpp"

Terrain::Terrain(int h, int w, Point pmn, Point pmx){
	
	size = h*w;
	pmin = pmn;
	pmax = pmx;
	int modcoef = w-h;
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
			double coef = j+modcoef;
			Point p1 = Point((double)pmin.x+col*xgap, (double)pmin.y+(w-coef-1)*ygap, pmin.z);
			Point p2 = Point((double)pmin.x+(col+1)*xgap, (double)pmin.y+(w-coef)*ygap, pmin.z);
			Brick n = Brick(id, p1, p2);
			if(p2.x >= pp.x && p2.y >= pp.y) pp =p2;
			if (i%w == 0)
			{
				if(col == 0 && j > 1 ) {
					n.initMesh(false, false, true, true);
					printf("%s\n", "innnnn");
				}
				else n.initMesh(true, false, true, true);
			}
			else if (i%w == w-1)
			{
				n.initMesh(true, true, false, false);
			}
			else n.initMesh(true, false, true);
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
					n.initMesh(false, true, true);
				}
				else if(k==0) {
					n.initMesh(true, false, false, true);
				}

				else n.initMesh(true, false, true);
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
	size = 16*16;
	pmin = pmn;
	pmax = pmx;
	double xgap = abs(pmax.x-pmin.x)/(double)16;
	double ygap = abs(pmax.y-pmin.y)/(double)16;
	if (nb == 1)
	{
		Point p1, p2;

		//row

		p1 = Point((double)pmin.x+9*xgap, (double)pmin.y+15*ygap, pmin.z);
		p2 = Point((double)pmin.x+10*xgap, (double)pmin.y+16*ygap, pmin.z);
		Brick n49 = Brick(19, p1, p2);
		n49.initMesh(true, false, false, true);
		bricks.push_back(n49);

		p1 = Point((double)pmin.x+10*xgap, (double)pmin.y+15*ygap, pmin.z);
		p2 = Point((double)pmin.x+11*xgap, (double)pmin.y+16*ygap, pmin.z);
		Brick n50 = Brick(20, p1, p2);
		n50.initMesh(true, false, false, false);
		bricks.push_back(n50);

		p1 = Point((double)pmin.x+11*xgap, (double)pmin.y+15*ygap, pmin.z);
		p2 = Point((double)pmin.x+12*xgap, (double)pmin.y+16*ygap, pmin.z);
		Brick n51 = Brick(21, p1, p2);
		n51.initMesh(true, false, false, false);
		bricks.push_back(n51);

		p1 = Point((double)pmin.x+12*xgap, (double)pmin.y+15*ygap, pmin.z);
		p2 = Point((double)pmin.x+13*xgap, (double)pmin.y+16*ygap, pmin.z);
		Brick n52 = Brick(22, p1, p2);
		n52.initMesh(true, false, false, false);
		bricks.push_back(n52);

		p1 = Point((double)pmin.x+13*xgap, (double)pmin.y+15*ygap, pmin.z);
		p2 = Point((double)pmin.x+14*xgap, (double)pmin.y+16*ygap, pmin.z);
		Brick n53 = Brick(23, p1, p2);
		n53.initMesh(true, true, false, false);
		bricks.push_back(n53);



		//row
		p1 = Point((double)pmin.x+8*xgap, (double)pmin.y+14*ygap, pmin.z);
		p2 = Point((double)pmin.x+9*xgap, (double)pmin.y+15*ygap, pmin.z);
		Brick n45 = Brick(19, p1, p2);
		n45.initMesh(true, false, false, true);
		bricks.push_back(n45);

		p1 = Point((double)pmin.x+9*xgap, (double)pmin.y+14*ygap, pmin.z);
		p2 = Point((double)pmin.x+10*xgap, (double)pmin.y+15*ygap, pmin.z);
		Brick n46 = Brick(20, p1, p2);
		n46.initMesh(false, false, false, false);
		bricks.push_back(n46);

		p1 = Point((double)pmin.x+10*xgap, (double)pmin.y+14*ygap, pmin.z);
		p2 = Point((double)pmin.x+11*xgap, (double)pmin.y+15*ygap, pmin.z);
		Brick n47 = Brick(21, p1, p2);
		n47.initMesh(false, false, false, false);
		bricks.push_back(n47);

		p1 = Point((double)pmin.x+11*xgap, (double)pmin.y+14*ygap, pmin.z);
		p2 = Point((double)pmin.x+12*xgap, (double)pmin.y+15*ygap, pmin.z);
		Brick n48 = Brick(22, p1, p2);
		n48.initMesh(false, false, false, false);
		bricks.push_back(n48);

		p1 = Point((double)pmin.x+12*xgap, (double)pmin.y+14*ygap, pmin.z);
		p2 = Point((double)pmin.x+13*xgap, (double)pmin.y+15*ygap, pmin.z);
		Brick n54 = Brick(23, p1, p2);
		n54.initMesh(false, false, false, false);
		bricks.push_back(n54);

		p1 = Point((double)pmin.x+13*xgap, (double)pmin.y+14*ygap, pmin.z);
		p2 = Point((double)pmin.x+14*xgap, (double)pmin.y+15*ygap, pmin.z);
		Brick n55 = Brick(24, p1, p2);
		n55.initMesh(false, false, false, false);
		bricks.push_back(n55);

		p1 = Point((double)pmin.x+14*xgap, (double)pmin.y+14*ygap, pmin.z);
		p2 = Point((double)pmin.x+15*xgap, (double)pmin.y+15*ygap, pmin.z);
		Brick n56 = Brick(25, p1, p2);
		n56.initMesh(true, true, false, false);
		bricks.push_back(n56);


		//row
		p1 = Point((double)pmin.x+8*xgap, (double)pmin.y+13*ygap, pmin.z);
		p2 = Point((double)pmin.x+9*xgap, (double)pmin.y+14*ygap, pmin.z);
		Brick n41 = Brick(19, p1, p2);
		n41.initMesh(false, false, false, true);
		bricks.push_back(n41);

		p1 = Point((double)pmin.x+9*xgap, (double)pmin.y+13*ygap, pmin.z);
		p2 = Point((double)pmin.x+10*xgap, (double)pmin.y+14*ygap, pmin.z);
		Brick n42 = Brick(20, p1, p2);
		n42.initMesh(false, false, false, false);
		bricks.push_back(n42);

		p1 = Point((double)pmin.x+10*xgap, (double)pmin.y+13*ygap, pmin.z);
		p2 = Point((double)pmin.x+11*xgap, (double)pmin.y+14*ygap, pmin.z);
		Brick n43 = Brick(21, p1, p2);
		n43.initMesh(false, false, false, false);
		bricks.push_back(n43);

		p1 = Point((double)pmin.x+11*xgap, (double)pmin.y+13*ygap, pmin.z);
		p2 = Point((double)pmin.x+12*xgap, (double)pmin.y+14*ygap, pmin.z);
		Brick n44 = Brick(22, p1, p2);
		n44.initMesh(false, false, true, false);
		bricks.push_back(n44);

		p1 = Point((double)pmin.x+12*xgap, (double)pmin.y+13*ygap, pmin.z);
		p2 = Point((double)pmin.x+13*xgap, (double)pmin.y+14*ygap, pmin.z);
		Brick n57 = Brick(23, p1, p2);
		n57.initMesh(false, false, false, false);
		bricks.push_back(n57);

		p1 = Point((double)pmin.x+13*xgap, (double)pmin.y+13*ygap, pmin.z);
		p2 = Point((double)pmin.x+14*xgap, (double)pmin.y+14*ygap, pmin.z);
		Brick n58 = Brick(24, p1, p2);
		n58.initMesh(false, false, false, false);
		bricks.push_back(n58);

		p1 = Point((double)pmin.x+14*xgap, (double)pmin.y+13*ygap, pmin.z);
		p2 = Point((double)pmin.x+15*xgap, (double)pmin.y+14*ygap, pmin.z);
		Brick n59 = Brick(25, p1, p2);
		n59.initMesh(false, true, false, false);
		bricks.push_back(n59);


		//row
		p1 = Point((double)pmin.x+8*xgap, (double)pmin.y+12*ygap, pmin.z);
		p2 = Point((double)pmin.x+9*xgap, (double)pmin.y+13*ygap, pmin.z);
		Brick n37 = Brick(19, p1, p2);
		n37.initMesh(false, false, false, true);
		bricks.push_back(n37);

		p1 = Point((double)pmin.x+9*xgap, (double)pmin.y+12*ygap, pmin.z);
		p2 = Point((double)pmin.x+10*xgap, (double)pmin.y+13*ygap, pmin.z);
		Brick n38 = Brick(19, p1, p2);
		n38.initMesh(false, false, false, false);
		bricks.push_back(n38);

		p1 = Point((double)pmin.x+10*xgap, (double)pmin.y+12*ygap, pmin.z);
		p2 = Point((double)pmin.x+11*xgap, (double)pmin.y+13*ygap, pmin.z);
		Brick n39 = Brick(20, p1, p2);
		n39.initMesh(false, true, true, false);
		bricks.push_back(n39);

		p1 = Point((double)pmin.x+12*xgap, (double)pmin.y+12*ygap, pmin.z);
		p2 = Point((double)pmin.x+13*xgap, (double)pmin.y+13*ygap, pmin.z);
		Brick n40 = Brick(24, p1, p2);
		n40.initMesh(false, false, true, true);
		bricks.push_back(n40);

		p1 = Point((double)pmin.x+13*xgap, (double)pmin.y+12*ygap, pmin.z);
		p2 = Point((double)pmin.x+14*xgap, (double)pmin.y+13*ygap, pmin.z);
		Brick n60 = Brick(26, p1, p2);
		n60.initMesh(false, false, false, false);
		bricks.push_back(n60);

		p1 = Point((double)pmin.x+14*xgap, (double)pmin.y+12*ygap, pmin.z);
		p2 = Point((double)pmin.x+15*xgap, (double)pmin.y+13*ygap, pmin.z);
		Brick n61 = Brick(26, p1, p2);
		n61.initMesh(false, false, false, false);
		bricks.push_back(n61);

		p1 = Point((double)pmin.x+15*xgap, (double)pmin.y+12*ygap, pmin.z);
		p2 = Point((double)pmin.x+16*xgap, (double)pmin.y+13*ygap, pmin.z);
		Brick n62 = Brick(25, p1, p2);
		n62.initMesh(true, true, false, false);
		bricks.push_back(n62);



		//row 
		p1 = Point((double)pmin.x+0*xgap, (double)pmin.y+11*ygap, pmin.z);
		p2 = Point((double)pmin.x+1*xgap, (double)pmin.y+12*ygap, pmin.z);
		Brick n = Brick(0, p1, p2);
		n.initMesh(true, false, true, false);
		bricks.push_back(n);

		p1 = Point((double)pmin.x+1*xgap, (double)pmin.y+11*ygap, pmin.z);
		p2 = Point((double)pmin.x+2*xgap, (double)pmin.y+12*ygap, pmin.z);
		Brick n2 = Brick(1, p1, p2);
		n2.initMesh(true, false, true, false);
		bricks.push_back(n2);

		p1 = Point((double)pmin.x+2*xgap, (double)pmin.y+11*ygap, pmin.z);
		p2 = Point((double)pmin.x+3*xgap, (double)pmin.y+12*ygap, pmin.z);
		Brick n3 = Brick(2, p1, p2);
		n3.initMesh(true, false, false, false);
		bricks.push_back(n3); 

		p1 = Point((double)pmin.x+3*xgap, (double)pmin.y+11*ygap, pmin.z);
		p2 = Point((double)pmin.x+4*xgap, (double)pmin.y+12*ygap, pmin.z);
		Brick n4 = Brick(1, p1, p2);
		n4.initMesh(true, true, false, false);
		bricks.push_back(n4);




		p1 = Point((double)pmin.x+8*xgap, (double)pmin.y+11*ygap, pmin.z);
		p2 = Point((double)pmin.x+9*xgap, (double)pmin.y+12*ygap, pmin.z);
		Brick n35 = Brick(18, p1, p2);
		n35.initMesh(false, false, false, true);
		bricks.push_back(n35);

		p1 = Point((double)pmin.x+9*xgap, (double)pmin.y+11*ygap, pmin.z);
		p2 = Point((double)pmin.x+10*xgap, (double)pmin.y+12*ygap, pmin.z);
		Brick n36 = Brick(18, p1, p2);
		n36.initMesh(false, true, false, false);
		bricks.push_back(n36);



		p1 = Point((double)pmin.x+13*xgap, (double)pmin.y+11*ygap, pmin.z);
		p2 = Point((double)pmin.x+14*xgap, (double)pmin.y+12*ygap, pmin.z);
		Brick n63 = Brick(26, p1, p2);
		n63.initMesh(false, false, true, true);
		bricks.push_back(n63);

		p1 = Point((double)pmin.x+14*xgap, (double)pmin.y+11*ygap, pmin.z);
		p2 = Point((double)pmin.x+15*xgap, (double)pmin.y+12*ygap, pmin.z);
		Brick n64 = Brick(27, p1, p2);
		n64.initMesh(false, false, false, false);
		bricks.push_back(n64);

		p1 = Point((double)pmin.x+15*xgap, (double)pmin.y+11*ygap, pmin.z);
		p2 = Point((double)pmin.x+16*xgap, (double)pmin.y+12*ygap, pmin.z);
		Brick n65 = Brick(27, p1, p2);
		n65.initMesh(false, false, false, false);
		bricks.push_back(n65);

		p1 = Point((double)pmin.x+16*xgap, (double)pmin.y+11*ygap, pmin.z);
		p2 = Point((double)pmin.x+17*xgap, (double)pmin.y+12*ygap, pmin.z);
		Brick n66 = Brick(26, p1, p2);
		n66.initMesh(true, true, false, false);
		bricks.push_back(n66);

		//row
		p1 = Point((double)pmin.x+3*xgap, (double)pmin.y+10*ygap, pmin.z);
		p2 = Point((double)pmin.x+4*xgap, (double)pmin.y+11*ygap, pmin.z);
		Brick n5 = Brick(3, p1, p2);
		n5.initMesh(false, true, false, false);
		bricks.push_back(n5);

		p1 = Point((double)pmin.x+2*xgap, (double)pmin.y+10*ygap, pmin.z);
		p2 = Point((double)pmin.x+3*xgap, (double)pmin.y+11*ygap, pmin.z);
		Brick n6 = Brick(2, p1, p2);
		n6.initMesh(false, false, false, true);
		bricks.push_back(n6);




		p1 = Point((double)pmin.x+8*xgap, (double)pmin.y+10*ygap, pmin.z);
		p2 = Point((double)pmin.x+9*xgap, (double)pmin.y+11*ygap, pmin.z);
		Brick n33 = Brick(17, p1, p2);
		n33.initMesh(false, false, false, true);
		bricks.push_back(n33);

		p1 = Point((double)pmin.x+9*xgap, (double)pmin.y+10*ygap, pmin.z);
		p2 = Point((double)pmin.x+10*xgap, (double)pmin.y+11*ygap, pmin.z);
		Brick n34 = Brick(17, p1, p2);
		n34.initMesh(false, true, false, false);
		bricks.push_back(n34);



		p1 = Point((double)pmin.x+14*xgap, (double)pmin.y+10*ygap, pmin.z);
		p2 = Point((double)pmin.x+15*xgap, (double)pmin.y+11*ygap, pmin.z);
		Brick n67 = Brick(28, p1, p2);
		n67.initMesh(false, false, false, true);
		bricks.push_back(n67);

		p1 = Point((double)pmin.x+15*xgap, (double)pmin.y+10*ygap, pmin.z);
		p2 = Point((double)pmin.x+16*xgap, (double)pmin.y+11*ygap, pmin.z);
		Brick n68 = Brick(28, p1, p2);
		n68.initMesh(false, false, false, false);
		bricks.push_back(n68);

		p1 = Point((double)pmin.x+16*xgap, (double)pmin.y+10*ygap, pmin.z);
		p2 = Point((double)pmin.x+17*xgap, (double)pmin.y+11*ygap, pmin.z);
		Brick n69 = Brick(28, p1, p2);
		n69.initMesh(false, true, false, false);
		bricks.push_back(n69);

		//row
		p1 = Point((double)pmin.x+3*xgap, (double)pmin.y+9*ygap, pmin.z);
		p2 = Point((double)pmin.x+4*xgap, (double)pmin.y+10*ygap, pmin.z);
		Brick n7 = Brick(3, p1, p2);
		n7.initMesh(false, true, true, false);
		bricks.push_back(n7);

		p1 = Point((double)pmin.x+2*xgap, (double)pmin.y+9*ygap, pmin.z);
		p2 = Point((double)pmin.x+3*xgap, (double)pmin.y+10*ygap, pmin.z);
		Brick n8 = Brick(4, p1, p2);
		n8.initMesh(false, false, false, false);
		bricks.push_back(n8);


		p1 = Point((double)pmin.x+1*xgap, (double)pmin.y+9*ygap, pmin.z);
		p2 = Point((double)pmin.x+2*xgap, (double)pmin.y+10*ygap, pmin.z);
		Brick n9 = Brick(3, p1, p2);
		n9.initMesh(true, false, false, true);
		bricks.push_back(n9);




		p1 = Point((double)pmin.x+8*xgap, (double)pmin.y+9*ygap, pmin.z);
		p2 = Point((double)pmin.x+9*xgap, (double)pmin.y+10*ygap, pmin.z);
		Brick n31 = Brick(16, p1, p2);
		n31.initMesh(false, false, false, true);
		bricks.push_back(n31);

		p1 = Point((double)pmin.x+9*xgap, (double)pmin.y+9*ygap, pmin.z);
		p2 = Point((double)pmin.x+10*xgap, (double)pmin.y+10*ygap, pmin.z);
		Brick n32 = Brick(16, p1, p2);
		n32.initMesh(false, true, false, false);
		bricks.push_back(n32);




		p1 = Point((double)pmin.x+14*xgap, (double)pmin.y+9*ygap, pmin.z);
		p2 = Point((double)pmin.x+15*xgap, (double)pmin.y+10*ygap, pmin.z);
		Brick n70 = Brick(29, p1, p2);
		n70.initMesh(false, false, false, true);
		bricks.push_back(n70);

		p1 = Point((double)pmin.x+15*xgap, (double)pmin.y+9*ygap, pmin.z);
		p2 = Point((double)pmin.x+16*xgap, (double)pmin.y+10*ygap, pmin.z);
		Brick n71 = Brick(29, p1, p2);
		n71.initMesh(false, false, false, false);
		bricks.push_back(n71);

		p1 = Point((double)pmin.x+16*xgap, (double)pmin.y+9*ygap, pmin.z);
		p2 = Point((double)pmin.x+17*xgap, (double)pmin.y+10*ygap, pmin.z);
		Brick n72 = Brick(29, p1, p2);
		n72.initMesh(false, true, false, false);
		bricks.push_back(n72);

		//row
		p1 = Point((double)pmin.x+2*xgap, (double)pmin.y+8*ygap, pmin.z);
		p2 = Point((double)pmin.x+3*xgap, (double)pmin.y+9*ygap, pmin.z);
		Brick n10 = Brick(6, p1, p2);
		n10.initMesh(false, true, false, false);
		bricks.push_back(n10);

		p1 = Point((double)pmin.x+1*xgap, (double)pmin.y+8*ygap, pmin.z);
		p2 = Point((double)pmin.x+2*xgap, (double)pmin.y+9*ygap, pmin.z);
		Brick n11 = Brick(5, p1, p2);
		n11.initMesh(false, false, false, true);
		bricks.push_back(n11);





		p1 = Point((double)pmin.x+8*xgap, (double)pmin.y+8*ygap, pmin.z);
		p2 = Point((double)pmin.x+9*xgap, (double)pmin.y+9*ygap, pmin.z);
		Brick n29 = Brick(15, p1, p2);
		n29.initMesh(false, false, false, true);
		bricks.push_back(n29);

		p1 = Point((double)pmin.x+9*xgap, (double)pmin.y+8*ygap, pmin.z);
		p2 = Point((double)pmin.x+10*xgap, (double)pmin.y+9*ygap, pmin.z);
		Brick n30 = Brick(15, p1, p2);
		n30.initMesh(false, true, false, false);
		bricks.push_back(n30);




		p1 = Point((double)pmin.x+14*xgap, (double)pmin.y+8*ygap, pmin.z);
		p2 = Point((double)pmin.x+15*xgap, (double)pmin.y+9*ygap, pmin.z);
		Brick n73 = Brick(30, p1, p2);
		n73.initMesh(false, false, false, true);
		bricks.push_back(n73);

		p1 = Point((double)pmin.x+15*xgap, (double)pmin.y+8*ygap, pmin.z);
		p2 = Point((double)pmin.x+16*xgap, (double)pmin.y+9*ygap, pmin.z);
		Brick n74 = Brick(30, p1, p2);
		n74.initMesh(false, false, false, false);
		bricks.push_back(n74);

		p1 = Point((double)pmin.x+16*xgap, (double)pmin.y+8*ygap, pmin.z);
		p2 = Point((double)pmin.x+17*xgap, (double)pmin.y+9*ygap, pmin.z);
		Brick n75 = Brick(30, p1, p2);
		n75.initMesh(false, true, false, false);
		bricks.push_back(n75);

		//row
		p1 = Point((double)pmin.x+1*xgap, (double)pmin.y+7*ygap, pmin.z);
		p2 = Point((double)pmin.x+2*xgap, (double)pmin.y+8*ygap, pmin.z);
		Brick n12 = Brick(6, p1, p2);
		n12.initMesh(false, false, true, true);
		bricks.push_back(n12);

		p1 = Point((double)pmin.x+2*xgap, (double)pmin.y+7*ygap, pmin.z);
		p2 = Point((double)pmin.x+3*xgap, (double)pmin.y+8*ygap, pmin.z);
		Brick n13 = Brick(7, p1, p2);
		n13.initMesh(false, false, false, false);
		bricks.push_back(n13);

		p1 = Point((double)pmin.x+3*xgap, (double)pmin.y+7*ygap, pmin.z);
		p2 = Point((double)pmin.x+4*xgap, (double)pmin.y+8*ygap, pmin.z);
		Brick n14 = Brick(8, p1, p2);
		n14.initMesh(true, false, false, false);
		bricks.push_back(n14);

		p1 = Point((double)pmin.x+4*xgap, (double)pmin.y+7*ygap, pmin.z);
		p2 = Point((double)pmin.x+5*xgap, (double)pmin.y+8*ygap, pmin.z);
		Brick n18 = Brick(9, p1, p2);
		n18.initMesh(true, false, false, false);
		bricks.push_back(n18);

		p1 = Point((double)pmin.x+5*xgap, (double)pmin.y+7*ygap, pmin.z);
		p2 = Point((double)pmin.x+6*xgap, (double)pmin.y+8*ygap, pmin.z);
		Brick n20 = Brick(10, p1, p2);
		n20.initMesh(true, false, false, false);
		bricks.push_back(n20);

		p1 = Point((double)pmin.x+6*xgap, (double)pmin.y+7*ygap, pmin.z);
		p2 = Point((double)pmin.x+7*xgap, (double)pmin.y+8*ygap, pmin.z);
		Brick n23 = Brick(11, p1, p2);
		n23.initMesh(true, false, false, false);
		bricks.push_back(n23);

		p1 = Point((double)pmin.x+7*xgap, (double)pmin.y+7*ygap, pmin.z);
		p2 = Point((double)pmin.x+8*xgap, (double)pmin.y+8*ygap, pmin.z);
		Brick n24 = Brick(12, p1, p2);
		n24.initMesh(true, false, false, false);
		bricks.push_back(n24);

		p1 = Point((double)pmin.x+8*xgap, (double)pmin.y+7*ygap, pmin.z);
		p2 = Point((double)pmin.x+9*xgap, (double)pmin.y+8*ygap, pmin.z);
		Brick n27 = Brick(13, p1, p2);
		n27.initMesh(false, false, false, false);
		bricks.push_back(n27);

		p1 = Point((double)pmin.x+9*xgap, (double)pmin.y+7*ygap, pmin.z);
		p2 = Point((double)pmin.x+10*xgap, (double)pmin.y+8*ygap, pmin.z);
		Brick n28 = Brick(14, p1, p2);
		n28.initMesh(false, true, false, false);
		bricks.push_back(n28);




		p1 = Point((double)pmin.x+13*xgap, (double)pmin.y+7*ygap, pmin.z);
		p2 = Point((double)pmin.x+14*xgap, (double)pmin.y+8*ygap, pmin.z);
		Brick n76 = Brick(30, p1, p2);
		n76.initMesh(true, false, false, true);
		bricks.push_back(n76);

		p1 = Point((double)pmin.x+14*xgap, (double)pmin.y+7*ygap, pmin.z);
		p2 = Point((double)pmin.x+15*xgap, (double)pmin.y+8*ygap, pmin.z);
		Brick n77 = Brick(30, p1, p2);
		n77.initMesh(false, false, false, false);
		bricks.push_back(n77);

		p1 = Point((double)pmin.x+15*xgap, (double)pmin.y+7*ygap, pmin.z);
		p2 = Point((double)pmin.x+16*xgap, (double)pmin.y+8*ygap, pmin.z);
		Brick n78 = Brick(30, p1, p2);
		n78.initMesh(false, false, false, false);
		bricks.push_back(n78);

		p1 = Point((double)pmin.x+16*xgap, (double)pmin.y+7*ygap, pmin.z);
		p2 = Point((double)pmin.x+17*xgap, (double)pmin.y+8*ygap, pmin.z);
		Brick n79 = Brick(30, p1, p2);
		n79.initMesh(false, true, true, false);
		bricks.push_back(n79);

		//row
		p1 = Point((double)pmin.x+2*xgap, (double)pmin.y+6*ygap, pmin.z);
		p2 = Point((double)pmin.x+3*xgap, (double)pmin.y+7*ygap, pmin.z);
		Brick n15 = Brick(6, p1, p2);
		n15.initMesh(false, false, true, true);
		bricks.push_back(n15);

		p1 = Point((double)pmin.x+3*xgap, (double)pmin.y+6*ygap, pmin.z);
		p2 = Point((double)pmin.x+4*xgap, (double)pmin.y+7*ygap, pmin.z);
		Brick n16 = Brick(7, p1, p2);
		n16.initMesh(false, false, true, false);
		bricks.push_back(n16);

		p1 = Point((double)pmin.x+4*xgap, (double)pmin.y+6*ygap, pmin.z);
		p2 = Point((double)pmin.x+5*xgap, (double)pmin.y+7*ygap, pmin.z);
		Brick n17 = Brick(8, p1, p2);
		n17.initMesh(false, false, true, false);
		bricks.push_back(n17);

		p1 = Point((double)pmin.x+5*xgap, (double)pmin.y+6*ygap, pmin.z);
		p2 = Point((double)pmin.x+6*xgap, (double)pmin.y+7*ygap, pmin.z);
		Brick n19 = Brick(9, p1, p2);
		n19.initMesh(false, false, true, false);
		bricks.push_back(n19);

		p1 = Point((double)pmin.x+6*xgap, (double)pmin.y+6*ygap, pmin.z);
		p2 = Point((double)pmin.x+7*xgap, (double)pmin.y+7*ygap, pmin.z);
		Brick n21 = Brick(10, p1, p2);
		n21.initMesh(false, false, true, false);
		bricks.push_back(n21);

		p1 = Point((double)pmin.x+7*xgap, (double)pmin.y+6*ygap, pmin.z);
		p2 = Point((double)pmin.x+8*xgap, (double)pmin.y+7*ygap, pmin.z);
		Brick n22 = Brick(11, p1, p2);
		n22.initMesh(false, false, true, false);
		bricks.push_back(n22);

		p1 = Point((double)pmin.x+8*xgap, (double)pmin.y+6*ygap, pmin.z);
		p2 = Point((double)pmin.x+9*xgap, (double)pmin.y+7*ygap, pmin.z);
		Brick n25 = Brick(12, p1, p2);
		n25.initMesh(false, false, true, false);
		bricks.push_back(n25);

		p1 = Point((double)pmin.x+9*xgap, (double)pmin.y+6*ygap, pmin.z);
		p2 = Point((double)pmin.x+10*xgap, (double)pmin.y+7*ygap, pmin.z);
		Brick n26 = Brick(13, p1, p2, false, true, true, false);
		//n26.initMesh(false, true, true, false);
		bricks.push_back(n26);


	}
}

Terrain::Terrain(std::string fileName){
	
    std::ifstream file;
    file.open("proj/projet/data/field/" + fileName);
    int h, w;
    //Lecture de la largeur et de la hauteur
    file >> h >> w;
    float rangex = h*6/2;
    float rangey = w*6/2;
    pmin = Point(-rangex, -rangey, 0);
    pmax = Point(rangex, rangey, 0);
	size = h*w;
	/*pmin = pmn;
	pmax = pmx;*/
	int modcoef = w-h;
	double xgap = abs(pmax.x-pmin.x)/(double)w;
	double ygap = abs(pmax.y-pmin.y)/(double)h;
	std::string objective;
    int min, max, id;
    std::string up, left, bottom, right, start, end;
    bool bup, bleft, bbottom, bright, bstart, bend;
    
    while(file >> min >> max >> up >> right >> bottom >> left >> id >> objective >> start >> end){
        bup = (up == "true");
        bright = (right == "true");
        bbottom = (bottom == "true");
        bleft = (left == "true");
        bstart = (start == "true");
        bend = (end == "true");
        //std::cout << min << " " << max << " " << up << " " << right << " " << bottom << " " << left << " " << id << std::endl; 
        Point p1, p2;
        p1 = Point((double)pmin.x+min*xgap, (double)pmin.y+max*ygap, pmin.z);
        p2 = Point((double)pmin.x+(min + 1)*xgap, (double)pmin.y+(max + 1)*ygap, pmin.z);
        Brick n = Brick(id, p1, p2, bup, bright, bbottom, bleft, objective, bend);
        if (bstart)
        {
        	spawnPoint = Point(p1.x + 2, p1.y + 3, 0);
        }
        //n.initMesh(bup, bright, bbottom, bleft);
        bricks.push_back(n);
    }
    Brick out = Brick(-1, Point(0, 0, -50), Point(0, 0, -50), false, false, false, false, "empty", false);
    bricks.push_back(out);
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
	return bricks[bricks.size()-1];
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