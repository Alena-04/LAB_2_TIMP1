#include "Cipher.h"
using namespace std;
Cipher::Cipher(const std::wstring& skey)
{
    for (unsigned i=0; i<numAlpha.size(); i++) {
        alphaNum[numAlpha[i]]=i;
    }
    key = convert(getValidKey(skey));
}

std::wstring Cipher::encrypt(const std::wstring& open_text)
{
    std::locale loc("ru_RU.UTF-8");
    std::vector<int> work = convert(getValidOpenText(open_text));
    for(unsigned i=0; i < work.size(); i++) {
        work[i] = (work[i] + key[i % key.size()]) % alphaNum.size();
    }
    return convert(work);
}

std::wstring Cipher::decrypt(const std::wstring& cipher_text)
{
    std::vector<int> work = convert(getValidCipherText(cipher_text));
    for(unsigned i=0; i < work.size(); i++) {
        work[i] = (work[i] + alphaNum.size() - key[i % key.size()]) % alphaNum.size();
    }
    return convert(work);
}

inline std::vector<int> Cipher::convert(const std::wstring& s)
{
    std::vector<int> result;
    for(auto c:s) {
        result.push_back(alphaNum[c]);
    }
    return result;
}
inline std::wstring Cipher::convert(const std::vector<int>& v)
{
    std::wstring result;
    for(auto i:v) {
        result.push_back(numAlpha[i]);
    }
    return result;
}
inline std::wstring Cipher::getValidKey(const std::wstring & in)
{
    if (in.empty()) throw cipher_error("Empty key");

    wstring tmp;
    std::locale loc("ru_RU.UTF-8");

    for (wchar_t c : in) {
        if (c >= L'А' && c <= L'Я') {
            tmp += c;
        } else if (c >= L'а' && c <= L'я') {
            tmp += toupper(c, loc);
        } else {
            throw cipher_error("Invalid key");
        }
    }

    return tmp;
}
inline std::wstring Cipher::getValidOpenText(const std::wstring & in)
{
    if (in.empty()) throw cipher_error("Empty Open Text");

    wstring tmp;
    std::locale loc("ru_RU.UTF-8");

    for (wchar_t c : in) {
        if (c >= L'А' && c <= L'Я') {
            tmp += c;
        } else if (c >= L'а' && c <= L'я') {
            tmp += toupper(c, loc);
        } else {
            throw cipher_error("Invalid Open Text");
        }
    }

    return tmp;
}
inline std::wstring Cipher::getValidCipherText(const std::wstring & in)
{
    if (in.empty()) throw cipher_error("Empty Cipher Text");

    wstring tmp;
    std::locale loc("ru_RU.UTF-8");

    for (wchar_t c : in) {
        if (c >= L'А' && c <= L'Я') {
            tmp += c;
        } else {
            throw cipher_error("Invalid Cipher Text");
        }
    }

    return tmp;
}
