#pragma once

#include "Shape.h"
#include "ShapeCollection.h"

bool appStart();
void wordStartEndIndexes(const char*, int&, int&, int);
void substr(char*, const char*, int, int);
int wordsCnt(const char*);
bool isValidCommand(const char*, const char*, const char*, const char*, const char*, const char*, const char*);
void fillCmdWords(const char*, int, char*, char*, char*, char*, char*, char*, char*);
