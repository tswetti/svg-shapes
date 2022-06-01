#include "Circle.h"

const double PI = 3.1415;
Circle::Circle(double x, double y, double radius, const char* fill) : Shape(1, fill), radius(radius)
{
	setPoint(0, x, y);
}

double Circle::getArea() const
{
	return PI * radius * radius;
}
double Circle::getPer() const
{
	return 2 * PI * radius;
}
bool Circle::isPointIn(double x, double y) const
{
	Shape::point p(x, y);
	return p.getDist(getPointAtIndex(0)) <= radius;
}

Shape* Circle::clone() const
{
	return new Circle(*this);
}

void Circle::print() const
{
	std::cout << "circle " << getPointAtIndex(0).x << " " << getPointAtIndex(0).y << " " << radius << " ";
	Shape::print();
}

void Circle::translate(double vertical, double horizontal)
{
	setPointAtIndex(0, getPointAtIndex(0).x + horizontal, getPointAtIndex(0).y + vertical);
}

bool Circle::withinRectangle(double x, double y, double width, double height) const
{
	Rectangle rect(x, y, width, height, "black");

	return rect.isPointIn(getPointAtIndex(0).x, getPointAtIndex(0).y) &&
		rect.isPointIn(getPointAtIndex(0).x + radius, getPointAtIndex(0).y + radius) &&
		rect.isPointIn(getPointAtIndex(0).x - radius, getPointAtIndex(0).y - radius);
}

bool Circle::withinCircle(double x, double y, double radius) const
{
	Circle c(x, y, radius, "black");

	return c.isPointIn(getPointAtIndex(0).x, getPointAtIndex(0).y + this->radius) &&
		c.isPointIn(getPointAtIndex(0).x, getPointAtIndex(0).y - this->radius) &&
		c.isPointIn(getPointAtIndex(0).x + this->radius, getPointAtIndex(0).y) &&
		c.isPointIn(getPointAtIndex(0).x - this->radius, getPointAtIndex(0).y);
}