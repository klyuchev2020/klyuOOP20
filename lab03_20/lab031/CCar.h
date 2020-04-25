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
	CGearKit(const CSpeedRange& revRange, const std::vector<CSpeedRange>& forRanges);

	int GetForwardGearsNumber() const;
	CSpeedRange GetReverseRange() const;
	CSpeedRange GetForwardRange(const int gear) const;
	
	bool CorrectGearNumber(const int gear) const;
	bool TooFast(const int gear, const int velocity) const;
	bool TooSlow(const int gear, const int velocity) const;
	bool AppropVelocity(const int gear, const int velocity) const;

private:
	CSpeedRange m_reverseRange;
	CSpeedRange m_neutralRange;
	std::vector<CSpeedRange> m_forwardRanges;
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

	bool AbleToSetForwardGear(const int);

	bool AbleToSetReverseGear();

	bool SetGear(const int gear);

	bool SetSpeed(int speed);



private:

	bool m_engineOn; // ��������� �������
	Direction m_direction; // ����������� ��������
	DriveError m_error; // ������ ���������� �������
	std::string m_errorMess; // c�������� �� ������
	CGearKit m_gearKit; // ���������� ����� �� ��������� min � max �������� �� �������� �� -1 �� ���������)
	int m_speed; // ��������
	int m_gear;  // �������� (������ -1, �������� 0, �������� ������ 1..n)
	void RenewDirection();
};

