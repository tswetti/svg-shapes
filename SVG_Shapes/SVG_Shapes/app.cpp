#include "app.h"
#include <iostream>
#include <cstring>

bool appStart()
{
	ShapeCollection sc;
	char currentFile[30] = {};

	std::cout << "commands: " << std::endl;
	std::cout << "open <file> | save | exit |" << std::endl;
	std::cout << "create <shape> <x> <y> ... <fill> | erase <index> |" << std::endl;
	std::cout << "print | perimeters | areas |" << std::endl;
	std::cout << "translate vertical=<value> horizontal=<value> | within <shape> <details> | point <x> <y> |" << std::endl;
	std::cout << std::endl;

	do
	{
		std::cout << ">";
		char command[100];
		std::cin.getline(command, 140);

		int commandsCnt = wordsCnt(command);
		if (commandsCnt == 0 || commandsCnt > 7)
		{
			// ne
		}

		char firstCmd[20] = {};
		char secondCmd[20] = {};
		char thirdCmd[20] = {};
		char fourthCmd[20] = {};
		char fifthCmd[20] = {};
		char sixthCmd[20] = {};
		char seventhCmd[20] = {};
		firstCmd[0] = secondCmd[0] = thirdCmd[0] = fourthCmd[0] = fifthCmd[0] = sixthCmd[0] = seventhCmd[0] = '\0';

		fillCmdWords(command, commandsCnt, firstCmd, secondCmd, thirdCmd, fourthCmd, fifthCmd, sixthCmd, seventhCmd);

		if (strcmp(firstCmd, "open") == 0)
		{
			std::ifstream ifs(secondCmd);

			if (!ifs.is_open())
			{
				std::cout << "File couldn't open." << std::endl;
				continue;
			}

			ShapeCollection scCopy(ifs);
			sc = scCopy;

			strcpy(currentFile, secondCmd);
			ifs.close();
		}
		else if (strcmp(firstCmd, "print") == 0)
		{
			sc.print();
		}
		else if (strcmp(firstCmd, "create") == 0)
		{
			if (strcmp(secondCmd, "rectangle") == 0)
				sc.addRectangle(convertToInt(thirdCmd), convertToInt(fourthCmd), convertToInt(fifthCmd), convertToInt(sixthCmd), seventhCmd);
			else if (strcmp(secondCmd, "circle") == 0)
				sc.addCircle(convertToInt(thirdCmd), convertToInt(fourthCmd), convertToInt(fifthCmd), sixthCmd);
			else if (strcmp(secondCmd, "line") == 0)
				sc.addLine(convertToInt(thirdCmd), convertToInt(fourthCmd), convertToInt(fifthCmd), convertToInt(sixthCmd), seventhCmd);
		}
		else if (strcmp(firstCmd, "within") == 0)
		{
			if (strcmp(secondCmd, "rectangle") == 0)
				sc.printWithinRectangle(convertToInt(thirdCmd), convertToInt(fourthCmd), convertToInt(fifthCmd), convertToInt(sixthCmd));
			else if (strcmp(secondCmd, "circle") == 0)
				sc.printWithinCircle(convertToInt(thirdCmd), convertToInt(fourthCmd), convertToInt(fifthCmd));
		}
		else if (strcmp(firstCmd, "point") == 0)
		{

		}
		else if (strcmp(firstCmd, "erase") == 0)
		{
			sc.deleteAt(convertToInt(secondCmd));
		}
		else if (strcmp(firstCmd, "translate") == 0)
		{

		}
		else if (strcmp(firstCmd, "save") == 0)
		{
			sc.save(currentFile);
			std::cout << "File successfully saved!" << std::endl;
		}
		else if (strcmp(firstCmd, "exit") == 0)
		{
			return false;
		}
	} while (true);

	return true;
}

void wordStartEndIndexes(const char* word, int& start, int& end, int startWord)
{
	start = -1;
	end = -1;
	if (word[startWord] >= 'a' && word[startWord] <= 'z' || word[startWord] >= 'A' && word[startWord] <= 'Z' ||
		word[startWord] >= '0' && word[startWord] <= '9')
		start = startWord;

	for (int i = startWord; i < strlen(word); i++)
	{
		if (start == -1 && (word[i] == ' ' || word[i] == '\t') && ((word[i + 1] >= 'a' &&
			word[i + 1] <= 'z') || (word[i + 1] >= 'A' && word[i + 1] <= 'Z') ||
			word[i + 1] >= '0' && word[i + 1] <= '9'))
			start = i + 1;

		if (((word[i] >= 'a' && word[i] <= 'z') || (word[i] >= 'A' && word[i] <= 'Z') ||
			(word[i] >= '0' && word[i] <= '9')) &&
			(word[i + 1] == ' ' || word[i + 1] == '\t' || word[i + 1] == '\n' || word[i + 1] == '\0'))
		{
			end = i;
			break;
		}
	}
}

void substr(char* word1, const char* word2, int start, int end)
{
	int wordLength = end - start + 1;
	int i = 0;
	for (i = 0; i < wordLength; i++, start++)
		word1[i] = word2[start];

	word1[i] = '\0';
}

int wordsCnt(const char* word)
{
	int cnt = 0;

	if (word[0] >= 'a' && word[0] <= 'z' || word[0] >= 'A' && word[0] <= 'Z' || word[0] >= '0' && word[0] <= '9')
		cnt++;

	for (int i = 0; i < strlen(word); i++)
	{
		if ((word[i] == ' ' || word[i] == '\t') && ((word[i + 1] >= 'a' &&
			word[i + 1] <= 'z') || (word[i + 1] >= 'A' && word[i + 1] <= 'Z') || 
			word[i + 1] >= '0' && word[i + 1] <= '9'))
			cnt++;
	}

	return cnt;
}

bool isValidCommand(const char* first, const char* second, const char* third, const char* fourth, const char* fifth, const char* sixth, const char* seventh)
{
	if (strcmp(first, "open") == 0 && second[0] == '\0' && third[0] != '\0' && fourth[0] != '\0' && fifth[0] != '\0' &&
		sixth[0] != '\0' && seventh[0] != '\0')
		return false;

	if (strcmp(first, "print") == 0 && second[0] != '\0' && third[0] != '\0' && fourth[0] != '\0' && fifth[0] != '\0' &&
		sixth[0] != '\0' && seventh[0] != '\0')
		return false;
	
}

void fillCmdWords(const char* cmd, int cnt, char* first, char* second, char* third, char* fourth, char* fifth, char* sixth, char* seventh)
{
	int start, end, cmdStartFrom;
	cmdStartFrom = 0;
	if (cnt >= 1)
	{
		wordStartEndIndexes(cmd, start, end, cmdStartFrom);
		substr(first, cmd, start, end);
	}
	if (cnt >= 2)
	{
		cmdStartFrom = end + 1;
		wordStartEndIndexes(cmd, start, end, cmdStartFrom);
		substr(second, cmd, start, end);
	}
	if (cnt >= 3)
	{
		cmdStartFrom = end + 1;
		wordStartEndIndexes(cmd, start, end, cmdStartFrom);
		substr(third, cmd, start, end);
	}
	if (cnt >= 4)
	{
		cmdStartFrom = end + 1;
		wordStartEndIndexes(cmd, start, end, cmdStartFrom);
		substr(fourth, cmd, start, end);
	}
	if (cnt >= 5)
	{
		cmdStartFrom = end + 1;
		wordStartEndIndexes(cmd, start, end, cmdStartFrom);
		substr(fifth, cmd, start, end);
	}
	if (cnt >= 6)
	{
		cmdStartFrom = end + 1;
		wordStartEndIndexes(cmd, start, end, cmdStartFrom);
		substr(sixth, cmd, start, end);
	}
	if (cnt >= 7)
	{
		cmdStartFrom = end + 1;
		wordStartEndIndexes(cmd, start, end, cmdStartFrom);
		substr(seventh, cmd, start, end);
	}

}