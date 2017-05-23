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
	// if (top)
	// {
	// 	tempm.normal(0.2, 0.8, 0.2);
	// }
	// else tempm.normal(0.2, 0.8, 0.4);
	// if (top)
	// {
		/*Mesh topMesh = Mesh(GL_TRIANGLES);
		// = read_mesh("data/border.obj");
		unsigned int ah1 = topMesh.vertex(pmin.x, pmax.y-side_weight_y, 0);
		// if (top)
		// {
		// 	tempm.normal(1, 1, 1);
		// }else tempm.normal(0, 0, 0);
		unsigned int ah2 = topMesh.vertex(pmax);
		// if(top)
		// {
		// 	tempm.normal(1, 1, 1);
		// }else tempm.normal(0, 0, 0);
		unsigned int ah3 = topMesh.vertex(pmin.x, pmax.y, 0);	
		
		// if (top)
		// {
		// 	tempm.normal(-0.2, 0.8, 0.2);
		// }
		// else tempm.normal(-0.2, 0.8, 0.4);
		unsigned int ah4 = topMesh.vertex(pmax.x, pmax.y-side_weight_y, 0);
		topMesh.triangle(ah1, ah2, ah3);
		topMesh.triangle(ah1, ah4, ah2);
		borders.push_back(topMesh);*/
		/*Mesh topMesh = read_mesh("proj/projet/data/case1.obj");
		Point tpmax, tpmin;
		topMesh.bounds(tpmin, tpmax);
		Point cent = center(tpmin, tpmax);
		Point cent2 = center(Point(pmin.x, pmax.y-side_weight_y, 0), pmax);
		transforms.push_back((Translation(cent2-cent))*(RotationY(90))*(RotationZ(90))); 
		//transforms.push_back(Identity());
		//std::cout << ((Translation(cent2-cent))*(RotationY(90))*(RotationZ(90))) << std::endl;
		borders.push_back(topMesh);*/
		topBox = CollideBox(Point(pmin.x, pmax.y-side_weight_y, 0), pmax);
	// }

	//arrete basse
	// if (bottom)
	// {
		 
		
		/*Mesh bottomMesh = Mesh(GL_TRIANGLES);

		// {
		// 	tempm.normal(1, 1, 1);
		// }
		// else tempm.normal(0, 0, 0);
		unsigned int ab1 = bottomMesh.vertex(pmin);
		// if (bottom)
		// {
		// 	tempm.normal(-0.2, -0.8, 0.2);
		// }
		// else tempm.normal(-0.2, -0.8, 0.4);
		unsigned int ab2 = bottomMesh.vertex(pmax.x, pmin.y+side_weight_y, 0);
		// if (bottom)
		// {
		// 	tempm.normal(0.2, -0.8, 0.2);
		// }
		// else tempm.normal(0.2, -0.8, 0.4);
		unsigned int ab3 = bottomMesh.vertex(pmin.x, pmin.y+side_weight_y, 0);
		// if (bottom)
		// {
		// 	tempm.normal(1, 1, 1);
		// }
		// else tempm.normal(0, 0, 0);
		unsigned int ab4 = bottomMesh.vertex(pmax.x, pmin.y, 0);
		bottomMesh.triangle(ab1, ab2, ab3);
		bottomMesh.triangle(ab1, ab4, ab2);*/
		
		bottomBox = CollideBox(pmin, Point(pmax.x, pmin.y+side_weight_y, 0));
	// }	
	

	//arrete droite
	unsigned int ad1;
	unsigned int ad2;
	unsigned int ad3;
	unsigned int ad4;
	unsigned int diffRight = 0;


	if (right)
	{

		diffRight = 1;
		/*Mesh rightMesh = Mesh(GL_TRIANGLES);
		// tempm.normal(0.2, 0.8, 0.2);
		ad1 = rightMesh.vertex(pmax.x - side_weight_x, pmin.y, 0);
		// tempm.normal(1, 1, 1);
		ad2 = rightMesh.vertex(pmax);
		// tempm.normal(0.2, -0.8, 0.2);
		ad3 = rightMesh.vertex(pmax.x - side_weight_x, pmax.y, 0);
		// tempm.normal(1, 1, 1);
		ad4 = rightMesh.vertex(pmax.x, pmin.y, 0);
		rightMesh.triangle(ad1, ad2, ad3);
		rightMesh.triangle(ad1, ad4, ad2);
		borders.push_back(rightMesh);*/
		//Mesh rightMesh = read_mesh("proj/projet/data/border.obj");
		Point tpmax, tpmin;
		//rightMesh.bounds(tpmin, tpmax);
		//Point cent = center(tpmin, tpmax);
		//transforms.push_back((Translation(Point(pmax.x, pmax.y-side_weight_y, 0)-cent))); 
		//transforms.push_back(Identity());
		rightBox = CollideBox(Point(pmax.x - side_weight_x, pmin.y, 0), pmax);
	}
	

	


	//arrete gauche
	unsigned int ag1;
	unsigned int ag2;
	unsigned int ag3;
	unsigned int ag4;
	unsigned int diffLeft = 0;

	if (left)
	{
		diffLeft = 1;
		/*Mesh leftMesh = Mesh(GL_TRIANGLES);
		// tempm.normal(1, 1, 1);
		ag1 = leftMesh.vertex(pmin);
		// tempm.normal(-0.2, -0.8, 0.2);
		ag2 = leftMesh.vertex(pmin.x + side_weight_x, pmax.y, 0);
		// tempm.normal(1, 1, 1);
		ag3 = leftMesh.vertex(pmin.x, pmax.y, 0);
		// tempm.normal(-0.2, 0.8, 0.2);
		ag4 = leftMesh.vertex(pmin.x + side_weight_x, pmin.y, 0);
		leftMesh.triangle(ag1, ag2, ag3);
		leftMesh.triangle(ag1, ag4, ag2);
		borders.push_back(leftMesh);*/
		//Mesh leftMesh = read_mesh("proj/projet/data/border.obj");
		Point tpmax, tpmin;
		//leftMesh.bounds(tpmin, tpmax);
		//Point cent = center(tpmin, tpmax);
		//transforms.push_back(Translation(Point(pmax.x, pmax.y-side_weight_y, 0)-cent)); 
		//transforms.push_back(Identity());
		leftBox = CollideBox(pmin, Point(pmin.x + side_weight_x, pmax.y, 0));
	}

	
	

	//center
	// tempm.normal(0.2, 0.8, 0.4);
	/*unsigned int a = tempm.vertex(pmin.x+ diffLeft*side_weight_x, pmin.y+side_weight_y, 0);
	// tempm.normal(-0.2, -0.8, 0.4);
	unsigned int b = tempm.vertex(pmax.x-diffRight*side_weight_x, pmax.y-side_weight_y, 0);
	// tempm.normal(0.2, -0.8, 0.4);
	unsigned int c = tempm.vertex(pmin.x+ diffLeft*side_weight_x, pmax.y-side_weight_y, 0);
	// tempm.normal(-0.2, 0.8, 0.4);
	unsigned int d = tempm.vertex(pmax.x- diffRight*side_weight_x, pmin.y+side_weight_y, 0);*/
	tempm.texcoord(0, 0);
	unsigned int a = tempm.vertex(pmin.x, pmin.y, 0);
	tempm.texcoord(1, 1);
	unsigned int b = tempm.vertex(pmax.x, pmax.y, 0);
	tempm.texcoord(1, 0);
	unsigned int c = tempm.vertex(pmin.x, pmax.y, 0);
	tempm.texcoord(0, 1);
	unsigned int d = tempm.vertex(pmax.x, pmin.y, 0);
	tempm.triangle(a, b, c);
	tempm.triangle(a, d, b);
	//std::cout << pmin.x << pmin.y << pmax.z << std::endl;

	//top + bottom 
	if(top && bottom && !right && !left){
		Mesh topbottomMesh = read_mesh("proj/projet/data/case11.obj");
		Point tpmax, tpmin;
		topbottomMesh.bounds(tpmin, tpmax);
		Point cent = center(tpmin, tpmax);
		Point cent2 = center(pmin, pmax);
		float te1 = pmax.x-pmin.x;
		//std::cout << te1 << std::endl;
		transforms.push_back((Translation(pmin-Point(tpmin.x-te1, tpmin.y, tpmax.z)))*(RotationY(90))*(RotationZ(90)));
		borders.push_back(topbottomMesh);
	}
	//right + left
	if(!top && !bottom && right && left){
		Mesh rightleftMesh = read_mesh("proj/projet/data/case11.obj");
		Point tpmax, tpmin;
		rightleftMesh.bounds(tpmin, tpmax);
		Point cent = center(tpmin, tpmax);
		Point cent2 = center(pmin, pmax);
		float te1 = pmax.x-pmin.x;
		float te2 = pmax.y-pmin.y;
		std::cout << te1 << std::endl;
		transforms.push_back((Translation(pmin-Point(tpmin.x-te1, tpmin.y-te2, tpmax.z)))*(RotationY(90))*(RotationZ(90))*(RotationY(90)));
		borders.push_back(rightleftMesh);
	}
	//top right
	if(top && !bottom && right && !left){
		Mesh toprightMesh = read_mesh("proj/projet/data/case2.obj");
		Point tpmax, tpmin;
		toprightMesh.bounds(tpmin, tpmax);
		Point cent = center(tpmin, tpmax);
		Point cent2 = center(pmin, pmax);
		float te1 = pmax.x-pmin.x;
		float te2 = pmax.y-pmin.y;
		std::cout << te1 << std::endl;
		transforms.push_back((Translation(pmin-Point(tpmin.x, tpmin.y, tpmax.z)))*(RotationY(90))*(RotationZ(90))*(RotationY(270)));
		borders.push_back(toprightMesh);
	}

	//top left
	if(top && !bottom && !right && left){
		Mesh topleftMesh = read_mesh("proj/projet/data/case2.obj");
		Point tpmax, tpmin;
		topleftMesh.bounds(tpmin, tpmax);
		Point cent = center(tpmin, tpmax);
		Point cent2 = center(pmin, pmax);
		float te1 = pmax.x-pmin.x;
		float te2 = pmax.y-pmin.y;
		std::cout << "yol" << std::endl;
		transforms.push_back((Translation(pmin-Point(tpmin.x-te1, tpmin.y, tpmax.z)))*(RotationY(90))*(RotationZ(90)));
		borders.push_back(topleftMesh);
	}

	//bottom right
	if(!top && bottom && right && !left){
		Mesh bottomrightMesh = read_mesh("proj/projet/data/case2.obj");
		Point tpmax, tpmin;
		bottomrightMesh.bounds(tpmin, tpmax);
		Point cent = center(tpmin, tpmax);
		Point cent2 = center(pmin, pmax);
		float te1 = pmax.x-pmin.x;
		float te2 = pmax.y-pmin.y;
		std::cout << bottomrightMesh.texcoord_buffer_size() << std::endl;
		transforms.push_back((Translation(pmin-Point(tpmin.x, tpmin.y-te2, tpmax.z)))*(RotationY(90))*(RotationZ(90))*(RotationY(-180)));
		borders.push_back(bottomrightMesh);
	}

	//bottom left
	if(!top && bottom && !right && left){
		Mesh bottomleftMesh = read_mesh("proj/projet/data/case2.obj");
		Point tpmax, tpmin;
		bottomleftMesh.bounds(tpmin, tpmax);
		Point cent = center(tpmin, tpmax);
		Point cent2 = center(pmin, pmax);
		float te1 = pmax.x-pmin.x;
		float te2 = pmax.y-pmin.y;
		std::cout << te1 << std::endl;
		transforms.push_back((Translation(pmin-Point(tpmin.x-te1, tpmin.y-te2, tpmax.z)))*(RotationY(90))*(RotationZ(90))*(RotationY(90)));
		borders.push_back(bottomleftMesh);
	}

	//top 
	if(top && !bottom && !right && !left){
		Mesh topMesh = read_mesh("proj/projet/data/case0.obj");
		Point tpmax, tpmin;
		topMesh.bounds(tpmin, tpmax);
		Point cent = center(tpmin, tpmax);
		Point cent2 = center(pmin, pmax);
		float te1 = pmax.x-pmin.x;
		float te2 = pmax.y-pmin.y;
		std::cout << te1 << std::endl;
		transforms.push_back((Translation(pmin-Point(tpmin.x, tpmin.y-te2, tpmax.z)))*(RotationY(90))*(RotationZ(90))*RotationY(180));
		borders.push_back(topMesh);
	}

	//right
	if(!top && !bottom && right && !left){
		Mesh topMesh = read_mesh("proj/projet/data/case0.obj");
		Point tpmax, tpmin;
		topMesh.bounds(tpmin, tpmax);
		Point cent = center(tpmin, tpmax);
		Point cent2 = center(pmin, pmax);
		float te1 = pmax.x-pmin.x;
		float te2 = pmax.y-pmin.y;
		std::cout << te1 << std::endl;
		transforms.push_back((Translation(pmin-Point(tpmin.x-te1, tpmin.y-te2, tpmax.z)))*(RotationY(90))*(RotationZ(90))*RotationY(-270));
		borders.push_back(topMesh);
	}
	//left
	if(!top && !bottom && !right && left){
		Mesh topMesh = read_mesh("proj/projet/data/case0.obj");
		Point tpmax, tpmin;
		topMesh.bounds(tpmin, tpmax);
		Point cent = center(tpmin, tpmax);
		Point cent2 = center(pmin, pmax);
		float te1 = pmax.x-pmin.x;
		float te2 = pmax.y-pmin.y;
		std::cout << te1 << std::endl;
		transforms.push_back((Translation(pmin-Point(tpmin.x, tpmin.y, tpmax.z)))*(RotationY(90))*(RotationZ(90))*(RotationY(-90)));
		borders.push_back(topMesh);
	}

	
	//////////////////////////////////////////////
	topB = false;
	rightB = false;
	bottomB = false;
	leftB = false;

	if (top)
	{
		topB = true;
		// tempm.color(ah1, clr);
		// tempm.color(ah2, clr);
		// tempm.color(ah3, clr);
		// tempm.color(ah4, clr);	
	}
	if (right)
	{
		rightB = true;
		// tempm.color(ad1, clr);
		// tempm.color(ad2, clr);
		// tempm.color(ad3, clr);
		// tempm.color(ad4, clr);
	}
	if (bottom)
	{
		bottomB = true;
		// tempm.color(ab1, clr);
		// tempm.color(ab2, clr);
		// tempm.color(ab3, clr);
		// tempm.color(ab4, clr);
	}
	if (left)
	{
		leftB = true;
		// tempm.color(ag1, clr);
		// tempm.color(ag2, clr);
		// tempm.color(ag3, clr);
		// tempm.color(ag4, clr);
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