#pragma once

#include <iostream>
#include <cstring>
#include <fstream>

#pragma warning(disable:4996)

class Shape
{
protected:
	struct point
	{
		point() :x(0), y(0) {}
		point(double x, double y) :x(x), y(y) {}
		double x;
		double y;
		double getDist(const point& other) const
		{
			double dx = x - other.x;
			double dy = y - other.y;

			return sqrt(dx * dx + dy * dy);
		}
	};
	const point& getPointAtIndex(size_t) const;
	bool setPointAtIndex(size_t, double, double);
	void setFill(const char*);

private:
	point* points;
	size_t pointsCount;

	char* fill;

	void copy(const Shape&);
	void free();

public:
	Shape(size_t, const char*);

	Shape(const Shape&);
	Shape& operator=(const Shape&);
	virtual ~Shape();

	bool setPoint(size_t, double, double);

	const char* getFill() const;
	virtual double getArea() const = 0;
	virtual double getPer()  const = 0;
	virtual bool isPointIn(double, double) const = 0;

	virtual void print() const;

	virtual void translate(double, double) = 0;

	virtual bool withinRectangle(double, double, double, double) const = 0;
	virtual bool withinCircle(double, double, double) const = 0;
	virtual void writeSvgTag(std::ofstream&) const = 0;

	virtual Shape* clone() const = 0;
};