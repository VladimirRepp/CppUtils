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

void Messager::ExceptionMessage(Exception^ ex, String^ pathFile = "..\\Log.txt")
{
	StreamWriter^ sw;

	DateTime^ dt = gcnew DateTime();
	String^ txt = dt->Now.ToString();
	txt += " - " + ex.Message;

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
