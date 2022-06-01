#include "Shape.h"
#include "Rectangle.h"
#include "Circle.h"
#include "ShapeCollection.h"
#include <iostream>

int main()
{
	ShapeCollection sc;
	sc.addRectangle(5, 5, 10, 10, "green");
	sc.addCircle(5, 5, 10, "blue");
	sc.addRectangle(100, 60, 10, 10, "red");

	sc.print();
	std::cout << std::endl;

	sc.addRectangle(1000, 1000, 10, 20, "yellow");

	sc.printWithinCircle(0, 0, 80);

	std::cout << std::endl;

	sc.translate(10, 100);

	sc.print();

	return 0;
}