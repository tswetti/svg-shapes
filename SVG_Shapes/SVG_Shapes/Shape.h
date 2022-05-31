#pragma once
#include <iostream>

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
			int dx = x - other.x;
			int dy = y - other.y;

			return sqrt(dx * dx + dy * dy);
		}
	};
	const point& getPointAtIndex(size_t) const;

private:
	point* points;
	size_t pointsCount;

	void copy(const Shape&);
	void free();

public:
	Shape(size_t);

	Shape(const Shape&);
	Shape& operator=(const Shape&);
	virtual ~Shape();

	void setPoint(size_t, double, double);

	virtual double getArea() const = 0;
	virtual double getPer()  const = 0;
	virtual bool isPointIn(double, double) const = 0;

	virtual Shape* clone() const = 0;
};