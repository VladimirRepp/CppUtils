#include "ConsoleHelper.h"

void ConsoleHelper::Write(string message)
{
	cout << message;
}

void ConsoleHelper::WriteLine(string message)
{
	cout << message << endl;
}

void ConsoleHelper::Write(string message, string header)
{
	cout << header << " " << message;
}

void ConsoleHelper::WriteLine(string message, string header)
{
	cout << header << " " << message << endl;
}

void ConsoleHelper::WriteWarning(string message)
{
	cout << "Внимание! " << message;
}

void ConsoleHelper::WriteLineWarning(string message)
{
	cout << "Внимание! " << message << endl;
}

void ConsoleHelper::WriteError(string message)
{
	cout << "Ошибка! Сообщение: " << message;
}

void ConsoleHelper::WriteLineError(string message)
{
	cout << "Ошибка! Сообщение: " << message << endl;
}

void ConsoleHelper::WriteException(string message)
{
	cout << "Исключение! Сообщение: " << message;
}

void ConsoleHelper::WriteLineException(string message)
{
	cout << "Исключение! Сообщение: " << message << endl;
}
