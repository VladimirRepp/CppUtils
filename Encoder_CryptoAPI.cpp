#include "Encoder_CryptoAPI.h"

void Encoder_CryptoAPI::SaveSessionKey()
{
	ofstream fout(path_to_session_key, ios::trunc | ios::binary);
	fout << hSessionKey;
	fout.close();
	
	cout << "Сеансовый ключ сохранен!" << endl;
}

void Encoder_CryptoAPI::LoadSessionKey()
{
	ifstream fin(path_to_session_key, ios::binary);
	fin >> hSessionKey;
	fin.close();

	cout << "Сеансовый ключ загружен!" << endl;
}

Encoder_CryptoAPI::Encoder_CryptoAPI()
{
	path_to_session_key = "SessionKey.txt";

	hSessionKey = NULL;
	hProv = NULL;
}

Encoder_CryptoAPI::~Encoder_CryptoAPI()
{
}

string Encoder_CryptoAPI::Encrypt(string source_str, bool isDebugPrint)
{
	// Получение контекста криптопровайдера
	if (!CryptAcquireContext(&hProv, NULL, NULL,
		PROV_RSA_FULL, CRYPT_VERIFYCONTEXT))
	{
		ConsoleHelper::WriteWarning("Encoder::Crypt(): CryptAcquireContext Is Fail!");
		return string();
	}
	std::cout << "Провайдер криптографии инициализирован . . ." << std::endl;

	// Генерация сессионного ключа
	if (!CryptGenKey(hProv, CALG_RC4, CRYPT_EXPORTABLE, &hSessionKey))
	{
		ConsoleHelper::WriteWarning("Encoder::Crypt(): CryptGenKey Is Fail!");
		return string();
	}

	std::cout << "Сеансовый ключ сгенерирован . . ." << std::endl;

	// Данные для шифрования
	string encrypt_txt = source_str;
	DWORD count = source_str.length();

	// Шифрование данных
	if (!CryptEncrypt(hSessionKey, 0, true, 0, (BYTE*)encrypt_txt.c_str(), &count, strlen(encrypt_txt.c_str())))
	{
		ConsoleHelper::WriteWarning("Encoder::Crypt(): CryptEncrypt Is Fail!");
		return string();
	}

	std::cout << "Шифрование завершено!" << std::endl;

	if (isDebugPrint) {
		// Тестовый вывод на экран
		cout << "Зашифрованная строка: " << encrypt_txt << endl;
		cout << "Длина строки: " << encrypt_txt.length() << endl;
	}

	return encrypt_txt;
}

string Encoder_CryptoAPI::Decrypt(string source_str, bool isDebugPrint)
{
	// Получение контекста криптопровайдера
	if (!CryptAcquireContext(&hProv, NULL, NULL,
		PROV_RSA_FULL, CRYPT_VERIFYCONTEXT))
	{
		ConsoleHelper::WriteException("Encoder::Crypt(): CryptAcquireContext Is Fail!");
		return string();
	}
	std::cout << "Провайдер криптографии инициализирован . . ." << std::endl;

	// Загрузка сеансового ключа
	try {
		LoadSessionKey();
	}
	catch (exception ex) {
		string message = "Encoder::Decrypt(): ";
		message += ex.what();
		throw new exception(message.c_str());
	}

	DWORD count1 = source_str.length();
	string decrypt_str = source_str;

	if (isDebugPrint) {
		// Тестовый вывод на экран
		cout << "Исходная строка: " << source_str << endl;
		cout << "Длина строки: " << source_str.length() << endl;
	}

	if (!CryptDecrypt(hSessionKey, 0, true, 0, (BYTE*)decrypt_str.c_str(), &count1))
	{
		ConsoleHelper::WriteWarning("Encoder::Crypt(): CryptDecrypt Is Fail!");
		return string();
	}
	
	if (isDebugPrint) {
		// Тестовый вывод на экран
		cout << "Расшифрованная строка: " << decrypt_str << endl;
		cout << "Длина строки: " << decrypt_str.length() << endl;
	}

	return decrypt_str;
}
