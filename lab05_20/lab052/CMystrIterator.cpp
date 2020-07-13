#include "CMystrIterator.h"

CMystrIterator::CMystrIterator(char* pChar)
	: m_pChar(pChar)
{
}

/*
CMystrIterator::CMystrIterator(const CMyString& mystr)
	: m_pChar(mystr.Begin())
{
}
*/

char& CMystrIterator::operator*() const
{
	return *m_pChar;
}

CMystrIterator& CMystrIterator::operator++()
{
	++m_pChar;
	return *this;
}

CMystrIterator CMystrIterator::operator++(int)
{
	CMystrIterator temp(*this);
	m_pChar++;
	return temp;
}

CMystrIterator& CMystrIterator::operator--()
{
	--m_pChar;
	return *this;
}

CMystrIterator CMystrIterator::operator--(int)
{
	CMystrIterator temp(*this);
	m_pChar--;
	return temp;
}

CMystrIterator& CMystrIterator::operator+=(int n)
{
	m_pChar += n;
	return *this;
}

CMystrIterator& CMystrIterator::operator-=(int n)
{
	m_pChar -= n;
	return *this;
}

CMystrIterator CMystrIterator::operator+(int n) const
{
	CMystrIterator temp = *this;
	return temp += n;
}


bool CMystrIterator::operator!=(const CMystrIterator& otherIt) const
{
	return m_pChar != otherIt.m_pChar;
}

bool CMystrIterator::operator==(const CMystrIterator& otherIt) const
{
	return !(*this != otherIt);
}

CMystrConstIterator::CMystrConstIterator(const char* cpChar)
	: m_pChar(cpChar)
{
}


CMystrConstIterator::CMystrConstIterator(const CMystrIterator& mystrIt)
	: m_pChar(static_cast<const char*>(mystrIt.m_pChar))
{
}

const char& CMystrConstIterator::operator*() const
{
	return *m_pChar;
}

CMystrConstIterator& CMystrConstIterator::operator++()
{
	++m_pChar;
	return *this;
}

CMystrConstIterator CMystrConstIterator::operator++(int)
{
	CMystrConstIterator temp(*this);
	m_pChar++;
	return temp;
}

CMystrConstIterator& CMystrConstIterator::operator--()
{
	--m_pChar;
	return *this;
}

CMystrConstIterator CMystrConstIterator::operator--(int)
{
	CMystrConstIterator temp(*this);
	m_pChar--;
	return temp;
}

CMystrConstIterator& CMystrConstIterator::operator+=(int n)
{
	m_pChar += n;
	return *this;
}

CMystrConstIterator& CMystrConstIterator::operator-=(int n)
{
	m_pChar -= n;
	return *this;
}

CMystrConstIterator CMystrConstIterator::operator+(int n) const
{
	CMystrConstIterator temp = *this;
	return temp += n;
}

bool CMystrConstIterator::operator!=(const CMystrConstIterator& otherIt) const
{
	return m_pChar != otherIt.m_pChar;
}

bool CMystrConstIterator::operator==(const CMystrConstIterator& otherIt) const
{
	return !(*this != otherIt);
}

CMystrIterator operator+(int n, const CMystrIterator& mystrIt)
{
	return mystrIt + n;
}

CMystrConstIterator operator+(int n, const CMystrConstIterator& mystrCIt)
{
	return mystrCIt + n;
}

