#pragma once
#include "Shape.h"

class Rectangle : public Shape
{
public:
	Rectangle(double, double, double, double, const char*);

	double getArea() const override;
	double getPer() const override;
	bool isPointIn(double, double) const override;

	void print() const override;

	void translate(double, double) override;

	Shape* clone() const override;
};