#include "CMyString.h"


CMyString::CMyString()
	: m_length(1)
	, m_pString( new char[1])
{
	m_pString[0] = '\0';
}

// �����������, ���������������� ������ ������� ������
// � ����������� ������� ��������
CMyString::CMyString(const char* pString)
{

}

// �����������, ���������������� ������ ������� ��
// ����������� ������� �������� �����
CMyString::CMyString(const char* pString, size_t length) 
{
}

// ����������� �����������
CMyString::CMyString(CMyString const& other)
{

}

// ������������ ����������� (��� ������������, ����������� � C++11)
//  ����������� ��������� � ������������ ���������� ������������
CMyString::CMyString(CMyString&& other)
{

}

// �����������, ���������������� ������ ������� ��
// ������ ����������� ���������� C++
CMyString::CMyString(std::string const& stlString)
{

}

// ���������� ������ - ����������� ������, ���������� ��������� ������
CMyString::~CMyString()
{

}

// ���������� ����� ������ (��� ����� ������������ �������� �������)
size_t CMyString::GetLength() const
{
	return m_length;
}

// ���������� ��������� �� ������ �������� ������.
// � ����� ������� ����������� ������ ���� ����������� ������� ������
// ���� ���� ������ ������
const char* CMyString::GetStringData() const
{
	return "";
}

// ���������� ��������� � �������� ������� ������ �� ������ length ��������
CMyString CMyString::SubString(size_t start, size_t length) const
{
	return CMyString();
}

// ������� ������ (������ ���������� ����� ������� �����)
void CMyString::Clear()
{

}
