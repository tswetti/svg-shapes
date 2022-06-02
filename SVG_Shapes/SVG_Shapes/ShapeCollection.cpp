#include "ShapeCollection.h"
#include "app.h"
#include <stdexcept>      // std::out_of_range
#include "Rectangle.h"
#include "Circle.h"
#include "Line.h"

void ShapeCollection::free()
{
	for (size_t i = 0; i < shapesCount; i++)
		delete shapes[i];
	delete[] shapes;
}

void ShapeCollection::copy(const ShapeCollection& other)
{
	shapes = new Shape * [other.shapesCount];
	shapesCount = other.shapesCount;
	capacity = other.capacity;

	for (size_t i = 0; i < shapesCount; i++)
	{
		shapes[i] = other.shapes[i]->clone();
	}
}

void ShapeCollection::resize()
{
	Shape** newCollection = new Shape * [capacity *= 2];

	for (size_t i = 0; i < shapesCount; i++)
		newCollection[i] = shapes[i];

	delete[] shapes;
	shapes = newCollection;
}

ShapeCollection::ShapeCollection()
{
	capacity = 8;
	shapesCount = 0;
	shapes = new Shape * [capacity];
}

void ShapeCollection::addFromFile(std::ifstream& ifs)
{
	bool isSvgTag = false;
	while (ifs.good())
	{
		char buff[1024];
		ifs.getline(buff, 1024);

		if (buff[0] == '<' && buff[1] == 's' && buff[2] == 'v' && buff[3] == 'g' && buff[4] == '>')
		{
			isSvgTag = true;
			continue;
		}

		if (buff[0] == '<' && buff[1] == '/' && buff[2] == 's' && buff[3] == 'v' && buff[4] == 'g' && buff[5] == '>')
			break;

		if (isSvgTag)
		{
			char shape[20];
			int i = 0;
			int shapeI = 0;

			while (buff[i] == ' ' || buff[i] == '\t')
				i++;

			while (buff[i] != ' ' && buff[i] != '\t' && shapeI < 20)
				shape[shapeI++] = buff[i++];
			shape[shapeI] = '\0';

			if (strcmp(shape, "<rect") == 0)
			{
				rectFromTag(buff);
			}
			else if (strcmp(shape, "<circle") == 0)
			{
				circleFromTag(buff);
			}
			else if (strcmp(shape, "<line") == 0)
			{
				lineFromTag(buff);
			}
		}
	}
}

/*ShapeCollection::ShapeCollection(std::ifstream& ifs)
{
	capacity = 8;
	shapesCount = 0;
	shapes = new Shape * [capacity];

	bool isSvgTag = false;
	while (ifs.good())
	{
		char buff[1024];
		ifs.getline(buff, 1024);

		if (buff[0] == '<' && buff[1] == 's' && buff[2] == 'v' && buff[3] == 'g' && buff[4] == '>')
		{
			isSvgTag = true;
			continue;
		}

		if (buff[0] == '<' && buff[1] == '/' && buff[2] == 's' && buff[3] == 'v' && buff[4] == 'g' && buff[5] == '>')
			break;

		if (isSvgTag)
		{
			char shape[20];
			int i = 0;
			int shapeI = 0;

			while (buff[i] == ' ' || buff[i] == '\t')
				i++;

			while (buff[i] != ' ' && buff[i]!='\t' && shapeI < 20)
				shape[shapeI++] = buff[i++];
			shape[shapeI] = '\0';

			if (strcmp(shape, "<rect") == 0)
			{
				std::cout << shapesCount << std::endl;
				rectFromTag(buff);
			}
			else if (strcmp(shape, "<circle") == 0)
			{
				std::cout << shapesCount << std::endl;
				circleFromTag(buff);
			}
			else if (strcmp(shape, "<line") == 0)
			{
				std::cout << shapesCount << std::endl;
				lineFromTag(buff);
			}
		}
	}
}*/

bool ShapeCollection::lineFromTag(const char* tag)
{
	double x1, y1, x2, y2;
	char* fill = new char[20];

	char x1Str[10], y1Str[10], x2Str[10], y2Str[10];
	int x1I, y1I, x2I, y2I, fI;
	x1I = y1I = x2I = y2I = fI = 0;

	int i = 0;

	while (!(tag[i] == 'x' && tag[i + 1] == '1' && tag[i + 2] == '=' && tag[i + 3] == '"'))
		i++;

	i += 4;

	while (tag[i] != '"')
		x1Str[x1I++] = tag[i++];
	x1Str[x1I] = '\0';

	while (!(tag[i] == 'y' && tag[i + 1] == '1' && tag[i + 2] == '=' && tag[i + 3] == '"'))
		i++;

	i += 4;

	while (tag[i] != '"')
		y1Str[y1I++] = tag[i++];
	y1Str[y1I] = '\0';

	while (!(tag[i] == 'x' && tag[i + 1] == '2' && tag[i + 2] == '=' && tag[i + 3] == '"'))
		i++;

	i += 4;

	while (tag[i] != '"')
		x2Str[x2I++] = tag[i++];
	x2Str[x2I] = '\0';

	while (!(tag[i] == 'y' && tag[i + 1] == '2' && tag[i + 2] == '=' && tag[i + 3] == '"'))
		i++;

	i += 4;

	while (tag[i] != '"')
		y2Str[y2I++] = tag[i++];
	y2Str[y2I] = '\0';

	while (!(tag[i] == 'f' && tag[i + 1] == 'i' && tag[i + 2] == 'l' && tag[i + 3] == 'l' && tag[i + 4] == '=' && tag[i + 5] == '"'))
		i++;
	
	i += 6;

	while (tag[i] != '"')
		fill[fI++] = tag[i++];
	fill[fI] = '\0';

	x1 = strToDouble(x1Str);
	y1 = strToDouble(y1Str);
	x2 = strToDouble(x2Str);
	y2 = strToDouble(y2Str);

	addLine(x1, y1, x2, y2, fill);
	delete[] fill;

	return true;
}

bool ShapeCollection::circleFromTag(const char* tag)
{
	double x, y, radius;
	char* fill = new char[20];

	char xStr[10], yStr[10], radiusStr[10];
	int xI, yI, rI, fI;
	xI = yI = rI = fI = 0;

	int i = 0;

	while (!(tag[i] == 'c' && tag[i + 1] == 'x' && tag[i + 2] == '=' && tag[i + 3] == '"'))
		i++;

	i += 4;

	while (tag[i] != '"')
		xStr[xI++] = tag[i++];
	xStr[xI] = '\0';

	while (!(tag[i] == 'c' && tag[i + 1] == 'y' && tag[i + 2] == '=' && tag[i + 3] == '"'))
		i++;

	i += 4;

	while (tag[i] != '"')
		yStr[yI++] = tag[i++];
	yStr[yI] = '\0';

	while (!(tag[i] == 'r' && tag[i + 1] == '=' && tag[i + 2] == '"'))
		i++;

	i += 3;

	while (tag[i] != '"')
		radiusStr[rI++] = tag[i++];
	radiusStr[rI] = '\0';

	while (!(tag[i] == 'f' && tag[i + 1] == 'i' && tag[i + 2] == 'l' && tag[i + 3] == 'l' && tag[i + 4] == '=' && tag[i + 5] == '"'))
		i++;

	i += 6;

	while (tag[i] != '"')
		fill[fI++] = tag[i++];
	fill[fI] = '\0';

	x = strToDouble(xStr);
	y = strToDouble(yStr);
	radius = strToDouble(radiusStr);

	addCircle(x, y, radius, fill);
	delete[] fill;

	return true;
}

bool ShapeCollection::rectFromTag(const char* tag)
{
	double x, y, width, height;
	char* fill = new char[20];

	char xStr[10], yStr[10], widthStr[10], heightStr[10];
	int xI, yI, wI, hI, fI;
	xI = yI = wI = hI = fI = 0;

	int i = 0;

	while (!(tag[i] == 'x' && tag[i + 1] == '=' && tag[i + 2] == '"'))
		i++;

	i += 3;

	while (tag[i] != '"')
		xStr[xI++] = tag[i++];
	xStr[xI] = '\0';

	while (!(tag[i] == 'y' && tag[i + 1] == '=' && tag[i + 2] == '"'))
		i++;

	i += 3;

	while (tag[i] != '"')
		yStr[yI++] = tag[i++];
	yStr[yI] = '\0';

	while (!(tag[i] == 'w' && tag[i + 1] == 'i' && tag[i + 2] == 'd' && tag[i + 3] == 't' && tag[i + 4] == 'h' && tag[i + 5] == '=' && tag[i + 6] == '"'))
		i++;

	i += 7;

	while (tag[i] != '"')
		widthStr[wI++] = tag[i++];
	widthStr[wI] = '\0';

	while (!(tag[i] == 'h' && tag[i + 1] == 'e' && tag[i + 2] == 'i' && tag[i + 3] == 'g' && tag[i + 4] == 'h' && tag[i + 5] == 't' && tag[i + 6] == '=' && tag[i + 7] == '"'))
		i++;

	i += 8;

	while (tag[i] != '"')
		heightStr[hI++] = tag[i++];
	heightStr[hI] = '\0';

	while (!(tag[i] == 'f' && tag[i + 1] == 'i' && tag[i + 2] == 'l' && tag[i + 3] == 'l' && tag[i + 4] == '=' && tag[i + 5] == '"'))
		i++;

	i += 6;

	while (tag[i] != '"')
		fill[fI++] = tag[i++];
	fill[fI] = '\0';

	x = strToDouble(xStr);
	y = strToDouble(yStr);
	width = strToDouble(widthStr);
	height = strToDouble(heightStr);

	addRectangle(x, y, width, height, fill);
	delete[] fill;

	return true;
}

int convertToInt(char a[1000]) {
	int i = 0;
	int num = 0;
	while (a[i] != '\0')
	{
		num = (a[i] - '0') + (num * 10);
		i++;
	}
	return num;;
}

ShapeCollection::ShapeCollection(const ShapeCollection& other)
{
	copy(other);
}

ShapeCollection& ShapeCollection::operator=(const ShapeCollection& other)
{
	if (this != &other)
	{
		free();
		copy(other);
	}
	return *this;
}

ShapeCollection::~ShapeCollection()
{
	free();
}

void ShapeCollection::addShape(Shape* shape)
{
	if (shapesCount >= capacity)
		resize();

	shapes[shapesCount++] = shape->clone();
}

void ShapeCollection::addRectangle(double x1, double y1, double width, double height, const char* fill)
{
	Rectangle* rect = new Rectangle(x1, y1, width, height, fill);
	addShape(rect);
	delete rect;
}

void ShapeCollection::addCircle(double x1, double y1, double r, const char* fill)
{
	Circle* circle = new Circle(x1, y1, r, fill);
	addShape(circle);
	delete circle;
}

void ShapeCollection::addLine(double x1, double y1, double x2, double y2, const char* fill)
{
	Line* l = new Line(x1, y1, x2, y2, fill);
	addShape(l);
	delete l;
}

bool ShapeCollection::deleteAt(int index)
{
	if (index < 0 || index >= shapesCount)
		return false;

	delete shapes[index];
	shapes[index] = nullptr;

	shapesCount--;
	for (int i = index; i < shapesCount; i++)
		shapes[i] = shapes[i + 1];
	
	return true;
}

void ShapeCollection::print() const
{
	for (int i = 0; i < shapesCount; i++)
	{
		std::cout << i + 1 << ". ";
		shapes[i]->print();
		std::cout << std::endl;
	}
}

void ShapeCollection::printAreas() const
{
	for (int i = 0; i < shapesCount; i++)
	{
		std::cout << i + 1 << ". ";
		std::cout << shapes[i]->getArea() << std::endl;
	}
}

void ShapeCollection::printPerimeters() const
{
	for (int i = 0; i < shapesCount; i++)
	{
		std::cout << i + 1 << ". ";
		std::cout << shapes[i]->getPer() << std::endl;
	}
}

void ShapeCollection::printWithinRectangle(double x, double y, double width, double height) const
{
	bool any = false;
	for (int i = 0; i < shapesCount; i++)
	{
		if (shapes[i]->withinRectangle(x, y, width, height))
		{
			any = true;
			std::cout << i + 1 << ". ";
			shapes[i]->print();
			std::cout << std::endl;
		}
	}

	if (!any)
		std::cout << "No figures are within " << x << " " << y << " " << width << " " << height << std::endl;
}

void ShapeCollection::printWithinCircle(double x, double y, double radius) const
{
	for (int i = 0; i < shapesCount; i++)
	{
		if (shapes[i]->withinCircle(x, y, radius))
		{
			std::cout << i + 1 << ". ";
			shapes[i]->print();
			std::cout << std::endl;
		}
	}
}

void ShapeCollection::printPointIn(double x, double y) const
{
	bool any = false;
	for (int i = 0; i < shapesCount; i++)
	{
		if (shapes[i]->isPointIn(x, y))
		{
			any = true;
			std::cout << i + 1 << ". ";
			shapes[i]->print();
			std::cout << std::endl;
		}
	}

	if (!any)
		std::cout << "No figures contain " << x << " " << y << std::endl;
}

void ShapeCollection::translate(double vertical, double horizontal)
{
	for (int i = 0; i < shapesCount; i++)
	{
		shapes[i]->translate(vertical, horizontal);
	}
}

bool ShapeCollection::translateAt(int index, double vertical, double horizontal)
{
	if (index < 0 || index > shapesCount)
		return false;

	shapes[index]->translate(vertical, horizontal);
	return true;
}

double ShapeCollection::getPerOfFigureByIndex(size_t ind) const
{
	if (ind >= shapesCount)
		throw std::out_of_range("Out of range in shapes collection");
	return shapes[ind]->getPer();
}

double ShapeCollection::getAreaOfFigureByIndex(size_t ind) const
{
	if (ind >= shapesCount)
		throw std::out_of_range("Out of range in shapes collection");
	return shapes[ind]->getArea();
}

int ShapeCollection::getSize() const
{
	return shapesCount;
}

double ShapeCollection::getIfPointInShapeByIndex(size_t ind, int x, int y) const
{
	if (ind >= shapesCount)
		throw std::out_of_range("Out of range in shapes collection");
	return shapes[ind]->isPointIn(x, y);
}

void ShapeCollection::save(const char* fileName) const
{
	std::ifstream ifs(fileName);
	char** linesBeforeSVG = new char* [200];
	char** linesAfterSVG = new char* [200];

	for (int i = 0; i < 200; i++)
	{
		linesBeforeSVG[i] = new char[1024];
		linesAfterSVG[i] = new char[1024];
	}

	int i1, i2;
	i1 = i2 = 0;

	bool isSVGTag = false;

	while (ifs.good())
	{
		char buff[1024];

		ifs.getline(buff, 1024);

		if (buff[0] == '<' && buff[1] == 's' && buff[2] == 'v' && buff[3] == 'g' && buff[4] == '>')
		{
			isSVGTag = true;
			break;
		}

		strcpy(linesBeforeSVG[i1++], buff);
	}

	while (ifs.good())
	{
		char buff[1024];

		ifs.getline(buff, 1024);

		if (buff[0] == '<' && buff[1] == 's' && buff[2] == 'v' && buff[3] == 'g' && buff[4] == '/' && buff[5] == '>')
		{
			isSVGTag = false;
			continue;
		}
		else
			continue;

		if (!isSVGTag)
			strcpy(linesAfterSVG[i2], buff);
	}

	ifs.close();

	std::ofstream ofs(fileName);

	for (int i = 0; i < i1; i++)
		ofs << linesBeforeSVG[i] << std::endl;

	ofs << "<svg>" << std::endl;

	for (int i = 0; i < shapesCount; i++)
		shapes[i]->writeSvgTag(ofs);

	ofs << "</svg>" << std::endl;

	for (int i = 0; i < i2; i++)
		ofs << linesAfterSVG[i] << std::endl;

	for (int i = 0; i < i1; i++)
		delete[] linesBeforeSVG[i];
	delete[] linesBeforeSVG;

	for (int i = 0; i < i2; i++)
		delete[] linesAfterSVG[i];
	delete[] linesAfterSVG;

	ofs.close();
}