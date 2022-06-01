#pragma once
#include "Shape.h"
#include "Rectangle.h"
#include "Circle.h"

class Line : public Shape
{
public:
	Line(double, double, double, double, const char*);

	double getArea() const override;
	double getPer() const override;
	double getLength() const;
	bool isPointIn(double, double) const override;

	void print() const override;

	void translate(double, double) override;

	bool withinRectangle(double, double, double, double) const override;
	bool withinCircle(double, double, double) const override;

	Shape* clone() const override;
	void writeSvgTag(std::ofstream&) const override;
};