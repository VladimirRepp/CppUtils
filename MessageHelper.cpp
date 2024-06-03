#include "MessageHelper.h"

void MessageHelper::Show(String^ message, String^ header)
{
	MessageBox::Show(message, header);
}

void MessageHelper::ShowWarning(String^ message)
{
	MessageBox::Show(message, "Внимание!");
}

void MessageHelper::ShowError(String^ message)
{
	MessageBox::Show(message, "Ошибка!");
}

void MessageHelper::ShowException(String^ message)
{
	MessageBox::Show(message, "Вызвано исключение!");
}
