#pragma once

#include <iostream>
#include <windows.h>
#include <wincrypt.h>
#include <stdio.h>
#include <string>
#include <fstream>
#include "ConsoleHelper.h"
using namespace std;

/// <summary>
/// Based On CryptoAPI
/// </summary>
class Encoder
{
	string path_to_session_key;

	HCRYPTPROV hProv;
	HCRYPTKEY hSessionKey;

	void SaveSessionKey();
	void LoadSessionKey();

public:
	Encoder();
	Encoder(string path_to_session_key) : path_to_session_key(path_to_session_key) { hProv = NULL; hSessionKey = NULL; }
	~Encoder();

	string Encrypt(string source_str, bool isDebugPrint = false);
	string Decrypt(string source_str, bool isDebugPrint = false);
};

/*
* === Usage Example: ===
 
#include <Windows.h>
#include "Encoder.h"

void main() {
	SetConsoleCP(1251);
	SetConsoleOutputCP(1251);

	Encoder encoder;
	string coder_str = encoder.Encrypt("”ниверѕервый", true);
	
	cout << endl;
	encoder.Decrypt(coder_str, true);

	system("pause");
	return;
}

*/

