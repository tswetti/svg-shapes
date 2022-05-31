#pragma once
#include "Shape.h"

class Circle : public Shape
{
	double radius;

public:
	Circle(double, double, double);

	double getArea() const override;
	double getPer() const override;
	bool isPointIn(double, double) const override;

	Shape* clone() const override;
};