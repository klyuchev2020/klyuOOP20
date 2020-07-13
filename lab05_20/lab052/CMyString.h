#pragma once

#include "stdafx.h"
#include "CMystrIterator.h"


class CMyString
{
public:
	// конструктор по умолчанию
	CMyString();

	// конструктор, инициализирующий строку данными строки
	// с завершающим нулевым символом
	explicit CMyString(const char* pString);

	// конструктор, инициализирующий строку данными из
	// символьного массива заданной длины
	CMyString(const char* pString, size_t length);

	// конструктор копирования
	CMyString(CMyString const& other);

	// перемещающий конструктор (для компиляторов, совместимых с C++11)
	//  реализуется совместно с перемещающим оператором присваивания
	CMyString(CMyString&& other);
	CMyString& operator=(CMyString&& other);

	// конструктор, инициализирующий строку данными из
	// строки стандартной библиотеки C++
	explicit CMyString(std::string const& stlString);

	// деструктор класса - освобождает память, занимаемую символами строки
	~CMyString();

	// возвращает длину строки (без учета завершающего нулевого символа)
	size_t GetLength() const;

	// возвращает указатель на массив символов строки.
	// В конце массива обязательно должен быть завершающий нулевой символ
	// даже если строка пустая
	const char* GetStringData() const;

	// возвращает подстроку с заданной позиции длиной не больше length символов
	CMyString SubString(size_t start, size_t length = SIZE_MAX) const;

	// очистка строки (строка становится снова нулевой длины)
	void Clear();

	CMyString& operator=(const CMyString& mystr);
	CMyString operator+(const CMyString& mystr) const;
	CMyString operator+(const char* cstr) const;
	CMyString operator+(const std::string& stlstr) const;

	CMyString& operator+=(const CMyString& mystr);

	char& operator[](const size_t index);
	const char operator[](const size_t index) const;

	CMystrIterator begin() const;
	CMystrIterator end() const;
	CMystrConstIterator cbegin() const;
	CMystrConstIterator cend() const;


	friend bool operator==(const CMyString& mystr1, const CMyString& mystr2);
	friend bool operator!=(const CMyString& mystr1, const CMyString& mystr2);
	friend bool operator<(const CMyString& mystr1, const CMyString& mystr2);
	friend bool operator>(const CMyString& mystr1, const CMyString& mystr2);
	friend bool operator<=(const CMyString& mystr1, const CMyString& mystr2);
	friend bool operator>=(const CMyString& mystr1, const CMyString& mystr2);

	friend std::ostream& operator<<(std::ostream & os, const CMyString& mystr);
	friend std::istream& operator>>(std::istream& is, CMyString& mystr);

private:
	size_t m_length;
	std::unique_ptr<char[]> m_pString;
};
