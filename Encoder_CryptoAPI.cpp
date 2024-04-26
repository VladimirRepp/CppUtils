#include "Encoder_CryptoAPI.h"

bool Encoder_CryptoAPI::ExportKey()
{
	HCRYPTKEY hPublicKey;

	// Получение ключа для экспорта ключа шифрования
	if (!CryptGetUserKey(hProv, AT_KEYEXCHANGE, &hPublicKey)) {
		MyHandleError("Encoder_CryptoAPI::ExportKey(): CryptGetUserKey() is Fail!");
		return false;
	}

	MyHandleMessage("Открытый ключ получен!");

	DWORD count = 0;
	// Получение размера массива, используемого для экспорта ключа
	if (!CryptExportKey(hSessionKey, hPublicKey, PUBLICKEYBLOB, 0, NULL, &count)) {
		MyHandleError("Encoder_CryptoAPI::ExportKey(): CryptExportKey() is Fail!");
		return false;
	}

	// Инициализация массива, используемого для экспорта ключа
	BYTE* data = static_cast<BYTE*>(malloc(count));
	ZeroMemory(data, count);

	// Экспорт ключа шифрования
	if (!CryptExportKey(hSessionKey, hPublicKey, PUBLICKEYBLOB, 0, data, &count)) {
		MyHandleError("Encoder_CryptoAPI::ExportKey(): CryptExportKey() is Fail!");
		return false;
	}

	MyHandleMessage("Экспорт ключа завершен!");
	return true;
}

bool Encoder_CryptoAPI::ImportKey()
{
	HCRYPTKEY hPublicKey, hNewKey;

	// Получение ключа для импорта ключа шифрования
	if (!CryptGetUserKey(hProv, AT_KEYEXCHANGE, &hPublicKey)) {
		MyHandleError("Encoder_CryptoAPI::ImportKey(): CryptGetUserKey() is Fail!");
		return false;
	}
	MyHandleMessage("Открытый ключ получен!");

	DWORD count = 0;
	// Получение размера массива, используемого для экспорта ключа
	if (!CryptExportKey(hSessionKey, hPublicKey, PUBLICKEYBLOB, 0, NULL, &count)) {
		MyHandleError("Encoder_CryptoAPI::ImportKey(): CryptExportKey() is Fail!");
		return false;
	}

	// Инициализация массива, используемого для экспорта ключа
	BYTE* data = static_cast<BYTE*>(malloc(count));
	ZeroMemory(data, count);

	// Импорт ключа шифрования из полученного массива данных
	if (!CryptImportKey(hProv, data, count, hPublicKey, 0, &hNewKey)) {
		MyHandleError("Encoder_CryptoAPI::ImportKey(): CryptImportKey() is Fail!");
		return false;
	}

	MyHandleMessage("Импорт ключа завершен!");
	hSessionKey = hNewKey;

	return true;
}

void Encoder_CryptoAPI::MyHandleMessage(string message)
{
	if (!isHandleMessage)
		return;

	cout << message << endl;
}

void Encoder_CryptoAPI::MyHandleError(string message)
{
	if (!isHandleMessage)
		return;

	cout <<"Ошибка! Сообщение: " << message << endl;
}

Encoder_CryptoAPI::Encoder_CryptoAPI(EStateKey stateKey, bool isHandleMessage)
{
	this->isHandleMessage = isHandleMessage;

	// Получение контекста криптопровайдера
	if (!CryptAcquireContext(&hProv, NULL, // TEXT("{EB57ED8A-CCCC-4bf5-8659-9DF2F05F24AD}")
		NULL, PROV_RSA_FULL, CRYPT_VERIFYCONTEXT))
	{
		MyHandleError("Encoder_CryptoAPI::Encoder_CryptoAPI(): CryptAcquireContext Is Fail!");
		return;
	}
	MyHandleMessage("Провайдер криптографии инициализирован . . .");

	if (stateKey == EStateKey::Gen) {
		// Генерация сеансового ключа ключа
	/*	if (!CryptGenKey(hProv, CALG_RC4,
			CRYPT_EXPORTABLE | CRYPT_ENCRYPT | CRYPT_DECRYPT, &hSessionKey))*/

		if (!CryptGenKey(hProv, CALG_RC4, CRYPT_EXPORTABLE, &hSessionKey))
		{
			MyHandleError("Encoder_CryptoAPI::Encoder_CryptoAPI(): CryptGenKey Is Fail!");
			return;
		}
		MyHandleMessage("Сеансовый ключ сгенерирован . . .");
	}
	else if (stateKey == EStateKey::Import) {
		// Импорт сеансового ключа
		if (!ImportKey()) {
			MyHandleError("Encoder_CryptoAPI::Encoder_CryptoAPI(): ImportKey Is Fail!");
			return;
		}
	}
}

Encoder_CryptoAPI::~Encoder_CryptoAPI()
{
	if (hSessionKey)
		CryptDestroyKey(hSessionKey);

	if (hProv)
		CryptReleaseContext(hProv, 0);
}

bool Encoder_CryptoAPI::SaveKey()
{
	//return ExportKey();

	ofstream fout("sk.bit", ios::out | ios::binary);
	fout << hSessionKey;
	fout.close();

	return true;
}

bool Encoder_CryptoAPI::LoadKey()
{
	//return ImportKey();

	ifstream fin("sk.bit", ios::binary);
	fin >> hSessionKey;
	fin.close();

	return true;
}

void Encoder_CryptoAPI::SetKey(HCRYPTKEY hSessionKey)
{
	this->hSessionKey = hSessionKey;
}

string Encoder_CryptoAPI::Encrypt(string source_str, bool isDebugPrint)
{
	// Данные для шифрования
	string encrypt_txt = source_str;
	DWORD count = source_str.length();

	// Шифрование данных
	if (!CryptEncrypt(hSessionKey, 0, true, 0, (BYTE*)encrypt_txt.c_str(), &count, strlen(encrypt_txt.c_str())))
	{
		MyHandleError("Encoder::Encrypt(): CryptEncrypt Is Fail!");
		return string();
	}

	MyHandleMessage("Шифрование завершено!");

	if (isDebugPrint) {
		// Тестовый вывод на экран
		cout << "Зашифрованная строка: " << encrypt_txt << endl;
		cout << "Длина строки: " << encrypt_txt.length() << endl;
	}

	return encrypt_txt;
}

string Encoder_CryptoAPI::Decrypt(string source_str, bool isDebugPrint)
{
	DWORD count = source_str.length();
	string decrypt_str = source_str;

	if (isDebugPrint) {
		// Тестовый вывод на экран
		cout << "Исходная строка: " << source_str << endl;
		cout << "Длина строки: " << source_str.length() << endl;
	}

	if (!CryptDecrypt(hSessionKey, 0, true, 0, (BYTE*)decrypt_str.c_str(), &count))
	{
		MyHandleError("Encoder::Decrypt(): CryptDecrypt Is Fail!");
		return string();
	}

	if (isDebugPrint) {
		// Тестовый вывод на экран
		cout << "Расшифрованная строка: " << decrypt_str << endl;
		cout << "Длина строки: " << decrypt_str.length() << endl;
	}

	return decrypt_str;
}
