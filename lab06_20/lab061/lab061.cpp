#include "stdafx.h"
#include "Equation4.h"

static double epsilonApprox = 1e-5;

bool ApproximatelyEqual(double foo, double bar)
{
	return std::abs(foo - bar) < epsilonApprox;
}

EquationRoot2 SolveQuadric(const CoeffSeries2& quadCoe) // для приведенного  x^2 + px + q = 0
{
	EquationRoot2 result;
	result.numRoots2 = 3;
	const double p = (quadCoe.coeff[1] / quadCoe.coeff[2]);
	const double q = (quadCoe.coeff[0] / quadCoe.coeff[2]);
	const double epsilonD = 0.0000000001;
	double Discr = std::pow(p, 2) - 4 * q;
	if (Discr < -epsilonD)
	{
		result.numRoots2 = 0;
	}
	else if (Discr > epsilonD)
	{
		result.numRoots2 = 2;
		result.roots2[0] = (-p - std::pow(Discr, 0.5)) / 2;
		result.roots2[1] = (-p + std::pow(Discr, 0.5)) / 2;
	}
	else
	{
		result.numRoots2 = 1;
		result.roots2[0] = -p / 2;
	}
	return result;
}

double CubicPolyValue(double x, const CoeffSeries2& cubicMinor) // x^3 + px^2 + qx + r; cubicMinor -- младшие коэффициенты p, q, r
{
	return std::pow(x, 3) + cubicMinor.coeff[2] * std::pow(x, 2) + cubicMinor.coeff[1] * x + cubicMinor.coeff[0];
}

bool ShrinkBordersToCubicRoot(const CoeffSeries2& cubicMinor, double& leftBorder, double& rightBorder, double& middle)
{
	double leftBorderValue = CubicPolyValue(leftBorder, cubicMinor);
	double rightBorderValue = CubicPolyValue(rightBorder, cubicMinor);
	double middleValue = CubicPolyValue(middle, cubicMinor);
	double side = leftBorderValue * middleValue;
	if (side == 0) // сравниваем знаки многочлена в середине отрезка и на концах
	{
		return false;
	}
	else if (side > 0)
	{
		leftBorder = middle;
	}
	else
	{
		rightBorder = middle;
	}
	middle = (leftBorder + rightBorder) / 2;
	return true;
}

double MakeBorder(const CoeffSeries2& qubicMinor)
{
	double preBorder = std::max(std::abs(qubicMinor.coeff[2]), std::abs(qubicMinor.coeff[1]));
	preBorder = std::max(preBorder, std::abs(qubicMinor.coeff[0]));
	return 2 * std::max(preBorder, 1.0);
}

double FindSomeRootOfCubic(const CoeffSeries2& qubicMinor) // для нахождения корня кубической резольвенты
{
	const double epsilon = std::numeric_limits<double>::epsilon();
	const double multiplier = 10;

	double preBorder = MakeBorder(qubicMinor);
	double leftBorder = -preBorder; // левая граница для корня
	double rightBorder = preBorder; // правая граница для корня
	double middle = (leftBorder + rightBorder) / 2;
	double difference = rightBorder - leftBorder;

	size_t counter = 0;
	while ((difference > multiplier * epsilon) && (counter < 100))
	{
		if (!ShrinkBordersToCubicRoot(qubicMinor, leftBorder, rightBorder, middle))
			break;
		difference = rightBorder - leftBorder;
	}

	return middle;
}

void MakeReducedEq4(const CoeffSeries4& fullDegFour, CoeffSeries2& fourDegMinor) // старший коэффициент не 0
{
	double b1 = fullDegFour.coeff[3] / fullDegFour.coeff[4];
	double c1 = fullDegFour.coeff[2] / fullDegFour.coeff[4];
	double d1 = fullDegFour.coeff[1] / fullDegFour.coeff[4];
	double e1 = fullDegFour.coeff[0] / fullDegFour.coeff[4];
	fourDegMinor.coeff[2] = c1 - 3 * std::pow(b1, 2) / 8;
	fourDegMinor.coeff[1] = std::pow(b1, 3) / 8 - b1 * c1 / 2 + d1;
	fourDegMinor.coeff[0] = -3 * std::pow(b1, 4) / 256 + std::pow(b1, 2) * c1 / 16 - d1 * b1 / 4 + e1;
}

double GetResolventaRoot(const CoeffSeries2& fourDegMinor)
{
	CoeffSeries2 resolCoe;
	resolCoe.coeff[2] = -fourDegMinor.coeff[2] / 2;
	resolCoe.coeff[1] = -fourDegMinor.coeff[0];
	resolCoe.coeff[0] = fourDegMinor.coeff[0] * fourDegMinor.coeff[2] / 2 - std::pow(fourDegMinor.coeff[1], 2.0) / 8;
	double root = FindSomeRootOfCubic(resolCoe);
	
	return root;
}

EquationRoot4 SolveBiquadricWithOneRoot(const double onlyRoot) // x^4 + px^2 + q -- полный квадрат
{
	EquationRoot4 res;
	res.numRoots = 0;

	if (onlyRoot < 0) 
	{
		throw std::domain_error("Equation has no roots! (from Biquadratic1)");
	}
	else if (onlyRoot == 0.0)
	{
		res.numRoots = 1;
		res.roots[0] = 0.0;
	}
	else
	{
		res.numRoots = 2;
		res.roots[0] = -std::pow(onlyRoot, 0.5);
		res.roots[1] = std::pow(onlyRoot, 0.5);
	}

	return res;
}

EquationRoot4 SolveBiquadricWithTwoRoots(EquationRoot2 const& preRoots) // x^4 + px^2 + q = (x^2 - y1)(x^2 - y2)
{
	EquationRoot4 res;
	res.numRoots = 0;

	double left = preRoots.roots2[0];
	double right = preRoots.roots2[1];
	if (right < 0)
	{
		throw std::domain_error("Equation has no roots! (from Biquadratic2)");
	}
	else if (right == 0.0)
	{
		res.numRoots = 1;
		res.roots[0] = 0.0;
	}
	else
	{
		res.roots[0] = -std::pow(right, 0.5);
		res.roots[1] = std::pow(right, 0.5);
		if (left < 0)
		{
			res.numRoots = 2;
		}
		if (left == 0.0)
		{
			res.numRoots = 3;
			res.roots[2] = 0.0;
		}
		if (left > 0)
		{
			res.numRoots = 4;
			res.roots[2] = -std::pow(left, 0.5);
			res.roots[3] = std::pow(left, 0.5);
		}
	}

	return res;
}

EquationRoot4 SolveBiquadric(const CoeffSeries2& biquadCoe) // приводится к x^4 + px^2 + q = 0
{
	EquationRoot4 result;
	result.numRoots = 0;

	EquationRoot2 biquadric = SolveQuadric(biquadCoe);
	if (biquadric.numRoots2 == 1)
	{
		result = SolveBiquadricWithOneRoot(biquadric.roots2[0]);
	}
	if (biquadric.numRoots2 == 2)
	{
		result = SolveBiquadricWithTwoRoots(biquadric);
	}
	if (result.numRoots == 0)
	{
		throw std::domain_error("Equation has no roots! (from biquadric case)");
	}

	return result;
}

EquationRoot4 SpecialCaseOfPossiblyOneRoot(double p, double q, double resRoot)
{
	EquationRoot4 res;
	res.numRoots = 0;

	const double epsilonSpec = 0.000000001;
	const double probRootCondVal = std::abs(4 * std::pow(2 * resRoot - p, 2) * resRoot - q * q);
	if (probRootCondVal > epsilonSpec)
	{
		throw std::domain_error("Equation has no roots! (from special case)");
	}
	else
	{
		res.numRoots = 1;
		res.roots[0] = q / (4 * resRoot - 2 * p);
	}

	return res;
}

EquationRoot4 SolveDecouplingOnTwoQuadratic(double p, double q, double resRoot)
{
	CoeffSeries2 deq1;
	CoeffSeries2 deq2;
	deq1.coeff[2] = 1.0;
	deq2.coeff[2] = 1.0;
	deq1.coeff[1] = -std::pow(2 * resRoot - p, 0.5);
	deq2.coeff[1] = -deq1.coeff[1];
	deq1.coeff[0] = q / (2 * deq2.coeff[1]) + resRoot;
	deq2.coeff[0] = q / (2 * deq1.coeff[1]) + resRoot;

	EquationRoot2 quadric1 = SolveQuadric(deq1);
	EquationRoot2 quadric2 = SolveQuadric(deq2);

	EquationRoot4 res;
	res.numRoots = 0;
	res.numRoots = quadric1.numRoots2 + quadric2.numRoots2;

	for (size_t i = 0; i < quadric1.numRoots2; ++i)
	{
		res.roots[i] = quadric1.roots2[i];
	}
	for (size_t j = 0; j < quadric2.numRoots2; ++j)
	{
		res.roots[j + quadric1.numRoots2] = quadric2.roots2[j];
	}
	if (res.numRoots == 0)
	{
		throw std::domain_error("Equation has no roots! (from coupling case)");
	}

	return res;
}

void SortRoots4(EquationRoot4& roots4)
{
	std::vector<double> vecRoots;
	if (roots4.numRoots != 0)
	{
		for (size_t i = 0; i < roots4.numRoots; ++i)
			vecRoots.push_back(roots4.roots[i]);
		std::sort(vecRoots.begin(), vecRoots.end());
		for (size_t i = 0; i < roots4.numRoots; ++i)
			roots4.roots[i] = vecRoots[i];
	}
}

void DelRepeated(EquationRoot4& roots4)
{
	SortRoots4(roots4);
	size_t numDistRoots = 0;
	double prev = 0.0;
	if (roots4.numRoots > 1)
	{
		numDistRoots = 1;
		for (size_t i = 1; i < roots4.numRoots; ++i)
		{
			if (ApproximatelyEqual(roots4.roots[i - 1], roots4.roots[i]))
				continue;
			else
			{
				double temp = roots4.roots[i];
				roots4.roots[numDistRoots] = temp;
				numDistRoots++;
			}
		}
		roots4.numRoots = numDistRoots;
	}
}

EquationRoot4 Solve4(const CoeffSeries4& fullDegFour)
{
	EquationRoot4 result;

	if (fullDegFour.coeff[4] == 0)
	{
		throw std::invalid_argument("Leading coefficient must not be equal to zero!");
	}
	else
	{
		CoeffSeries2 fourDegMinor;
		MakeReducedEq4(fullDegFour, fourDegMinor);
		double resRoot = GetResolventaRoot(fourDegMinor);

		double factor = fourDegMinor.coeff[2] - 2 * resRoot;

		if (ApproximatelyEqual(factor, 0.0)) // на деле этот случай жестко ограничивает множество уравнений
		{                                    // Корень резольвенты p/2 обязательно является кратным, поэтому
			CoeffSeries2 biq;                // половинным делением будет найден не он (кроме случая трехкратного корня резольвенты)
			biq.coeff[2] = 1.0;              // То есть, из этого случая получаются только решения для уравнения с четырьмя равными корнями
			biq.coeff[1] = 2 * resRoot;
			biq.coeff[0] = fourDegMinor.coeff[0];
			result = SolveBiquadric(biq);
		}
		else if (factor > 0)
		{
			result = SpecialCaseOfPossiblyOneRoot(fourDegMinor.coeff[2], fourDegMinor.coeff[1], resRoot);
		}
		else
		{
			result = SolveDecouplingOnTwoQuadratic(fourDegMinor.coeff[2], fourDegMinor.coeff[1], resRoot);
		}
		for (size_t n = 0; n < result.numRoots; ++n)
		{
			result.roots[n] -= fullDegFour.coeff[3] / (4 * fullDegFour.coeff[4]);
		}
		DelRepeated(result);
	}
	return result;
}

void PrintRoots(EquationRoot4 const& rootSet)
{
	std::cout << rootSet.numRoots << " distinct roots: " << std::endl;
	for (size_t i = 0; i < rootSet.numRoots; ++i)
	{
		std::cout << std::fixed << std::setprecision(16) << rootSet.roots[i] << std::endl;
	}
}

void Solve4WithExpns(const CoeffSeries4& fullDegFour)
{
	EquationRoot4 result4;
	try
	{
		result4 = Solve4(fullDegFour);
		PrintRoots(result4);
	}
	catch (std::invalid_argument const& e)
	{
		std::cout << "Error: " << e.what() << std::endl;
	}
	catch (std::domain_error const& e)
	{
		std::cout << "Attention! " << e.what() << std::endl;
	}
	catch (...)
	{
		std::cout << "Unknown error!" << std::endl;
	}
}

void SolveMultipleEqns4()
{
	CoeffSeries4 eqn;
	double nextCoeff;
	int cntr = 4;

	std::cout << "Enter coeffs a, b, c, d, e in equation ax^4 + bx^3 + cx^2 + dx + e = 0" << std::endl;
	while (std::cin >> nextCoeff)
	{
		eqn.coeff[cntr--] = nextCoeff;
		if (cntr == -1)
		{
			std::cout << "Equation: " << eqn.coeff[4] << "x^4 + " << eqn.coeff[3] << "x^3 + "
					  << eqn.coeff[2] << "x^2 + " << eqn.coeff[1] << "x + " << eqn.coeff[0] << " = 0" << std::endl;
			Solve4WithExpns(eqn);
			cntr = 4;

			std::cout << "\nEnter coeffs a, b, c, d, e in equation ax^4 + bx^3 + cx^2 + dx + e = 0" << std::endl;
		}
	}
}




