#include "Logger.h"

#pragma region Constructors

Logger::Logger()
{
    _port_toolStripLable = nullptr;
    _port_label = nullptr;
    _port_textBox = nullptr;
    _port_richTextBox = nullptr;
    _port_pathToTxtFile = nullptr;
    _port_isInMessageBox = false;
    _port_defaultTxtLogFile = "..\\Log.txt";
}

Logger::Logger(ToolStripLabel^ port_toolStripLable)
{
    _port_toolStripLable = port_toolStripLable;
}

Logger::Logger(Label^ port_labe)
{
    _port_label = port_labe;
}

Logger::Logger(TextBox^ port_textBox)
{
    _port_textBox = port_textBox;
}

Logger::Logger(RichTextBox^ port_richTextBox)
{
    _port_richTextBox = port_richTextBox;
}

Logger::Logger(String^ port_pathToTxtFile)
{
    _port_pathToTxtFile = port_pathToTxtFile;
}

Logger::Logger(bool port_isInMessageBox)
{
    _port_isInMessageBox = port_isInMessageBox;
}

Logger::Logger(ToolStripLabel^ port_toolStripLable, Label^ port_labe, TextBox^ port_textBox,
    RichTextBox^ port_richTextBox, String^ port_pathToTxtFile, bool port_isInMessageBox)
{
    _port_toolStripLable = port_toolStripLable;
    _port_label = port_labe;
    _port_textBox = port_textBox;
    _port_richTextBox = port_richTextBox;
    _port_pathToTxtFile = port_pathToTxtFile;
    _port_isInMessageBox = port_isInMessageBox;
}

#pragma endregion

#pragma region Methods

void Logger::MessageToToolStripLabel(ToolStripLabel^ port, String^ message)
{
    port->Text = message;
}

void Logger::MessageToToolStripLabel(String^ message)
{
    if (_port_toolStripLable != nullptr)
        _port_toolStripLable->Text = message;
    else
        throw gcnew Exception("Logger::MessageToToolStripLabel(String^ message): port is NULL");
}

void Logger::MessageToLabel(Label^ port, String^ message)
{
    port->Text = message;
}

void Logger::MessageToLabel(String^ message)
{
    if (_port_label != nullptr)
        _port_label->Text = message;
    else
        throw gcnew Exception("Logger::MessageToLabel(String^ message): port is NULL");
}

void Logger::MessageToTextBox(TextBox^ port, String^ message)
{
    port->Text = message;
}

void Logger::MessageToTextBox(String^ message)
{
    if (_port_textBox != nullptr)
        _port_textBox->Text = message;
    else
        throw gcnew Exception("Logger::MessageToTextBox(String^ message): port is NULL");
}

void Logger::MessageToRichTextBox(RichTextBox^ port, String^ message)
{
    port->Text = message;
}

void Logger::MessageToRichTextBox(String^ message)
{
    if (_port_richTextBox != nullptr)
        _port_richTextBox->Text = message;
    else
        throw gcnew Exception("Logger::MessageToRichTextBox(String^ message): port is NULL");
}

void Logger::MessageToTxtFile(String^ port, String^ message)
{
    StreamWriter^ sw;

    try {
        String^ fileName = port;

        sw = gcnew StreamWriter(fileName, true);
        sw->WriteLine(message);
    }
    catch (Exception^ ex) {
        throw gcnew Exception("Logger::MessageToTxtFile(String^ port, String^ message): " + ex->Message);
    }
    finally{
        sw->Close();
    }
}

void Logger::MessageToTxtFile(String^ message)
{
    if (_port_pathToTxtFile != nullptr)
        if(_port_pathToTxtFile != "")
            MessageToTxtFile(_port_pathToTxtFile, message);
        else
            throw gcnew Exception("MessageToTxtFile(String^ message): port is NULL");
    else
        throw gcnew Exception("MessageToTxtFile(String^ message): port is NULL");
}

void Logger::MessageToMessageBox(String^ message, String^ header)
{
    if (_port_isInMessageBox)
        MessageBox::Show(message, header);
}

void Logger::MessageToException(String^ message)
{
    MessageBox::Show(message, "Вызвано исключение!");

    DateTime^ dt = gcnew DateTime();
    String^ txt = dt->Now.ToString();
    txt += " - " + message;

    MessageToTxtFile(_port_defaultTxtLogFile, txt);

    if (_port_pathToTxtFile != nullptr)
        if (_port_pathToTxtFile != "")
            MessageToTxtFile(_port_pathToTxtFile, txt);
}

void Logger::Message(String^ message, String^ header)
{
    if (_port_isInMessageBox)
        MessageToMessageBox(message, header);

    if (_port_label)
        MessageToLabel(_port_label, message);

    if (_port_pathToTxtFile)
        MessageToTxtFile(_port_pathToTxtFile, message);

    if (_port_richTextBox)
        MessageToRichTextBox(_port_richTextBox, message);

    if (_port_textBox)
        MessageToTextBox(_port_textBox, message);

    if (_port_toolStripLable)
        MessageToToolStripLabel(_port_toolStripLable, message);
}

void Logger::Message(String^ message)
{
    Message(message, "Внимание!");
}

#pragma endregion
