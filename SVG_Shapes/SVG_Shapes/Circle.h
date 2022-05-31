#pragma once
#include "Shape.h"

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

	Shape* clone() const override;
};