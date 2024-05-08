#include "Utilities.h"

#pragma region Functions
std::string ConvertToString(System::String^ s) {
	using namespace Runtime::InteropServices;
	const char* chars =
		(const char*)(Marshal::StringToHGlobalAnsi(s)).ToPointer();
	std::string	os = chars;
	Marshal::FreeHGlobal(IntPtr((void*)chars));

	return os;
}

System::String^ ConvertToString(std::string& os) {
	System::String^ s = gcnew System::String(os.c_str());

	return s;
}

int MyRandom(int from, int to) {
	return rand()% (to - from + 1) + from;
}
#pragma endregion

#pragma region Messager WinForm
void Messager::WarningMessage(String^ mess)
{
	MessageBox::Show(mess, "Внимание!");
}

void Messager::ExceptionMessage(String^ mess)
{
	MessageBox::Show(mess, "Вызвано исключение!");
}

void Messager::ExceptionMessage(Exception^ ex, String^ pathFile)
{
	StreamWriter^ sw;

	DateTime^ dt = gcnew DateTime();
	String^ txt = dt->Now.ToString();
	txt += " - " + ex->Message;

	try {
		sw = gcnew StreamWriter(pathFile, true);
		sw->WriteLine(txt);
	}
	catch (Exception^ exMessager) {
		throw gcnew Exception("Messager::MessageToTxtFile(): " + exMessager->Message);
	}
	finally {
		sw->Close();
	}

	MessageBox::Show(ex->Message, "Вызвано исключение!");
}

void Messager::Message(String^ mess, String^ header)
{
	MessageBox::Show(mess, header);
}
#pragma endregion

#pragma region StringHelper
std::string StringHelper::ConvertToString(System::String^ s)
{
	using namespace Runtime::InteropServices;
	const char* chars =
		(const char*)(Marshal::StringToHGlobalAnsi(s)).ToPointer();
	std::string	os = chars;
	Marshal::FreeHGlobal(IntPtr((void*)chars));

	return os;
}

String^ StringHelper::ConvertToString(std::string& os)
{
	System::String^ s = gcnew System::String(os.c_str());

	return s;
}
#pragma endregion

#pragma region ConsoleHelper

void ConsoleHelper::Write(std::string message)
{
	std::cout << message;
}

void ConsoleHelper::WriteLine(std::string message)
{
	std::cout << message << std::endl;
}

void ConsoleHelper::Write(std::string message, std::string header)
{
	std::cout << header << " " << message;
}

void ConsoleHelper::WriteLine(std::string message, std::string header)
{
	std::cout << header << " " << message << std::endl;
}

void ConsoleHelper::WriteWarning(std::string message)
{
	std::cout << "Внимание! " << message;
}

void ConsoleHelper::WriteLineWarning(std::string message)
{
	std::cout << "Внимание! " << message << std::endl;
}

void ConsoleHelper::WriteException(std::string message)
{
	std::cout << "Исключение! Сообщение: " << message;
}

void ConsoleHelper::WriteLineException(std::string message)
{
	std::cout << "Исключение! Сообщение: " << message << std::endl;
}
#pragma endregion

