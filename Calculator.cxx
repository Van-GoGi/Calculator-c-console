#include <iostream>
#include <vector>
#include <string>
#include <conio.h>

using namespace std;

vector<int> nums;
string opers;

bool checkSymbolOper(char symbol)
{
	switch (symbol)
	{
	case '+':
	case '-':
	case '*':
	case '/':
	case '=':
		return true;
	default:
		return false;
	}
}

bool checkNums(char symbol)
{
	static string allNums("1234567890");

	for (int i = 0; i < allNums.size(); i++)
	{
		if (allNums.at(i) == symbol)
			return true;
	}

	return false;
}

void addNumber(string &text)
{
	if (text != "")
		nums.push_back(stoi(text));
}

void addOperator(char symbol)
{
	opers.push_back(symbol);
}

int checkPriorityOperators()
{
	for (int i = 0; i < opers.size(); i++)
	{
		if (opers.at(i) == '*' || opers.at(i) == '/')
			return i;
	}

	return 0;
}

void calculateMathOperations()
{
	while (nums.size() > 1)
	{
		int index = checkPriorityOperators();
		switch (opers.at(index))
		{
		case '+':
			nums[index] = nums[index] + nums[index + 1];
			nums.erase(nums.begin() + index + 1);
			opers.erase(opers.begin() + index);
			break;
		case '-':
			nums[index] = nums[index] - nums[index + 1];
			nums.erase(nums.begin() + index + 1);
			opers.erase(opers.begin() + index);
			break;
		case '*':
			nums[index] = nums[index] * nums[index + 1];
			nums.erase(nums.begin() + index + 1);
			opers.erase(opers.begin() + index);
			break;
		case '/':
			nums[index] = nums[index] / nums[index + 1];
			nums.erase(nums.begin() + index + 1);
			opers.erase(opers.begin() + index);
			break;
		}
	}
}

int main()
{
	string displayText, numbText;
	char input;
	bool run = true;
	bool endMathOper = false;

	while (run)
	{
		input = _getch();
		if (checkNums(input) && endMathOper)
		{
			displayText.clear();
			nums.clear();
			endMathOper = false;
		}
		displayText.push_back(input);

		system("clear");

		if (input == 'q')
			run = false;
		else
		{
			if (checkSymbolOper(input) && (numbText.size() > 0 || nums.size() > 0))
			{
				if (input != '=')
				{
					addNumber(numbText);
					addOperator(input);
					endMathOper = false;
				}
				else
				{
					addNumber(numbText);
					calculateMathOperations();
					displayText = to_string(nums[0]);
					endMathOper = true;
				}
				numbText.clear();
			}
			else if (checkNums(input))
			{
				numbText.push_back(input);
			}
			cout << displayText;
		}
	}

	return 0;
}