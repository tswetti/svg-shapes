#include "Line.h"

Line::Line(double x1, double y1, double x2, double y2, const char* fill) : Shape(2, fill)
{
	setPoint(0, x1, y1);
	setPoint(1, x2, y2);
}
double Line::getArea() const
{
	return 0;

}
double Line::getPer() const
{
	return getLength();
}

double Line::getLength() const
{
	return getPointAtIndex(0).getDist(getPointAtIndex(1));
}

bool Line::isPointIn(double x, double y) const
{
	if ((getPointAtIndex(0).x < getPointAtIndex(1).x) &&
		(x < getPointAtIndex(0).x || x > getPointAtIndex(1).x) ||
		(getPointAtIndex(0).x > getPointAtIndex(1).x) &&
		(x > getPointAtIndex(0).x || x < getPointAtIndex(1).x))
		return false;

	if ((getPointAtIndex(0).y > getPointAtIndex(1).y) &&
		(y < getPointAtIndex(0).y || y > getPointAtIndex(1).y) ||
		(getPointAtIndex(0).y < getPointAtIndex(1).y) &&
		(y > getPointAtIndex(0).y || y < getPointAtIndex(1).y))
		return false;

	if ((x * getPointAtIndex(0).y * 1 + getPointAtIndex(0).x + getPointAtIndex(1).y * 1 + y * 1 * getPointAtIndex(1).x
		- 1 * getPointAtIndex(0).y * getPointAtIndex(1).x - y * getPointAtIndex(0).x * 1 - x * getPointAtIndex(1).y * 1) == 0)
		return true;

	return false;
}

Shape* Line::clone() const
{
	return new Line(*this);
}

void Line::print() const
{
	std::cout << "line " << getPointAtIndex(0).x << " " << getPointAtIndex(0).y <<
		getPointAtIndex(1).x << " " << getPointAtIndex(1).y << " ";
	Shape::print();
}

void Line::translate(double vertical, double horizontal)
{
	setPointAtIndex(0, getPointAtIndex(0).x + horizontal, getPointAtIndex(0).y + vertical);
	setPointAtIndex(1, getPointAtIndex(1).x + horizontal, getPointAtIndex(1).y + vertical);
}