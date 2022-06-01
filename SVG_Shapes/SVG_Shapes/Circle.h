#pragma once
#include "Shape.h"
#include "Rectangle.h"

class Circle : public Shape
{
	double radius;

public:
	Circle(double, double, double, const char*);

	double getArea() const override;
	double getPer() const override;
	bool isPointIn(double, double) const override;

	void print() const override;

	void translate(double, double) override;

	bool withinRectangle(double, double, double, double) const override;
	bool withinCircle(double, double, double) const override;

	Shape* clone() const override;
	void writeSvgTag(std::ofstream&) const override;
};