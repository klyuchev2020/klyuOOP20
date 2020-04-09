#pragma once
// автомобиль для прямолинейного движения (н-р, по рельсам)

enum class Direction
{
	Backward = -1, Stop, Forward
};

enum class DriveError
{
	NoError, GearOutOfRange, TurningOnPresentGear, GearOnStanding, UnpossibleReverse,
	IllGearOnBackwardMoving, TooSlowForNewGear, TooFastForNewGear, NegativeSpeed, AccelerOnNeutralAttempt,
	TooSlowForPresentGear, TooFastForPresentGear
};

class CSpeedRange
{
public:
	CSpeedRange();
	CSpeedRange(int lower, int upper);
	
	int GetUpper() const;
	int GetLower() const;

	bool Contains(int value) const; // value в диапазоне
	bool Below(int value) const;	// диапазон весь ниже value 
	bool Over(int value) const;		// диапазон всеь выше value

private:
	int m_lower;
	int m_upper;
};

class CGearKit
{
public:
	CGearKit();
	CGearKit(const CGearKit& givenKit);
	CGearKit(const CSpeedRange& revRange, const int forNumber, const std::vector<CSpeedRange>& forRange);

	int GetForwardNumber() const;
	CSpeedRange GetReverseDiapazon() const;
	CSpeedRange GetForwardDiapazon(const int gear) const;

	bool GearNotExists(const int gear) const;
	bool TooFast(const int gear, const int velocity) const;
	bool TooSlow(const int gear, const int velocity) const;
	bool AppropVelocity(const int gear, const int velocity) const;

private:
	int m_forwardNumber;
	CSpeedRange m_reverseRange;
	CSpeedRange m_neutralRange;
	std::vector<CSpeedRange> m_forwardRange;
};

class CCar
{
public:

	CCar();

	CCar(const CGearKit& gearKit); // конструктор с заданной КПП

	CGearKit GetGearKit() const; // получить параметры КПП

	bool GetEngineState() const;

	Direction GetMovingDirection() const;

	int GetGearNum() const;

	int GetSpeedValue() const;

	std::string GetErrorMessage() const;

	bool TurnOnEngine();

	bool TurnOffEngine();

	bool SetGear(int gear);

	bool SetSpeed(int speed);



private:

	bool m_engineOn; // двигатель включен
	Direction m_direction; // направление движения
	DriveError m_error; // ошибка управления машиной
	std::string m_errorMess; // cообщение об ошибке
	CGearKit m_gearKit; // скоростной режим на передачах min и max скорость на передаче от -1 до наивысшей)
	int m_speed; // скорость
	int m_gear;  // передача (реверс -1, нейтраль 0, движение вперед 1..n)
};

