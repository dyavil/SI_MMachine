#include "collidebox.hpp"

bool CollideBox::collide(CollideBox & box) const{
	Point otherMin = box.getPmin();
	Point otherMax = box.getPmax();
	/*Point otherTopLeft = Point(otherMin.x, otherMax.y, otherMin.z);
	Point otherBottomRight = Point(otherMax.x, otherMin.y, otherMin.z);

	Point Topleft = Point(pmin.x, pmax.y, pmin.z);
	Point BottomRight = Point(pmax.x, pmin.y, pmin.z);*/

	//std::cout << otherMin.x << ", " << pmin.x << std::endl;
	if (pmin.x <= otherMax.x && pmax.x >= otherMin.x &&
    pmin.y <= otherMax.y && pmax.y >= otherMin.y) return true;
	return false;
}