#pragma once
#include "Shape.h"
#include "Circle.h"

class Rectangle : public Shape
{
public:
	Rectangle(double, double, double, double, const char*);

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