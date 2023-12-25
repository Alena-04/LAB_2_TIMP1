/** @file
	*@author Елинова А.С
	*@version 1.0
	*@date 25.12.23
	*@copyright ИБСТ ПГУ
	*@warning LAB_4
	*@brief Заголовочный файл для модуля modAlphaCipher
*/
#pragma once
#include <vector>
#include <string>
#include <map>
#include <locale>
#include <codecvt>
using namespace std;
/** @brief Шифрование методом Гронсфельда
 * @details Ключ устанавливается в конструкторе.
 * Для зашифровывания и расшифровывания предназначены методы encrypt и decrypt.
 * @warning Реализация только для русского языка
 */
class modAlphaCipher
{
private:
	wstring_convert<codecvt_utf8<wchar_t>, wchar_t> codec;
	wstring numAlpha =L"АБВГДЕЁЖЗИЙКЛМНОПРСТУФХЦЧШЩЪЫЬЭЮЯ"; //алфавит по порядку
	map <wchar_t,int> alphaNum; //ассоциативный массив "номер по символу"
	vector <int> key; //ключ
	vector<int> convert(const wstring& s); //преобразование строка-вектор
	wstring convert(const vector<int>& v); //преобразование вектор-строка
	wstring getValidKey(const wstring & s);
	wstring getValidOpenText(const wstring & s);
	wstring getValidCipherText(const wstring & s);
public:
	modAlphaCipher()=delete; //запретим конструктор без параметров
	modAlphaCipher(const wstring& skey); //конструктор для установки ключа
	/**
     * @brief Зашифрование
     * @details Формируется вектор "work" из строки  текста с помощью метода
     *   convert().  Происходит проверка текста на наличие ошибки методом getValidAlphabetText().
     *  @code
     *       vector<int> work = convert(getValidAlphabetText(open_text));
     * @endcode
     *  В цикле каждому элементу вектора прибавляется элемент ключа по модулю  размера
     *   алфавита. 
     *  @code
     *   for(unsigned i=0; i < work.size(); i++) {
     *      work[i] = (work[i] + key[i % key.size()]) % alphaNum.size();
     *   }
     * @endcode
     * @param wstring open_text - текст, для зашифрования
     * @throw cipher_error - строка, пришедшея на вход, кторая оказывается пустой или в ней есть недопустимые символы
     * @return строка зашифрованного текста типа "wstring"
     */
	wstring encrypt(const wstring& open_text); //зашифрование
	/**
     * @brief 	Расшифрование
     * @details Формируется вектор "work" из строки  зашифрованного текста с помощью метода
     *   convert().  А также   зашифрованный текст проверяется на наличие ошибки  методом getValidAlphabetText().
     *  @code
     *       vector<int> work = convert(getValidAlphabetText(cipher_text));
     * @endcode
     *  Если при зашифровывании прибавляется значение ключа, то при расшифровывании значения ключа вычитается.
     *  @code
     *   for(unsigned i=0; i < work.size(); i++) {
     *           work[i] = (work[i] + alphaNum.size() - key[i % key.size()]) % alphaNum.size();
     *   }
     * @endcode
     *
     * @param wstring cipher_text - текст расшифрования
     * @throw cipher_error - строка, пришедшея на вход, кторая оказывается пустой или в ней есть недопустимые символы
     * @return  строка расшифрованного текста типа "wstring"
     */
	wstring decrypt(const wstring& cipher_text);//расшифрование
};
//! @class cipher_error - возбуждение исключений.
class cipher_error: public invalid_argument
{
public:
	explicit cipher_error (const string& what_arg):
		invalid_argument(what_arg) {}
	explicit cipher_error (const char* what_arg):
		invalid_argument(what_arg) {}
};
