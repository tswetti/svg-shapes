#pragma once
#include "Shape.h"
#include <fstream>

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
	ShapeCollection(std::ifstream&);
	ShapeCollection(const ShapeCollection&);
	ShapeCollection& operator=(const ShapeCollection&);
	~ShapeCollection();

	bool rectFromTag(const char*);
	bool circleFromTag(const char*);
	bool lineFromTag(const char*);

	void addRectangle(double, double, double, double, const char*);
	void addCircle(double, double, double, const char*);
	void addLine(double, double, double, double, const char*);

	bool deleteAt(size_t);

	void print() const;
	void printAreas() const;
	void printPerimeters() const;

	void printWithinRectangle(double, double, double, double) const;
	void printWithinCircle(double, double, double) const;

	void translate(double, double);

	double getPerOfFigureByIndex(size_t) const;
	double getAreaOfFigureByIndex(size_t) const;
	double getIfPointInShapeByIndex(size_t, int, int) const;

	void save(const char*) const;
};

int convertToInt(char a[1000]);