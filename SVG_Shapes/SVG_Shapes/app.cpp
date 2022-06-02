#include "app.h"
#include <iostream>
#include <cstring>

bool appStart()
{
	ShapeCollection sc;
	char currentFile[30] = {};
	currentFile[0] = '\0';

	std::cout << "commands: " << std::endl;
	std::cout << "open <file> | save | exit |" << std::endl;
	std::cout << "create <shape> <x> <y> ... <fill> | erase <index> |" << std::endl;
	std::cout << "print | perimeters | areas |" << std::endl;
	std::cout << "translate <vertical value> <horizontal value> | within <shape> <details> | point <x> <y> |" << std::endl;
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

		if (!isValidCommand(firstCmd, secondCmd, thirdCmd, fourthCmd, fifthCmd, sixthCmd, seventhCmd))
		{
			std::cout << "Invalid command!" << std::endl;
			continue;
		}

		if (strcmp(firstCmd, "open") == 0)
		{
			std::ifstream ifs(secondCmd);

			if (!ifs.is_open())
			{
				std::cout << "File couldn't open." << std::endl;
				continue;
			}

			if (currentFile[0] != '\0')
			{
				for (int i = sc.getSize() - 1; i >= 0; i--)
					sc.deleteAt(i);
			}

			strcpy(currentFile, secondCmd);

			std::cout << "Successfully opened " << currentFile << std::endl;

			sc.addFromFile(ifs);
			ifs.close();
			continue;
		}
		
		if (currentFile[0] == '\0')
		{
			std::cout << "No file is open. Use open <filename>" << std::endl;
			continue;
		}

		if (strcmp(firstCmd, "print") == 0)
		{
			sc.print();
			continue;
		}
		else if (strcmp(firstCmd, "create") == 0)
		{
			if (strcmp(secondCmd, "rectangle") == 0)
				sc.addRectangle(strToDouble(thirdCmd), strToDouble(fourthCmd), strToDouble(fifthCmd), strToDouble(sixthCmd), seventhCmd);
			else if (strcmp(secondCmd, "circle") == 0)
				sc.addCircle(strToDouble(thirdCmd), strToDouble(fourthCmd), strToDouble(fifthCmd), sixthCmd);
			else if (strcmp(secondCmd, "line") == 0)
				sc.addLine(strToDouble(thirdCmd), strToDouble(fourthCmd), strToDouble(fifthCmd), strToDouble(sixthCmd), seventhCmd);
			std::cout << "Successfully created shape (" << sc.getSize() << ")" << std::endl;

			continue;
		}
		else if (strcmp(firstCmd, "within") == 0)
		{
			if (strcmp(secondCmd, "rectangle") == 0)
				sc.printWithinRectangle(strToDouble(thirdCmd), strToDouble(fourthCmd), strToDouble(fifthCmd), strToDouble(sixthCmd));
			else if (strcmp(secondCmd, "circle") == 0)
				sc.printWithinCircle(strToDouble(thirdCmd), strToDouble(fourthCmd), strToDouble(fifthCmd));

			continue;
		}
		else if (strcmp(firstCmd, "point") == 0)
		{
			sc.printPointIn(strToDouble(secondCmd), strToDouble(thirdCmd));
			continue;
		}
		else if (strcmp(firstCmd, "erase") == 0)
		{
			if (!sc.deleteAt(convertToInt(secondCmd) - 1))
			{
				std::cout << "No such shape." << std::endl;
				continue;
			}
			std::cout << "Successfully erased shape (" << convertToInt(secondCmd) << ")" << std::endl;
			continue;
		}
		else if (strcmp(firstCmd, "translate") == 0)
		{
			if (commandsCnt == 3)
			{
				sc.translate(strToDouble(secondCmd), strToDouble(thirdCmd));
				std::cout << "Translated all shapes." << std::endl;
				continue;
			}
			else
			{
				int pos = convertToInt(secondCmd) - 1;
				if (!sc.translateAt(pos, strToDouble(thirdCmd), strToDouble(fourthCmd)))
				{
					std::cout << "No such shape." << std::endl;
						continue;
				}
				std::cout << "Shape (" << pos + 1 << ") successfully translated." << std::endl;
				continue;

			}
		}
		else if (strcmp(firstCmd, "perimeters") == 0)
			sc.printPerimeters();
		else if (strcmp(firstCmd, "areas") == 0)
			sc.printAreas();
		else if (strcmp(firstCmd, "save") == 0)
		{
			sc.save(currentFile);
			std::cout << "Successfully saved the changes to " << currentFile << std::endl;
			continue;
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
	if (word[startWord] == '-' || word[startWord] >= 'a' && word[startWord] <= 'z' || word[startWord] >= 'A' && word[startWord] <= 'Z' ||
		word[startWord] >= '0' && word[startWord] <= '9')
		start = startWord;

	for (int i = startWord; i < strlen(word); i++)
	{
		if (start == -1 && (word[i] == ' ' || word[i] == '\t') && (word[i + 1] == '-' ||(word[i + 1] >= 'a' &&
			word[i + 1] <= 'z') || (word[i + 1] >= 'A' && word[i + 1] <= 'Z') ||
			word[i + 1] >= '0' && word[i + 1] <= '9'))
			start = i + 1;

		if ((word[i] == '-' || (word[i] >= 'a' && word[i] <= 'z') || (word[i] >= 'A' && word[i] <= 'Z') ||
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

	if (word[0]=='-' || word[0] >= 'a' && word[0] <= 'z' || word[0] >= 'A' && word[0] <= 'Z' || word[0] >= '0' && word[0] <= '9')
		cnt++;

	for (int i = 0; i < strlen(word); i++)
	{
		if ((word[i] == ' ' || word[i] == '\t') && (word[i + 1] == '-' || (word[i + 1] >= 'a' &&
			word[i + 1] <= 'z') || (word[i + 1] >= 'A' && word[i + 1] <= 'Z') || 
			word[i + 1] >= '0' && word[i + 1] <= '9'))
			cnt++;
	}

	return cnt;
}

bool isValidCommand(const char* first, const char* second, const char* third, const char* fourth, const char* fifth, const char* sixth, const char* seventh)
{
	/*if (strcmp(first, "open") != 0 && strcmp(first, "print") != 0 && strcmp(first, "create") != 0 && strcmp(first, "within") != 0 &&
		strcmp(first, "point") != 0 && strcmp(first, "erase") != 0 && strcmp(first, "translate") != 0 && strcmp(first, "perimeters") != 0 &&
		strcmp(first, "areas") != 0 && strcmp(first, "save") != 0 && strcmp(first, "exit") != 0)
		return false;*/

	if (strcmp(first, "open") == 0)
		return second[0] != '\0' && third[0] == '\0';

	if (strcmp(first, "print") == 0)
		return second[0] == '\0';

	if (strcmp(first, "create") == 0)
	{
		if (strcmp(second, "rectangle") == 0)
			return isNumber(third) && isNumber(fourth) && fifth[0] != '-' && isNumber(fifth) &&
			sixth[0] != '-' && isNumber(sixth) && seventh[0] != '\0';

		if (strcmp(second, "circle") == 0)
			return isNumber(third) && isNumber(fourth) && fifth[0] != '-' && 
			isNumber(fifth) && sixth[0] != '\0' && seventh[0] == '\0';

		if (strcmp(second, "line") == 0)
			return isNumber(third) && isNumber(fourth) && isNumber(fifth) && isNumber(sixth) && seventh[0] != '\0';
	}

	if (strcmp(first, "within") == 0)
	{
		if (strcmp(second, "rectangle") == 0)
			return isNumber(third) && isNumber(fourth) && fifth[0] != '-' && isNumber(fifth) && 
			sixth[0] != '-' && isNumber(sixth) && seventh[0] == '\0';

		if (strcmp(second, "circle") == 0)
			return isNumber(third) && isNumber(fourth) && fifth[0] != '-' && isNumber(fifth) && sixth[0] == '\0';
	}

	if (strcmp(first, "point") == 0)
		return isNumber(second) && isNumber(third) && fourth[0] == '\0';

	if (strcmp(first, "erase") == 0)
		return second[0] != '-' && isInteger(second) && third[0] == '\0';

	if (strcmp(first, "translate") == 0)
		return isNumber(second) && isNumber(third) && (isNumber(fourth) || fourth[0] == '\0') && fifth[0] == '\0';

	if (strcmp(first, "perimeters") == 0)
		return second[0] == '\0';

	if (strcmp(first, "areas") == 0)
		return second[0] == '\0';

	if (strcmp(first, "save") == 0)
		return second[0] == '\0';

	if (strcmp(first, "exit") == 0)
		return second[0] == '\0';

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

bool isNumber(const char* str)
{
	if (strlen(str) == 0)
		return false;

	bool hasPoint = false;

	for (int i = 0; i < strlen(str); i++)
	{
		if (str[i] < '0' || str[i] > '9')
		{
			if (str[i] != '.' && str[i] != ',')
				if (str[i] == '-' && i == 0)
					continue;
				return false;
			if (hasPoint)
				return false;
			hasPoint = true;
		}
	}

	return true;
}

bool isInteger(const char* str)
{
	for (int i = 0; i < strlen(str); i++)
	{
		if (str[i] < '0' || str[i] > '9')
			return false;
	}

	return true;
}

double strToDouble(const char* str)
{
	int i = 0;

	int length = strlen(str);

	double num, denom, divide;
	num = denom = 0;
	divide = 1;
	bool isNegative = false;

	if (str[i] == '-')
	{
		isNegative = true;
		i++;
	}

	while (str[i] != '.' && str[i] != ',' && i < length)
	{
		num *= 10;
		num += str[i] - '0';
		i++;
	}

	i++;

	while (i < length)
	{
		denom *= 10;
		denom += str[i] - '0';
		divide *= 10;
		i++;
	}

	num *= divide;
	num += denom;
	num /= divide;

	if (isNegative)
		num = -num;

	return num;
}