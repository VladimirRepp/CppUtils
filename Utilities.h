#pragma once

#include <string>
using namespace System;
using namespace System::Windows::Forms;

// --- Прототипы функций --- 
std::string ConvertToString(System::String^ s); // конвертируем System::string ^ в std::string
String^ ConvertToString(std::string& os);		// конвертируем std::string в System::string ^  

/// <summary>
/// Вспомогательные функции для работы со стороками
/// </summary>
namespace StringHelper {
	/// <summary>
	/// Конвертирует System::string^ в std::string
	/// </summary>
	/// <param name="s"> - системная строка</param>
	/// <returns></returns>
	std::string ConvertToString(System::String^ s);

	/// <summary>
	/// Конвертируеи std::string в System::string^  
	/// </summary>
	/// <param name="os"> - стандартная строка</param>
	/// <returns></returns>
	String^ ConvertToString(std::string& os);	  
}

/// <summary>
/// Вывод соообщений в MessageBox WinForm
/// </summary>
namespace Messager {
	void WarningMessage(String^ mess);
	void ExceptionMessage(String^ mess);
	void ExceptionMessage(Exception^ ex);
	void Message(String^ mess, String^ header);
}
