#include <iostream>
#include <cctype>
#include "Cipher.h"
using namespace std;
void check(const wstring& Text, const wstring& key, const bool destructCipherText=false)
{
    try {
        wstring cipherText;
        wstring decryptedText;
        Cipher cipher(key);
        cipherText = cipher.encrypt(Text);
        if (destructCipherText)
            cipherText.front() = tolower(cipherText.front());
        decryptedText = cipher.decrypt(cipherText);
        wcout<<"key="<<key<<endl;
        wcout<<Text<<endl;
        wcout<<cipherText<<endl;
        wcout<<decryptedText<<endl;
    } catch (const cipher_error & e) {
        cerr<<"Error: "<<e.what()<<endl;
    }
}
int main(int argc, char **argv)
{
    locale loc("ru_RU.UTF-8");
    locale::global(loc);
    wcout<<L'-'<<endl;
    check(L"ЭТОРАНДОМНЫЙТЕКСТ",L"ПРИВЕТ");
    wcout<<L'-'<<endl;
    check(L"ЭТОРАНДОМНЫЙТЕКСТ",L"");
    wcout<<L'-'<<endl;
    check(L"ЭТОРАНДОМНЫЙТЕКСТ",L"П1Р2И3В4Е5Т6");
    wcout<<L'-'<<endl;
    check(L"ЭТО РАНДОМНЫЙ ТЕКСТ",L"ПРИВЕТ");
    wcout<<L'-'<<endl;
    check(L"ЭТОРАНДОМНЫЙТЕКСТ",L"ПРИВЕТ",true);
    wcout<<L'-'<<endl;
    check(L"21908321786912367801327860",L"ПРИВЕТ");
    wcout<<L'-'<<endl;
    return 0;
}
