#include "ShapeCollection.h"
#include <stdexcept>      // std::out_of_range
#include "Rectangle.h"
#include "Circle.h"
#include "Line.h"

void ShapeCollection::free()
{
	for (size_t i = 0; i < shapesCount; i++)
		delete shapes[i];
	delete[] shapes;
}
void ShapeCollection::copy(const ShapeCollection& other)
{
	shapes = new Shape * [other.shapesCount];
	shapesCount = other.shapesCount;
	capacity = other.capacity;

	for (size_t i = 0; i < shapesCount; i++)
	{
		shapes[i] = other.shapes[i]->clone();
	}
}

void ShapeCollection::resize()
{
	Shape** newCollection = new Shape * [capacity *= 2];

	for (size_t i = 0; i < shapesCount; i++)
		newCollection[i] = shapes[i];

	delete[] shapes;
	shapes = newCollection;
}

ShapeCollection::ShapeCollection()
{
	capacity = 8;
	shapesCount = 0;
	shapes = new Shape * [capacity];
}

ShapeCollection::ShapeCollection(const ShapeCollection& other)
{
	copy(other);
}
ShapeCollection& ShapeCollection::operator=(const ShapeCollection& other)
{
	if (this != &other)
	{
		free();
		copy(other);
	}
	return *this;
}
ShapeCollection::~ShapeCollection()
{
	free();
}

void ShapeCollection::addShape(Shape* shape)
{
	if (shapesCount == capacity)
		resize();

	shapes[shapesCount++] = shape;
}

void ShapeCollection::addRectangle(double x1, double y1, double x3, double y3, const char* fill)
{
	Rectangle* rect = new Rectangle(x1, y1, x3, y3, fill);
	addShape(rect);
}
void ShapeCollection::addCircle(double x1, double y1, double r, const char* fill)
{
	Circle* circle = new Circle(x1, y1, r, fill);
	addShape(circle);
}

void ShapeCollection::addLine(double x1, double y1, double x2, double y2, const char* fill)
{
	Line* l = new Line(x1, y1, x2, y2, fill);
	addShape(l);
}

bool ShapeCollection::deleteAt(size_t index)
{
	if (index >= shapesCount)
		return false;

	delete shapes[index];
	shapes[index] = nullptr;
	
	return true;
}

void ShapeCollection::print() const
{
	for (int i = 0; i < shapesCount; i++)
	{
		if (shapes[i] == nullptr)
			continue;

		std::cout << i << " ";
		shapes[i]->print();
		std::cout << std::endl;
	}
}

void ShapeCollection::printAreas() const
{
	for (int i = 0; i < shapesCount; i++)
	{
		if (shapes[i] == nullptr)
			continue;

		std::cout << i << " ";
		shapes[i]->getArea();
		std::cout << std::endl;
	}
}

void ShapeCollection::printPerimeters() const
{
	for (int i = 0; i < shapesCount; i++)
	{
		if (shapes[i] == nullptr)
			continue;

		std::cout << i << " ";
		shapes[i]->getPer();
		std::cout << std::endl;
	}
}

double ShapeCollection::getPerOfFigureByIndex(size_t ind) const
{
	if (ind >= shapesCount)
		throw std::out_of_range("Out of range in shapes collection");
	return shapes[ind]->getPer();
}
double ShapeCollection::getAreaOfFigureByIndex(size_t ind) const
{
	if (ind >= shapesCount)
		throw std::out_of_range("Out of range in shapes collection");
	return shapes[ind]->getArea();
}
double ShapeCollection::getIfPointInShapeByIndex(size_t ind, int x, int y) const
{
	if (ind >= shapesCount)
		throw std::out_of_range("Out of range in shapes collection");
	return shapes[ind]->isPointIn(x, y);
}