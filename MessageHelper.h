#pragma once
using namespace System;
using namespace System::Windows::Forms;

namespace MessageHelper {
	void Show(String^ message, String^ header);
	void ShowWarning(String^ message);
	void ShowError(String^ message);
	void ShowException(String^ message);
}

