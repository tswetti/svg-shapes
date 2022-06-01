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
	_CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF);
	if (!appStart())
		return 0;

	_CrtDumpMemoryLeaks();

	return 0;
}