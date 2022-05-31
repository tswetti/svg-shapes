#pragma once
#include "Shape.h"

class Rectangle : public Shape
{
public:
	Rectangle(double, double, double, double);

	double getArea() const override;
	double getPer() const override;
	bool isPointIn(double, double) const override;

	Shape* clone() const override;
};