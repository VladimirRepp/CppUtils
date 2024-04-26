#pragma once
#define MY_ENCODING_TYPE  (PKCS_7_ASN_ENCODING | X509_ASN_ENCODING)

#include "ConsoleHelper.h"

#include <iostream>
#include <windows.h>
#include <wincrypt.h>
#include <stdio.h>
#include <string>
#include <fstream>
using namespace std;

#pragma comment(lib, "crypt32.lib")

enum EStateKey {
	Non,
	Gen,
	Import,
	Export
};

/// <summary>
/// Based On CryptoAPI
/// </summary>
class Encoder_CryptoAPI
{
private:
	EStateKey stateKey;
	bool isHandleMessage;

	HCRYPTPROV hProv;
	HCRYPTKEY hSessionKey;

	bool ExportKey();
	bool ImportKey();

	void MyHandleMessage(string);
	void MyHandleError(string);

public:
	Encoder_CryptoAPI(EStateKey stateKey, bool isHandleMessage = false);
	~Encoder_CryptoAPI();

	bool SaveKey();
	bool LoadKey();

	void SetKey(HCRYPTKEY hSessionKey);
	HCRYPTKEY GetKey() { return hSessionKey; }

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

	Encoder_CryptoAPI encoder_en(EStateKey::Gen, true);
	Encoder_CryptoAPI encoder_de(EStateKey::Non, true);

	string coder_str = encoder_en.Encrypt("УниверПервый", true);
	encoder_en.SaveKey();

	system("pause");
	cout << endl;
	
	//encoder_de.SetKey(encoder_en.GetKey());
	encoder_de.LoadKey();
	encoder_de.Decrypt(coder_str, true);

	system("pause");
	return;
}
*/

