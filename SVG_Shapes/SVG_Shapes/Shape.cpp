#include "Shape.h"

Shape::Shape(size_t pointsCount, const char* fill) : pointsCount(pointsCount)
{
	points = new point[pointsCount];
	this->fill = new char[strlen(fill) + 1];
	strcpy(this->fill, fill);
}

void Shape::copy(const Shape& other)
{
	points = new point[other.pointsCount];

	for (int i = 0; i < other.pointsCount; i++)
		points[i] = other.points[i];

	pointsCount = other.pointsCount;

	fill = new char[strlen(other.fill) + 1];
	strcpy(fill, other.fill);
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

bool Shape::setPointAtIndex(size_t index, double x, double y)
{
	if (index >= pointsCount)
		return false;

	points[index].x = x;
	points[index].y = y;
	return true;
}

void Shape::setFill(const char* fill)
{
	delete[] this->fill;
	this->fill = new char[strlen(fill) + 1];
	strcpy(this->fill, fill);
}

bool Shape::setPoint(size_t pointIndex, double x, double y)
{
	if (pointIndex >= pointsCount)
		return false;

	points[pointIndex] = point(x, y);
	return true;
}

void Shape::print() const
{
	std::cout << fill;
}

const char* Shape::getFill() const
{
	return fill;
}