#include <iostream>
#include <cctype>
#include "modAlphaCipher.h"
#include <locale>
using namespace std;

void check(const wstring& Text, const wstring& key, const bool destructCipherText=false)
{
	try {
		wstring cipherText;
		wstring decryptedText;
		modAlphaCipher cipher(key);
		cipherText = cipher.encrypt(Text);
		if (destructCipherText)
			cipherText.front() = towlower(cipherText.front());
		decryptedText = cipher.decrypt(cipherText);
		wcout<<"key:"<<key<<endl;
		wcout<<Text<<endl;
		wcout<<cipherText<<endl;
		wcout<<decryptedText<<endl;
	} catch (const cipher_error & e) {
		wcerr<<"Error: "<<e.what()<<endl;
	}
}

int main()
{
	locale loc("ru_RU.UTF-8");
	locale::global(loc);
	check(L"СПАСИОТСЕССИИ",L"Спасу");
	wcout << "-------------" << endl;
	check(L"СПАСИОТСЕССИИ",L"СПАСУ");
	wcout << "-------------" << endl;
	check(L"СПАСИОТСЕССИИ",L"!СПАСУ!");
	wcout << "-------------" << endl;
	check(L"СПАСИ ОТ СЕСИИ",L"11032002");
	wcout << "-------------" << endl;
	check(L"СПАСИОТСЕССИИ",L"ЛТЦ",true);
	wcout << "-------------" << endl;
	check(L"№;%?:*()446484,,,,,,,,,",L"ЛТЦ");
	return 0;
}
