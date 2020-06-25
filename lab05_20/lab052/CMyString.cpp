#include "CMyString.h"


CMyString::CMyString()
	: m_length(1)
	, m_pString( new char[1])
{
	m_pString[0] = '\0';
}

// конструктор, инициализирующий строку данными строки
// с завершающим нулевым символом
CMyString::CMyString(const char* pString)
{

}

// конструктор, инициализирующий строку данными из
// символьного массива заданной длины
CMyString::CMyString(const char* pString, size_t length) 
{
}

// конструктор копирования
CMyString::CMyString(CMyString const& other)
{

}

// перемещающий конструктор (для компиляторов, совместимых с C++11)
//  реализуется совместно с перемещающим оператором присваивания
CMyString::CMyString(CMyString&& other)
{

}

// конструктор, инициализирующий строку данными из
// строки стандартной библиотеки C++
CMyString::CMyString(std::string const& stlString)
{

}

// деструктор класса - освобождает память, занимаемую символами строки
CMyString::~CMyString()
{

}

// возвращает длину строки (без учета завершающего нулевого символа)
size_t CMyString::GetLength() const
{
	return m_length;
}

// возвращает указатель на массив символов строки.
// В конце массива обязательно должен быть завершающий нулевой символ
// даже если строка пустая
const char* CMyString::GetStringData() const
{
	return "";
}

// возвращает подстроку с заданной позиции длиной не больше length символов
CMyString CMyString::SubString(size_t start, size_t length) const
{
	return CMyString();
}

// очистка строки (строка становится снова нулевой длины)
void CMyString::Clear()
{

}
