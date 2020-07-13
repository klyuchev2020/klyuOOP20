#include "CMyString.h"
#include "CMystrIterator.h"

CMyString::CMyString()
	: m_length(0)
	, m_pString(new char[1])
{
	m_pString[0] = '\0';
}

// конструктор, инициализирующий строку данными строки
// с завершающим нулевым символом
CMyString::CMyString(const char* pString)
	: m_length(strlen(pString))
	, m_pString(new char[m_length + 1])
{
	for (size_t i = 0; i <= m_length; ++i)
	{
		m_pString[i] = pString[i];
	}
}

// конструктор, инициализирующий строку данными из
// символьного массива заданной длины
CMyString::CMyString(const char* pString, size_t length)
	: m_length(length)
	, m_pString(new char[m_length + 1])
{
	for (size_t i = 0; i < m_length; ++i)
	{
		m_pString[i] = pString[i];
	}
	m_pString[m_length] = '\0';
}

// конструктор копирования
CMyString::CMyString(CMyString const& other)
{
	m_length = other.m_length;
	m_pString = std::make_unique<char[]>(m_length + 1);
	for (size_t i = 0; i <= m_length; ++i)
	{
		m_pString[i] = other.m_pString[i];
	}
}

// перемещающий конструктор (для компиляторов, совместимых с C++11)
//  реализуется совместно с перемещающим оператором присваивания
CMyString::CMyString(CMyString&& other)
	: m_length(other.m_length)
	, m_pString(std::move(other.m_pString))
{
}

CMyString& CMyString::operator=(CMyString&& other)
{
	if (this != &other)
	{
		m_length = other.m_length;
		m_pString = std::move(other.m_pString);
		other.Clear();
	}
	return *this;
}

// конструктор, инициализирующий строку данными из
// строки стандартной библиотеки C++
CMyString::CMyString(std::string const& stlString)
	: m_length(stlString.size())
	, m_pString(new char[m_length + 1])
{
	std::copy(stlString.begin(), stlString.end(), m_pString.get());
	m_pString[m_length] = '\0';
}

// деструктор класса - освобождает память, занимаемую символами строки
CMyString::~CMyString()
{
	std::cout << "CMyString Dtor" << std::endl;
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
	return static_cast<const char*>(m_pString.get());
}

// возвращает подстроку с заданной позиции длиной не больше length символов
CMyString CMyString::SubString(size_t start, size_t length) const
{
	if (start >= m_length || length == 0)
	{
		return CMyString();
	}
	else
	{
		size_t substrLength = (start + length <= m_length) ? length : m_length - start;
		const char* substrData = GetStringData() + start;
		return CMyString(substrData, substrLength);
	}
}

// очистка строки (строка становится снова нулевой длины)
void CMyString::Clear()
{
	m_pString.reset(nullptr);
	m_length = 0;
}

CMyString& CMyString::operator=(const CMyString& mystr)
{
	if (this != &mystr)
	{
		Clear();
		m_length = mystr.m_length;
		m_pString = std::make_unique<char[]>(m_length + 1);
		for (size_t i = 0; i <= m_length; ++i)
		{
			m_pString[i] = mystr.m_pString[i];
		}
	}
	return *this;
}

CMyString CMyString::operator+(const CMyString& mystr) const
{
	size_t length = m_length + mystr.m_length;
	auto newPlace = std::make_unique<char[]>(length + 1);
	for (size_t i = 0; i < m_length; ++i)
	{
		newPlace[i] = m_pString[i];
	}
	for (size_t i = 0; i < mystr.m_length; ++i)
	{
		newPlace[m_length + i] = mystr.GetStringData()[i];
	}
	newPlace[length] = '\0';
	return CMyString(newPlace.get(), length);
}

CMyString CMyString::operator+(const char* cstr) const
{
	return *this + CMyString(cstr);
}

CMyString CMyString::operator+(const std::string& stlstr) const
{
	return *this + CMyString(stlstr);
}

CMyString& CMyString::operator+=(const CMyString& mystr)
{
	auto newPlace = std::make_unique<char[]>(m_length + mystr.m_length + 1);
	for (size_t i = 0; i < m_length; ++i)
	{
		newPlace[i] = m_pString[i];
	}
	for (size_t i = 0; i < mystr.m_length; ++i)
	{
		newPlace[m_length + i] = mystr.GetStringData()[i];
	}
	m_length += mystr.m_length;
	newPlace[m_length] = '\0';
	m_pString = std::move(newPlace);
	return *this;
}

bool operator==(const CMyString& mystr1, const CMyString& mystr2)
{
	bool result = true;
	if (mystr1.m_length == mystr2.m_length)
	{
		for (size_t i = 0; i < mystr1.m_length; ++i)
		{
			if (mystr1.m_pString[i] != mystr2.m_pString[i])
			{
				result = false;
				break;
			}
		}
	}
	else
	{
		result = false;
	}
	return result;
}

bool operator!=(const CMyString& mystr1, const CMyString& mystr2)
{
	return !(mystr1 == mystr2);
}

bool operator<(const CMyString& mystr1, const CMyString& mystr2)
{
	size_t i;
	for (i = 0; (i < mystr1.m_length) && (i < mystr2.m_length); ++i)
	{
		if (mystr1.m_pString[i] < mystr2.m_pString[i])
		{
			return true;
		}
		if (mystr1.m_pString[i] > mystr2.m_pString[i])
		{
			return false;
	    }
	}
	return (i == mystr1.m_length) && (i < mystr2.m_length);
}

bool operator>(const CMyString& mystr1, const CMyString& mystr2)
{
	return (mystr1 >= mystr2) && (mystr1 != mystr2);
}

bool operator<=(const CMyString& mystr1, const CMyString& mystr2)
{
	return (mystr1 < mystr2) || (mystr1 == mystr2);
}

bool operator>=(const CMyString& mystr1, const CMyString& mystr2)
{
	return !(mystr1 < mystr2);
}

char& CMyString::operator[](const size_t index)
{
	if (index < m_length)
	{
		return m_pString[index];
	}
	else
	{
		throw std::out_of_range("Index is out of range");
	}
}


const char CMyString::operator[](const size_t index) const
{
	if (index < m_length)
	{
		return m_pString[index];
	}
	else
	{
		throw std::out_of_range("Index is out of range");
	}
}

std::ostream& operator<<(std::ostream& os, const CMyString& mystr)
{
	for (size_t i = 0; (i < mystr.m_length) && (os.good()); ++i)
	{
		os.put(mystr.m_pString[i]);
	}
	return os;
}

std::istream& operator>>(std::istream& is, CMyString& mystr) // временная версия
{
	const size_t BUF_SIZE = 256; 
	mystr = CMyString();
	char part[BUF_SIZE];
	while (is.good())
	{
		is.get(part, BUF_SIZE, '\0');
		mystr += CMyString(part);
	}
	is.clear();
	return is;
}

CMystrIterator CMyString::begin() const
{
	return CMystrIterator(m_pString.get());
}

CMystrIterator CMyString::end() const
{
	return CMystrIterator(m_pString.get() + m_length);
}

CMystrConstIterator CMyString::cbegin() const
{
	return CMystrIterator(m_pString.get());
}

CMystrConstIterator CMyString::cend() const
{
	return CMystrIterator(m_pString.get() + m_length);
}