#pragma once
using namespace System;
using namespace System::IO;
using namespace System::Windows::Forms;

ref class  Logger
{
private:
	ToolStripLabel^ _port_toolStripLable = nullptr;
	Label^ _port_label = nullptr;
	TextBox^ _port_textBox = nullptr;
	RichTextBox^ _port_richTextBox = nullptr;
	String^ _port_pathToTxtFile = nullptr;
	bool _port_isInMessageBox = false;

	String^ _port_defaultTxtLogFile = "..\\Log.txt";

public:
	Logger();
	Logger(ToolStripLabel^ port_toolStripLable);
	Logger(Label^ port_labe);
	Logger(TextBox^ port_textBox);
	Logger(RichTextBox^ _port_richTextBox);
	Logger(String^ _port_pathToTxtFile);
	Logger(bool port_isInMessageBox);

	Logger(ToolStripLabel^ port_toolStripLable, Label^ port_labe, TextBox^ port_textBox, 
		RichTextBox^ port_richTextBox, String^ port_pathToTxtFile, bool port_isInMessageBox);

	property ToolStripLabel^ SetPortToolStripLabel {
		void set(ToolStripLabel^ value) {
			_port_toolStripLable = value;
		}
	}

	property Label^ SetPortLabel {
		void set(Label^ value) {
			_port_label = value;
		}
	}

	property TextBox^ SetTextBox {
		void set(TextBox^ value) {
			_port_textBox = value;
		}
	}

	property RichTextBox^ SetPortRichTextBox {
		void set(RichTextBox^ value) {
			_port_richTextBox = value;
		}
	}

	property String^ SetPortPathToTxtFile {
		void set(String^ value) {
			_port_pathToTxtFile = value;
		}
	}

	property bool SetPortIsInMessageBox {
		void set(bool value) {
			_port_isInMessageBox = value;
		}
	}

	void MessageToToolStripLabel(ToolStripLabel^ port, String^ message);
	void MessageToToolStripLabel(String^ message);

	void MessageToLabel(Label^ port, String^ message);
	void MessageToLabel(String^ message);

	void MessageToTextBox(TextBox^ port, String^ message);
	void MessageToTextBox(String^ message);

	void MessageToRichTextBox(RichTextBox^ port, String^ message);
	void MessageToRichTextBox(String^ message);

	void MessageToTxtFile(String^ port, String^ message);
	void MessageToTxtFile(String^ message);

	void MessageToMessageBox(String^ message, String^ header);

	void MessageToException(String^ message);

	void Message(String^ message, String^ header);
	void Message(String^ message);
};

