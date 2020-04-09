#pragma once
// ���������� ��� �������������� �������� (�-�, �� �������)

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

	bool Contains(int value) const; // value � ���������
	bool Below(int value) const;	// �������� ���� ���� value 
	bool Over(int value) const;		// �������� ���� ���� value

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

	CCar(const CGearKit& gearKit); // ����������� � �������� ���

	CGearKit GetGearKit() const; // �������� ��������� ���

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

	bool m_engineOn; // ��������� �������
	Direction m_direction; // ����������� ��������
	DriveError m_error; // ������ ���������� �������
	std::string m_errorMess; // c�������� �� ������
	CGearKit m_gearKit; // ���������� ����� �� ��������� min � max �������� �� �������� �� -1 �� ���������)
	int m_speed; // ��������
	int m_gear;  // �������� (������ -1, �������� 0, �������� ������ 1..n)
};

