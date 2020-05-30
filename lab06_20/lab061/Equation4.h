#pragma once

#include "stdafx.h"

struct CoeffSeries4
{
	double coeff[5];
	CoeffSeries4(){};
	CoeffSeries4(double a, double b, double c, double d, double e)
	{
		coeff[0] = e;
		coeff[1] = d;
		coeff[2] = c;
		coeff[3] = b;
		coeff[4] = a;
	}
};

struct CoeffSeries2
{
	double coeff[3];
	CoeffSeries2(){};
	CoeffSeries2(double a, double b, double c)
	{
		coeff[0] = c;
		coeff[1] = b;
		coeff[2] = a;
	}
};

struct EquationRoot2
{
	size_t numRoots2;
	double roots2[2];
};

struct EquationRoot4
{
	size_t numRoots;
	double roots[4];
};

bool ApproximatelyEqual(double foo, double bar);
EquationRoot2 SolveQuadric(const CoeffSeries2& quadCoe);
double CubicPolyValue(double x, const CoeffSeries2& qubicMinor);
bool ShrinkBordersToCubicRoot(const CoeffSeries2& cubicMinor, double& leftBorder, double& rightBorder, double& middle);
double MakeBorder(const CoeffSeries2& qubicMinor);
double FindSomeRootOfCubic(const CoeffSeries2& qubicMinor);
void MakeReducedEq4(const CoeffSeries4& fullDegFour, CoeffSeries2& fourDegMinor);
double GetResolventaRoot(const CoeffSeries2& fourDegMinor);
EquationRoot4 SolveBiquadricWithOneRoot(const double onlyRoot);
EquationRoot4 SolveBiquadricWithTwoRoots(EquationRoot2 const& preRoots);
EquationRoot4 SolveBiquadric(const CoeffSeries2& quadCoe);
EquationRoot4 SpecialCaseOfPossiblyOneRoot(double p, double q, double resRoot);
EquationRoot4 SolveDecouplingOnTwoQuadratic(double p, double q, double resRoot);
void SortRoots4(EquationRoot4& roots4);
void DelRepeated(EquationRoot4& roots4);
EquationRoot4 Solve4(const CoeffSeries4& fullDegFour);
void Solve4WithExpns(const CoeffSeries4& fullDegFour);
void PrintRoots(EquationRoot4 const& rootSet);
void SolveMultipleEqns4();
