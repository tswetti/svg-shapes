#pragma once
#include "Shape.h"

class Line : public Shape
{
public:
	Line(double, double, double, double);

	double getArea() const override;
	double getPer() const override;
	double getLength() const;
	bool isPointIn(double, double) const override;

	Shape* clone() const override;
};