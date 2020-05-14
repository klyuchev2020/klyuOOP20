#pragma once

class CRational
{
public:
	CRational();
	CRational(int value);
	CRational(int numeretor, int denominator);

	int GetNumerator() const;
	int GetDenominator() const;

	CRational& operator+=(CRational const& summand);
	CRational& operator-=(CRational const& subtrahend);
	CRational& operator*=(CRational const& multiplier);
	CRational& operator/=(CRational const& divisor);

	//CRational& operator+=(CRational summand); такая сигнатура была раньше

	double ToDouble() const;

private:
	int m_numerator;
	int m_denominator;
	CRational& Normalize();
};

CRational operator+(const CRational& ratio);
CRational operator-(const CRational& ratio);
CRational operator+(CRational summand1, CRational summand2);
CRational operator-(CRational minuend, CRational subtrahend);
CRational operator*(CRational multiplier1, CRational multiplier2);
CRational operator/(CRational dividend, CRational divisor);

bool operator==(CRational left, CRational right);
bool operator!=(CRational left, CRational right);
bool operator>(CRational left, CRational right);
bool operator<(CRational left, CRational right);
bool operator>=(CRational left, CRational right);
bool operator<=(CRational left, CRational right);

std::ostream& operator<<(std::ostream& ostrm, CRational const& ratio);
std::istream& operator>>(std::istream& istrm, CRational& ratio);
