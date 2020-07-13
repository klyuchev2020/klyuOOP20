#pragma once
#include "stdafx.h"

class CMystrIterator
{
public:
	typedef std::random_access_iterator_tag iterator_category;
	
	explicit CMystrIterator(char* pChar);

	char& operator*() const;
	CMystrIterator& operator++();
	CMystrIterator operator++(int);
	CMystrIterator& operator--();
	CMystrIterator operator--(int);
	CMystrIterator& operator+=(int n);
	CMystrIterator& operator-=(int n);
	CMystrIterator operator+(int n) const;

	bool operator!=(const CMystrIterator& otherIt) const;
	bool operator==(const CMystrIterator& otherIt) const;

	friend class CMystrConstIterator;

private:
	char* m_pChar = nullptr;
};

CMystrIterator operator+(int n, const CMystrIterator& mystrIt);

class CMystrConstIterator
{
public:
	typedef std::random_access_iterator_tag iterator_category;
	
	explicit CMystrConstIterator(const char* cpChar);
	CMystrConstIterator(const CMystrIterator& mystrIt);
	const char& operator*() const;
	CMystrConstIterator& operator++();
	CMystrConstIterator operator++(int);
	CMystrConstIterator& operator--();
	CMystrConstIterator operator--(int);
	CMystrConstIterator& operator+=(int n);
	CMystrConstIterator& operator-=(int n);
	CMystrConstIterator operator+(int n) const;
	
	bool operator!=(const CMystrConstIterator& otherIt) const;
	bool operator==(const CMystrConstIterator& otherIt) const;

private:
	const char* m_pChar = nullptr;
};

CMystrConstIterator operator+(int n, const CMystrConstIterator& mystrCIt);
