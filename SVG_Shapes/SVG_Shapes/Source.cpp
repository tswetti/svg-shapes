#include "Shape.h"
#include "Rectangle.h"
#include "Circle.h"
#include "ShapeCollection.h"
#include "app.h"
#include <iostream>

#define _CRTDBG_MAP_ALLOC
#include <crtdbg.h>

int main()
{
	/*
	* example tags:
	* 
	<rect x="205" y="105" width="10" height="10" fill="green" />
	<line x1="-212" y1="112" x2="218" y2="-118" fill="orange" />
	<circle cx="0.5" cy="0.5" r="30" fill="purple" />
	*/

	_CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF);

	if (!appStart())
		return 0;

	_CrtDumpMemoryLeaks();

	return 0;
}