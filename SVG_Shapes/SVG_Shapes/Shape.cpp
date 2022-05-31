#include "Shape.h"

Shape::Shape(size_t pointsCount) : pointsCount(pointsCount)
{
	points = new point[pointsCount];
}

void Shape::copy(const Shape& other)
{
	points = new point[other.pointsCount];

	for (int i = 0; i < other.pointsCount; i++)
		points[i] = other.points[i];

	pointsCount = other.pointsCount;
}
void Shape::free()
{
	delete[] points;
}

Shape::Shape(const Shape& other)
{
	copy(other);
}
Shape& Shape::operator= (const Shape& other)
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

void Shape::setPoint(size_t pointIndex, double x, double y)
{
	if (pointIndex >= pointsCount)
		throw std::exception("Invalid point index!");

	points[pointIndex] = point(x, y);
}