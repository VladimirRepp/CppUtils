#pragma once
#include <string>
#include <iostream>
using namespace std;

namespace ConsoleHelper {
	void Write(string message);
	void WriteLine(string message);
	void Write(string message, string header);
	void WriteLine(string message, string header);
	void WriteWarning(string message);
	void WriteLineWarning(string message);
	void WriteError(string message);
	void WriteLineError(string message);
	void WriteException(string message);
	void WriteLineException(string message);
}

