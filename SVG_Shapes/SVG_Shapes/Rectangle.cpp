#include "Rectangle.h"

Rectangle::Rectangle(double x1, double y1, double width, double height, const char* fill) : Shape(4, fill)
{
	setPoint(0, x1, y1);
	setPoint(1, x1 + width, y1);
	setPoint(2, x1 + width, y1 + height);
	setPoint(3, x1, y1 + height);
}

double Rectangle::getArea() const
{
	Shape::point p0 = getPointAtIndex(0);
	Shape::point p1 = getPointAtIndex(1);
	Shape::point p3 = getPointAtIndex(3);

	return p0.getDist(p1) * p0.getDist(p3);

}
double Rectangle::getPer() const
{
	Shape::point p0 = getPointAtIndex(0);
	Shape::point p1 = getPointAtIndex(1);
	Shape::point p3 = getPointAtIndex(3);

	return 2 * (p0.getDist(p1) + p0.getDist(p3));
}

bool Rectangle::isPointIn(double x, double y) const
{
	Shape::point p(x, y);
	//std::cout << p.x << " " << getPointAtIndex(0).x << " ";
	bool test = p.x >= getPointAtIndex(0).x && p.x <= getPointAtIndex(1).x &&
		p.y >= getPointAtIndex(0).y && p.y <= getPointAtIndex(2).y;
	//std::cout << test;
	return test;
}
Shape* Rectangle::clone() const
{
	return new Rectangle(*this);
}

void Rectangle::print() const
{
	std::cout << "rectangle " << getPointAtIndex(0).x << " " << getPointAtIndex(0).y << " ";
	std::cout << getPointAtIndex(1).x - getPointAtIndex(0).x << " " << getPointAtIndex(3).y - getPointAtIndex(0).y << " ";
	Shape::print();
}

void Rectangle::translate(double vertical, double horizontal)
{
	setPointAtIndex(0, getPointAtIndex(0).x + horizontal, getPointAtIndex(0).y + vertical);
	setPointAtIndex(1, getPointAtIndex(1).x + horizontal, getPointAtIndex(1).y + vertical);
	setPointAtIndex(2, getPointAtIndex(2).x + horizontal, getPointAtIndex(2).y + vertical);
	setPointAtIndex(3, getPointAtIndex(3).x + horizontal, getPointAtIndex(3).y + vertical);
}

bool Rectangle::withinRectangle(double x, double y, double width, double height) const
{
	Rectangle rect(x, y, width, height, "black");

	return rect.isPointIn(getPointAtIndex(0).x, getPointAtIndex(0).y) &&
		rect.isPointIn(getPointAtIndex(1).x, getPointAtIndex(1).y) &&
		rect.isPointIn(getPointAtIndex(2).x, getPointAtIndex(2).y) &&
		rect.isPointIn(getPointAtIndex(3).x, getPointAtIndex(3).y);
}

bool Rectangle::withinCircle(double x, double y, double radius) const
{
	Circle c(x, y, radius, "black");

	return c.isPointIn(getPointAtIndex(0).x, getPointAtIndex(0).y) &&
		c.isPointIn(getPointAtIndex(1).x, getPointAtIndex(1).y) &&
		c.isPointIn(getPointAtIndex(2).x, getPointAtIndex(2).y) &&
		c.isPointIn(getPointAtIndex(3).x, getPointAtIndex(3).y);
}

void Rectangle::writeSvgTag(std::ofstream& ofs) const
{
	const char* fill = getFill();
	ofs << " <rect x=\"" << getPointAtIndex(0).x << "\" y=\"" << getPointAtIndex(0).y << "\"";
	ofs << " width=\"" << getPointAtIndex(1).x - getPointAtIndex(0).x << "\"";
	ofs << " height=\"" << getPointAtIndex(3).y - getPointAtIndex(0).y << "\"";
	ofs << " fill=\"" << fill << "\" />" << std::endl;

	delete[] fill;
}