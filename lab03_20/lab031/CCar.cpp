#include "stdafx.h"
#include "CCar.h"

const std::vector<std::vector<int>> AnAutomobileKit = { { 0, 20 }, { 0, 150 }, { 0, 30 }, { 20, 50 }, { 30, 60 }, { 40, 90 }, { 50, 150 } };

const std::vector<std::vector<int>> OldMoskvichKit = { { 0, 20 }, { 0, 100 }, { 0, 30 }, { 20, 60 }, { 40, 100 } };

// класс диапазон скоростей

CSpeedRange::CSpeedRange(int lower, int upper)
{
	assert(lower >= 0 && lower <= upper);
	m_lower = lower;
	m_upper = upper;
}

int CSpeedRange::GetUpper() const
{
	return m_upper;
}

int CSpeedRange::GetLower() const
{
	return m_lower;
}

bool CSpeedRange::Below(int value) const
{
	return (value > m_upper);
}

bool CSpeedRange::Over(int value) const
{
	return (value < m_lower);
}

bool CSpeedRange::Contains(int value) const
{
	return (!Below(value) && !Over(value));
}

// класс коробка передач

CGearKit::CGearKit()
	: m_reverseRange(CSpeedRange::CSpeedRange(0, 20))
	, m_neutralRange(CSpeedRange::CSpeedRange(0, 150))
	, m_forwardRanges({ { 0, 30 }, { 20, 50 }, { 30, 60 }, { 40, 90 }, { 50, 150 } })
{
}

int GetMaxForwardSpeed(const std::vector<CSpeedRange>& forwardRanges)
{
	return forwardRanges.back().GetUpper();
}

int GetMaxSpeed(const CSpeedRange& reverseRange, const std::vector<CSpeedRange>& forwardRanges)
{
	return std::max(GetMaxForwardSpeed(forwardRanges), reverseRange.GetUpper());
}

bool IntersectsProperly(const CSpeedRange& rangeLeft, const CSpeedRange& rangeRight)
{
	return rangeLeft.Contains(rangeRight.GetLower()) && rangeRight.Contains(rangeLeft.GetUpper());
}

bool ValidForwardRanges(const std::vector<CSpeedRange>& forwardRanges)
{
	bool valid = true;
	for (size_t i = 0; i + 1 < forwardRanges.size(); ++i)
	{
		if (!IntersectsProperly(forwardRanges[i], forwardRanges[i + 1]))
		{
			valid = false;
			break;
		}
	}
	return valid;
}

CGearKit::CGearKit(const CSpeedRange& reverseRange, const std::vector<CSpeedRange>& forwardRanges)
	: m_reverseRange(CSpeedRange::CSpeedRange(0, 20))
	, m_neutralRange(CSpeedRange::CSpeedRange(0, 150))
	, m_forwardRanges({ { 0, 30 }, { 20, 50 }, { 30, 60 }, { 40, 90 }, { 50, 150 } })
{ //
	if (ValidForwardRanges(forwardRanges))
	{
		CSpeedRange m_reverseRange(reverseRange);
		CSpeedRange m_neutralRange(0, GetMaxSpeed(reverseRange, forwardRanges));
		m_forwardRanges = forwardRanges;
	}
}

int CGearKit::GetForwardGearsNumber() const
{
	return int(m_forwardRanges.size());
}

CSpeedRange CGearKit::GetReverseRange() const
{
	return m_reverseRange;
}

CSpeedRange CGearKit::GetForwardRange(const int gear) const
{
	return m_forwardRanges[gear - 1];
}

bool CGearKit::CorrectGearNumber(const int gear) const
{
	return ((gear >= -1) && (gear <= GetForwardGearsNumber()));
}

bool CGearKit::TooFast(const int gear, const int velocity) const
{
	if (gear == -1)
	{
		return m_reverseRange.Below(velocity);
	}
	else if (gear > 0)
	{
		return m_forwardRanges[gear - 1].Below(velocity);
	}
	return false;
}

bool CGearKit::TooSlow(const int gear, const int velocity) const
{
	if (gear > 0)
	{
		return m_forwardRanges[gear - 1].Over(velocity);
	}
	return false;
}

bool CGearKit::AppropVelocity(const int gear, const int velocity) const
{
	if (gear == -1)
	{
		return m_reverseRange.Contains(velocity);
	}
	else if (gear > 0)
	{
		return m_forwardRanges[gear - 1].Contains(velocity);
	}
	return false;
}

// класс CCar

CCar::CCar()
	: m_engineOn(false)
	, m_direction(Direction::Stop)
	, m_errorMess("")
	, m_gearKit(CGearKit())
	, m_gear(0)
	, m_speed(0)
{
}

CCar::CCar(const CGearKit& gearKit)
{
	m_engineOn = false;
	m_direction = Direction::Stop;
	m_errorMess = "";
	m_gear = 0;
	m_speed = 0;
	CGearKit m_gearKit(gearKit);
}

CGearKit CCar::GetGearKit() const
{
	return m_gearKit;
}

// получить элементы состояния car

bool CCar::GetEngineState() const
{
	return m_engineOn;
}

Direction CCar::GetMovingDirection() const
{
	return m_direction;
}

int CCar::GetGearNum() const
{
	return m_gear;
}

int CCar::GetSpeedValue() const
{
	return m_speed;
}

std::string CCar::GetErrorMessage() const
{
	return m_errorMess;
}

bool CCar::TurnOnEngine() // включить двигатель; если двигатель включен, возвращает false
{
	m_errorMess.clear();
	if (m_engineOn)
	{
		m_errorMess = "Engine is already works!";
		return false;
	}
	else
	{
		return m_engineOn = true;
	}
}

bool CCar::TurnOffEngine() // выключить двигатель; если двигатель нельзя выключить
{ // (выключен, или передача не нейтральная, или скорость не нулевая), то возвращает false
	m_errorMess.clear();
	if (m_engineOn && m_gear == 0 && m_speed == 0)
	{
		return !(m_engineOn = false);
	}
	else
	{
		m_errorMess = "You can turn engine off only if engine turned on and gear set neutral and car not moving";
		return false;
	}
}

bool CCar::AbleToSetForwardGear(const int gear)
{
	if (!m_engineOn)
	{
		m_errorMess = "You can use only neutral gear then engine is off!";
		return false;
	}
	if (m_direction == Direction::Backward)
	{
		m_errorMess = "The car is moving backward. Do stop before use such the gear!";
		return false;
	}
	if (m_gearKit.TooSlow(gear, m_speed))
	{
		m_errorMess = "Too low speed for moving on " + std::to_string(gear) + " gear!";
		return false;
	}
	if (m_gearKit.TooFast(gear, m_speed))
	{
		m_errorMess = "Too high speed for moving on " + std::to_string(gear) + " gear!";
		return false;
	}

	return true;
}

bool CCar::AbleToSetReverseGear()
{
	if (!m_engineOn)
	{
		m_errorMess = "You can use only neutral gear then engine is off!";
		return false;
	}
	if (m_direction != Direction::Stop)
	{
		m_errorMess = "You must stop before use reverse gear!";
		return false;
	}

	return true;
}

bool CCar::SetGear(const int gear) // включить данную передачу
{
	m_errorMess.clear();

	if (!m_gearKit.CorrectGearNumber(gear))
	{
		m_errorMess = "There only gear modes from -1 to " + std::to_string(m_gearKit.GetForwardGearsNumber()) + " are available!";
		return false;
	}
	if ((gear > 0) && AbleToSetForwardGear(gear) || (gear == -1) && AbleToSetReverseGear() || (gear == 0) || (m_gear == gear))
	{
		m_gear = gear; // если выполнение оказалось здесь -- можно включать передачу
		return true;
	}

	return false;
}

void CCar::RenewDirection()
{
	if (m_speed == 0)
	{
		m_direction = Direction::Stop;
	}
	else if (m_direction == Direction::Stop)
	{
		m_direction = (m_gear == -1) ? Direction::Backward : Direction::Forward;
	}
}

bool CCar::SetSpeed(int speed) // добиться данной скорости
{
	m_errorMess.clear();

	if (speed < 0)
	{
		m_errorMess = "Speed must be nonnegative!";
		return false;
	}
	if ((m_gear == 0) && (speed > m_speed))
	{
		m_errorMess = "To increase the speed use nonneutral gear!";
		return false;
	}
	if ((m_direction == Direction::Backward) && (m_gearKit.TooFast(-1, speed)))
	{
		m_speed = m_gearKit.GetReverseRange().GetUpper();
		m_errorMess = "Too high speed for moving on reverse gear. Speed achieved is "
			+ std::to_string(m_speed);
		return false;
	}
	if (m_gearKit.TooFast(m_gear, speed))
	{
		m_speed = m_gearKit.GetForwardRange(m_gear).GetUpper();
		m_errorMess = "Too high speed for moving on " + std::to_string(m_gear)
			+ " gear. Speed achieved is " + std::to_string(m_speed);
		return false;
	}
	if (m_gearKit.TooSlow(m_gear, speed))
	{
		m_speed = m_gearKit.GetForwardRange(m_gear).GetLower();
		m_errorMess = "Too low speed for moving on " + std::to_string(m_gear)
			+ " gear. Speed achieved is " + std::to_string(m_speed);
		return false;
	}
	m_speed = speed;
	RenewDirection();

	return true;
}
