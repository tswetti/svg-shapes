#pragma once
#include "Shape.h"

class ShapeCollection
{
	Shape** shapes;
	size_t shapesCount;
	size_t capacity;

	void free();
	void copy(const ShapeCollection&);
	void resize();

	void addShape(Shape* shape);

public:
	ShapeCollection();
	ShapeCollection(const ShapeCollection&);
	ShapeCollection& operator=(const ShapeCollection&);
	~ShapeCollection();

	void addRectangle(double, double, double, double, const char*);
	void addCircle(double, double, double, const char*);
	void addLine(double, double, double, double, const char*);

	bool deleteAt(size_t);

	void print() const;
	void printAreas() const;
	void printPerimeters() const;

	double getPerOfFigureByIndex(size_t) const;
	double getAreaOfFigureByIndex(size_t) const;
	double getIfPointInShapeByIndex(size_t, int, int) const;
};