#include "stdafx.h"
#include "CRational.h"

CRational::CRational()
	: m_numerator(0)
	, m_denominator(1)
{
}

CRational::CRational(int value)
	: m_numerator(value)
	, m_denominator(1)
{
}

CRational& CRational::Normalize()
{
	if (m_numerator == 0)
	{
		m_denominator = 1;
		return *this;
	}
	if (m_denominator < 0)
	{
		m_numerator = -m_numerator;
		m_denominator = -m_denominator;
	}

	int gcdNumDenom = std::gcd(std::abs(m_numerator), std::abs(m_denominator));
	m_numerator /= gcdNumDenom;
	m_denominator /= gcdNumDenom;

	return *this;
}

CRational::CRational(int numerator, int denominator)
{
	if (denominator > 0)
	{
		m_numerator = numerator;
		m_denominator = denominator;
	}
	else if (denominator < 0)
	{
		m_numerator = -numerator;
		m_denominator = -denominator;
	}
	else if (denominator == 0)
	{
		throw std::invalid_argument("Can't create ratio with zero in denominator!");
	}
	Normalize();
}

int CRational::GetNumerator() const
{
	return m_numerator;
}

int CRational::GetDenominator() const
{
	return m_denominator;
}

double CRational::ToDouble() const
{
	return 1.0 * m_numerator / m_denominator;
}

CRational& CRational::operator+=(CRational const& summand)
{
	int oldDenom = m_denominator;
	int summDenom = summand.m_denominator;
	m_denominator = oldDenom * summDenom;
	m_numerator = m_numerator * summDenom + oldDenom * summand.m_numerator;

	return Normalize();
}

CRational& CRational::operator-=(CRational const& subtrahend)
{
	int oldDenom = m_denominator;
	int subtDenom = subtrahend.m_denominator;
	m_denominator = oldDenom * subtDenom;
	m_numerator = m_numerator * subtDenom - oldDenom * subtrahend.m_numerator;

	return Normalize();
}

CRational& CRational::operator*=(CRational const& multiplier)
{
	m_numerator *= multiplier.m_numerator;
	m_denominator *= multiplier.m_denominator;

	return Normalize();
}

CRational& CRational::operator/=(CRational const& divisor)
{
	if (divisor.m_numerator == 0)
	{
		throw std::invalid_argument("Zero division attempt!");
	}
	else
	{
		int newDenom = m_denominator * divisor.m_numerator;
		m_numerator = m_numerator * divisor.m_denominator;
		m_denominator = newDenom;
	}
	return Normalize();
}

CRational operator+(const CRational& ratio)
{
	return ratio;
}

CRational operator-(const CRational& ratio)
{
	return CRational(-ratio.GetNumerator(), ratio.GetDenominator());
}

CRational operator+(CRational summand1, CRational summand2)
{
	return summand1 += summand2;
}

CRational operator-(CRational minuend, CRational subtrahend)
{
	return minuend -= subtrahend;
}

CRational operator*(CRational multiplier1, CRational multiplier2)
{
	return multiplier1 *= multiplier2;
}

CRational operator/(CRational dividend, CRational divisor)
{
	return dividend /= divisor;
}

bool operator==(CRational left, CRational right)
{
	return ((left.GetNumerator() == right.GetNumerator()) && (left.GetDenominator() == right.GetDenominator()));
}

bool operator!=(CRational left, CRational right)
{
	return !(left == right);
}

bool operator>(CRational left, CRational right)
{
	return (left.GetNumerator() * right.GetDenominator() > left.GetDenominator() * right.GetNumerator());
}

bool operator<(CRational left, CRational right)
{
	return (right > left);
}

bool operator>=(CRational left, CRational right)
{
	return !(right > left);
}

bool operator<=(CRational left, CRational right)
{
	return !(left > right);
}

std::ostream& operator<<(std::ostream& ostrm, CRational const& ratio)
{
	ostrm << ratio.GetNumerator();
	if (ratio.GetDenominator() != 1)
	{
		ostrm << "/" << ratio.GetDenominator();
	}
	return ostrm;
}

std::istream& operator>>(std::istream& istrm, CRational& ratio)
{
	int numerator = 0;
	int denominator = 1;
	if (istrm >> numerator)
	{
		if ((istrm.get() == '/') && (istrm >> denominator))
        {
		     ratio = CRational(numerator, denominator);
		}
		else
		{
			ratio = CRational(numerator, 1);
		}
	}
	return istrm;
}

/*
CRational& CRational::operator+=(CRational summand)
{
m_numerator = m_numerator * summand.m_denominator + m_denominator * summand.m_numerator;
m_denominator = m_denominator * summand.m_denominator;
return Normalize();
}

CRational& CRational::operator-=(CRational subtrahend)
{
m_numerator = m_numerator * subtrahend.m_denominator - m_denominator * subtrahend.m_numerator;
m_denominator = m_denominator * subtrahend.m_denominator;
return Normalize();
}

CRational& CRational::operator*=(CRational multiplier)
{
m_numerator *= multiplier.m_numerator;
m_denominator *= multiplier.m_denominator;
return Normalize();
}

CRational& CRational::operator/=(CRational divisor)
{
if (divisor.m_numerator == 0)
{
throw std::invalid_argument("Zero division attempt!");
}
else
{
m_numerator = m_numerator * divisor.m_denominator;
m_denominator = m_denominator * divisor.m_numerator;
}
return Normalize();
}
*/
