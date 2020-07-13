#pragma once

#include "stdafx.h"
#include "CMystrIterator.h"


class CMyString
{
public:
	// ����������� �� ���������
	CMyString();

	// �����������, ���������������� ������ ������� ������
	// � ����������� ������� ��������
	explicit CMyString(const char* pString);

	// �����������, ���������������� ������ ������� ��
	// ����������� ������� �������� �����
	CMyString(const char* pString, size_t length);

	// ����������� �����������
	CMyString(CMyString const& other);

	// ������������ ����������� (��� ������������, ����������� � C++11)
	//  ����������� ��������� � ������������ ���������� ������������
	CMyString(CMyString&& other);
	CMyString& operator=(CMyString&& other);

	// �����������, ���������������� ������ ������� ��
	// ������ ����������� ���������� C++
	explicit CMyString(std::string const& stlString);

	// ���������� ������ - ����������� ������, ���������� ��������� ������
	~CMyString();

	// ���������� ����� ������ (��� ����� ������������ �������� �������)
	size_t GetLength() const;

	// ���������� ��������� �� ������ �������� ������.
	// � ����� ������� ����������� ������ ���� ����������� ������� ������
	// ���� ���� ������ ������
	const char* GetStringData() const;

	// ���������� ��������� � �������� ������� ������ �� ������ length ��������
	CMyString SubString(size_t start, size_t length = SIZE_MAX) const;

	// ������� ������ (������ ���������� ����� ������� �����)
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
