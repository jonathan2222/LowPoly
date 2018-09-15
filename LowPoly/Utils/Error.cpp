#include "Error.h"

HANDLE yami::Error::hstdin = (void*)0;
HANDLE yami::Error::hstdout = (void*)0;
CONSOLE_SCREEN_BUFFER_INFO yami::Error::csbi = {};

void yami::Error::init()
{
	hstdin = GetStdHandle(STD_INPUT_HANDLE);
	hstdout = GetStdHandle(STD_OUTPUT_HANDLE);

	// Remember how things were when we started
	GetConsoleScreenBufferInfo(hstdout, &csbi);
}

void yami::Error::print(const std::string & str)
{
	print(str, CONSOLE_COLOR::WHITE);
}

void yami::Error::print(const std::string & description, const std::string & str)
{
	print(description, str, CONSOLE_COLOR::WHITE);
}

void yami::Error::print(const std::string & str, CONSOLE_COLOR color)
{
	print("", str, color);
}

void yami::Error::print(const std::string & description, const std::string & str, CONSOLE_COLOR color)
{
	print(description, "", str, color);
}

void yami::Error::print(const std::string & description1, const std::string & description2, const std::string & str, CONSOLE_COLOR color)
{
	// Tell the user how to stop
	SetConsoleTextAttribute(hstdout, color);
	const std::string s = description1 + description2;
	if (s.size() == 0)
	{
		std::cout << str.c_str() << std::endl;
	}
	else
	{
		std::cout << "[" << description1.c_str() << "::" << description2.c_str() << "]\t" << str.c_str() << std::endl;
	}
	FlushConsoleInputBuffer(hstdin);

	// Keep users happy
	SetConsoleTextAttribute(hstdout, csbi.wAttributes);
}

void yami::Error::printError(const std::string & str)
{
	printError("Error", str);

}

void yami::Error::printError(const std::string & description, const std::string & str)
{
	print("Error", description, str, CONSOLE_COLOR::RED);
}

void yami::Error::printWarning(const std::string & str)
{
	printWarning("Warning", str);
}

void yami::Error::printWarning(const std::string & description, const std::string & str)
{
	print("Warning", description, str, CONSOLE_COLOR::YELLOW);
}
