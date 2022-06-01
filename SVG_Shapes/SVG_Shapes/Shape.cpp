#include "Shape.h"

Shape::Shape(size_t pointsCount, const char* fill) : pointsCount(pointsCount)
{
	points = new point[pointsCount];
	setFill(fill);
}

void Shape::copy(const Shape& other)
{
	points = new point[other.pointsCount];

	for (int i = 0; i < other.pointsCount; i++)
		points[i] = other.points[i];

	pointsCount = other.pointsCount;

	setFill(other.fill);
}
void Shape::free()
{
	delete[] points;
	delete[] fill;
}

Shape::Shape(const Shape& other)
{
	copy(other);
}
Shape& Shape::operator=(const Shape& other)
{
	if (this != &other)
	{
		free();
		copy(other);
	}
	return *this;
}
Shape::~Shape()
{
	free();
}

const Shape::point& Shape::getPointAtIndex(size_t index) const
{
	if (index >= pointsCount)
		throw std::exception("Invalid point index!");

	return  points[index];
}

void Shape::setPointAtIndex(size_t index, double x, double y)
{
	if (index >= pointsCount)
		throw std::exception("Invalid point index!");

	points[index].x = x;
	points[index].y = y;
}

void Shape::setFill(const char* fill)
{
	this->fill = new char[strlen(fill) + 1];
	strcpy(this->fill, fill);
}

void Shape::setPoint(size_t pointIndex, double x, double y)
{
	if (pointIndex >= pointsCount)
		throw std::exception("Invalid point index!");

	points[pointIndex] = point(x, y);
}

void Shape::print() const
{
	std::cout << fill;
}

const char* Shape::getFill() const
{
	return fill;
}