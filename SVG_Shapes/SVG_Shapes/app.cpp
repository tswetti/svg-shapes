#include "app.h"
#include <iostream>
#include <cstring>

bool appStart()
{
	const int MAX_WORD_LENGTH = 30;
	const int MAX_CMD_WORDS = 7;

	ShapeCollection sc;

	char currentFile[MAX_WORD_LENGTH] = {};
	currentFile[0] = '\0';

	char firstCmd[MAX_WORD_LENGTH] = {}, secondCmd[MAX_WORD_LENGTH] = {}, thirdCmd[MAX_WORD_LENGTH] = {},
		fourthCmd[MAX_WORD_LENGTH] = {}, fifthCmd[MAX_WORD_LENGTH] = {}, sixthCmd[MAX_WORD_LENGTH] = {}, seventhCmd[MAX_WORD_LENGTH] = {};

	std::cout << "commands: " << std::endl;
	std::cout << "open <file> | save | exit |" << std::endl;
	std::cout << "create <figure> <x> <y> ... <fill> | erase <index> |" << std::endl;
	std::cout << "print | perimeters | areas | perimeter <figure number> | area <figure number> |" << std::endl;
	std::cout << "translate <figure number - optional> <vertical value> <horizontal value> | within <figure> <details> | point <x> <y> |" << std::endl;
	std::cout << std::endl;

	do
	{
		std::cout << ">";
		char command[MAX_WORD_LENGTH * MAX_CMD_WORDS];
		std::cin.getline(command, MAX_WORD_LENGTH * MAX_CMD_WORDS);

		if (!hasOnlyValidCharacters(command))
		{
			std::cout << "Invalid characters!" << std::endl;
			continue;
		}

		int commandsCnt = wordsCnt(command);
		if (commandsCnt == 0 || commandsCnt > MAX_CMD_WORDS)
		{
			continue;
		}

		firstCmd[0] = secondCmd[0] = thirdCmd[0] = fourthCmd[0] = fifthCmd[0] = sixthCmd[0] = seventhCmd[0] = '\0';

		fillCmdWords(command, commandsCnt, firstCmd, secondCmd, thirdCmd, fourthCmd, fifthCmd, sixthCmd, seventhCmd);

		if (!isValidCommand(firstCmd, secondCmd, thirdCmd, fourthCmd, fifthCmd, sixthCmd, seventhCmd))
		{
			std::cout << "Invalid command!" << std::endl << std::endl;
			continue;
		}

		if (strcmp(firstCmd, "exit") == 0)
		{
			return false;
		}

		else if (strcmp(firstCmd, "open") == 0)
		{
			std::ifstream ifs(secondCmd);

			if (!ifs.is_open())
			{
				std::cout << "File couldn't open." << std::endl << std::endl;
				continue;
			}

			if (currentFile[0] != '\0')
			{
				for (int i = sc.getSize() - 1; i >= 0; i--)
					sc.deleteAt(i);
			}

			strcpy(currentFile, secondCmd);

			std::cout << "Successfully opened " << currentFile << std::endl << std::endl;

			sc.addFromFile(ifs);
			ifs.close();
			continue;
		}
		
		if (currentFile[0] == '\0')
		{
			std::cout << "No file is open. Use open <filename>" << std::endl << std::endl;
			continue;
		}

		if (strcmp(firstCmd, "print") == 0)
		{
			sc.print();
			std::cout << std::endl;
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
			std::cout << "Successfully created figure (" << sc.getSize() << ")" << std::endl << std::endl;

			continue;
		}
		else if (strcmp(firstCmd, "within") == 0)
		{
			if (strcmp(secondCmd, "rectangle") == 0)
				sc.printWithinRectangle(strToDouble(thirdCmd), strToDouble(fourthCmd), strToDouble(fifthCmd), strToDouble(sixthCmd));
			else if (strcmp(secondCmd, "circle") == 0)
				sc.printWithinCircle(strToDouble(thirdCmd), strToDouble(fourthCmd), strToDouble(fifthCmd));

			std::cout << std::endl;
			continue;
		}
		else if (strcmp(firstCmd, "point") == 0)
		{
			sc.printPointIn(strToDouble(secondCmd), strToDouble(thirdCmd));
			std::cout << std::endl;
			continue;
		}
		else if (strcmp(firstCmd, "erase") == 0)
		{
			if (!sc.deleteAt(convertToInt(secondCmd) - 1))
			{
				std::cout << "There is no figure " << convertToInt(secondCmd) << std::endl << std::endl;
				continue;
			}
			std::cout << "Successfully erased figure (" << convertToInt(secondCmd) << ")" << std::endl << std::endl;
			continue;
		}
		else if (strcmp(firstCmd, "translate") == 0)
		{
			if (commandsCnt == 3)
			{
				sc.translate(strToDouble(secondCmd), strToDouble(thirdCmd));
				std::cout << "Translated all figures." << std::endl << std::endl;
				continue;
			}
			else
			{
				int pos = convertToInt(secondCmd) - 1;
				if (!sc.translateAt(pos, strToDouble(thirdCmd), strToDouble(fourthCmd)))
				{
					std::cout << "There is no figure " << pos + 1 << std::endl << std::endl;
					continue;
				}
				std::cout << "Figure (" << pos + 1 << ") successfully translated." << std::endl << std::endl;
				continue;

			}
		}
		else if (strcmp(firstCmd, "perimeters") == 0)
		{
			sc.printPerimeters();
			std::cout << std::endl;
			continue;
		}
		else if (strcmp(firstCmd, "areas") == 0)
		{
			sc.printAreas();
			std::cout << std::endl;
			continue;
		}
		else if (strcmp(firstCmd, "perimeter") == 0)
		{
			int index = convertToInt(secondCmd) - 1;
			double perimeter = sc.getPerOfFigureByIndex(index);

			if (perimeter == -1)
				std::cout << "There is no figure " << index + 1 << std::endl << std::endl;
			else
				std::cout << '\t' << index + 1 << ". perimeter: " << perimeter << std::endl << std::endl;
		}
		else if (strcmp(firstCmd, "area") == 0)
		{
			int index = convertToInt(secondCmd) - 1;
			double area = sc.getAreaOfFigureByIndex(index);

			if (area == -1)
				std::cout << "There is no figure " << index + 1 << std::endl << std::endl;
			else
				std::cout << '\t' << index + 1 << ". area: " << area << std::endl << std::endl;
		}
		else if (strcmp(firstCmd, "save") == 0)
		{
			sc.save(currentFile);
			std::cout << "Successfully saved the changes to " << currentFile << std::endl << std::endl;
			continue;
		}
	} while (true);

	return true;
}

void wordStartEndIndexes(const char* word, int& start, int& end, int startWord)
{
	start = -1;
	end = -1;

	if (isValidCharacter(word[startWord]))
		start = startWord;

	for (int i = startWord; i < strlen(word); i++)
	{
		if (start == -1 && (word[i] == ' ' || word[i] == '\t') && isValidCharacter(word[i + 1]))
			start = i + 1;

		if (isValidCharacter(word[i]) && (word[i + 1] == ' ' || word[i + 1] == '\t' || word[i + 1] == '\n' || word[i + 1] == '\0'))
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

	if (isValidCharacter(word[0]))
		cnt++;

	for (int i = 0; i < strlen(word); i++)
	{
		if ((word[i] == ' ' || word[i] == '\t') && isValidCharacter(word[i + 1]))
			cnt++;
	}

	return cnt;
}

bool isValidCommand(const char* first, const char* second, const char* third, const char* fourth, const char* fifth, const char* sixth, const char* seventh)
{
	if (strcmp(first, "open") == 0)
		return second[0] != '\0' && third[0] == '\0';

	if (strcmp(first, "print") == 0)
		return second[0] == '\0';

	if (strcmp(first, "create") == 0)
	{
		if (strcmp(second, "rectangle") == 0)
			return isNumber(third) && isNumber(fourth) && isNumber(fifth) && strToDouble(fifth) > 0 &&
			isNumber(sixth) && strToDouble(sixth) > 0 && seventh[0] != '\0';

		if (strcmp(second, "circle") == 0)
			return isNumber(third) && isNumber(fourth) && 
			isNumber(fifth) && strToDouble(fifth) > 0 && sixth[0] != '\0' && seventh[0] == '\0';

		if (strcmp(second, "line") == 0)
			return isNumber(third) && isNumber(fourth) && isNumber(fifth) && isNumber(sixth) && seventh[0] != '\0';
	}

	if (strcmp(first, "within") == 0)
	{
		if (strcmp(second, "rectangle") == 0)
			return isNumber(third) && isNumber(fourth) && isNumber(fifth) && strToDouble(fifth) > 0 &&
			isNumber(sixth) && strToDouble(sixth) > 0 && seventh[0] == '\0';

		if (strcmp(second, "circle") == 0)
			return isNumber(third) && isNumber(fourth) && isNumber(fifth) && strToDouble(fifth) > 0 && sixth[0] == '\0';
	}

	if (strcmp(first, "point") == 0)
		return isNumber(second) && isNumber(third) && fourth[0] == '\0';

	if (strcmp(first, "erase") == 0)
		return isPositiveInteger(second) && third[0] == '\0';

	if (strcmp(first, "translate") == 0)
		return isPositiveInteger(second) && isNumber(third) && (isNumber(fourth) || fourth[0] == '\0') && fifth[0] == '\0';

	if (strcmp(first, "perimeter") == 0)
		return isPositiveInteger(second) && third[0] == '\0';

	if (strcmp(first, "area") == 0)
		return isPositiveInteger(second) && third[0] == '\0';

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
				if (str[i] == '-' && i == 0 && strlen(str) > 1)
					continue;
				return false;
			if (hasPoint)
				return false;
			hasPoint = true;
		}
	}

	return true;
}

bool isPositiveInteger(const char* str)
{
	if (strlen(str) == 0)
		return false;

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

int convertToInt(const char* str) 
{
	int num = 0;

	for(int i = 0; i < strlen(str); i++)
	{
		num *= 10;
		num += str[i] - '0';
	}

	return num;
}

bool isValidCharacter(char ch)
{
	return ch == '-' || ch == '_' || ch == '.' || 
		(ch >= 'a' && ch <= 'z') || (ch >= 'A' && ch <= 'Z') || (ch >= '0' && ch <= '9');
}

bool hasOnlyValidCharacters(const char* str)
{
	for (int i = 0; i < strlen(str); i++)
	{
		if (!isValidCharacter(str[i]) && str[i] != ' ' && str[i] != '\t' && str[i] != '\n')
			return false;
	}

	return true;
}