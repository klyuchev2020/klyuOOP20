// lab031cCatchTests.cpp: определяет точку входа для консольного приложения.
//

#include "stdafx.h"
#include "../lab031/CCar.h"


void PrintCarState(const CCar& aCar)
{
	std::cout << "Engine: " << aCar.GetEngineState() << "  ";
	std::cout << "Moving direction: " << (int)aCar.GetMovingDirection() << "  ";
	std::cout << "Gear mode: " << aCar.GetGearNum() << "  ";
	std::cout << "Speed: " << aCar.GetSpeedValue() << std::endl;
}

TEST_CASE("Turning the engine on and off")
{
	CCar Zhiguli;
	CHECK(Zhiguli.TurnOnEngine() == true);
	CHECK(Zhiguli.TurnOnEngine() == false); // пытаемся выключить работающий двигатель
	CHECK(Zhiguli.TurnOffEngine() == true);
	CHECK(Zhiguli.TurnOffEngine() == false); // пытаемся выключить неработающий двигатель
	std::cout << "Test on engine turning on/off is Ok" << std::endl;
}

TEST_CASE("Changing gear on stop when engine off: only neutral allowed; can choose -1, 0, 1 gear on stop but others")
{

	CCar Zhiguli;
	GIVEN("Engine turned off")
	{
		PrintCarState(Zhiguli);
		CHECK(Zhiguli.SetGear(-1) == false); // двигатель не включен -> нельзя включить реверс
		PrintCarState(Zhiguli);
		CHECK(Zhiguli.SetGear(0) == true); // при выключенном двигателе передача и так нейтральная
		PrintCarState(Zhiguli);
	}
	CHECK(Zhiguli.TurnOnEngine() == true); // включаем выключенный двигатель
	PrintCarState(Zhiguli);
	CHECK(Zhiguli.SetGear(-1) == true); // можно стоя на месте включить реверс
	PrintCarState(Zhiguli);
	CHECK(Zhiguli.SetGear(1) == true); // а можно стоя с реверса на первую
	PrintCarState(Zhiguli);
	CHECK(Zhiguli.SetGear(2) == false); // а на вторую нельзя
	PrintCarState(Zhiguli);
	CHECK(Zhiguli.SetGear(0) == true); // на нейтраль, чтобы затем выключить
	PrintCarState(Zhiguli);
	CHECK(Zhiguli.TurnOffEngine() == true); // выключаем двигатель
	PrintCarState(Zhiguli);
	std::cout << "Test on gear handling on stop is Ok" << std::endl;
}

TEST_CASE("Test on well forward moving")
{
	CCar Zhiguli;
	CHECK(Zhiguli.TurnOnEngine() == true); // включаем двигатель
	PrintCarState(Zhiguli);
	CHECK(Zhiguli.SetGear(1) == true); // 1-я передача
	PrintCarState(Zhiguli);
	CHECK(Zhiguli.SetSpeed(100) == false);
	CHECK(Zhiguli.GetSpeedValue() == 30); // слишком большая скорость
	PrintCarState(Zhiguli);
	CHECK(Zhiguli.SetSpeed(20) == true); // а такая скорость годится
	PrintCarState(Zhiguli);
	CHECK(Zhiguli.SetGear(2) == true); // 2-я передача
	PrintCarState(Zhiguli);
	CHECK(Zhiguli.SetSpeed(50) == true); // такая скорость годится
	PrintCarState(Zhiguli);
	CHECK(Zhiguli.SetGear(4) == true); // 2-я передача
	PrintCarState(Zhiguli);
	CHECK(Zhiguli.SetSpeed(80) == true); // такая скорость годится
	PrintCarState(Zhiguli);
	CHECK(Zhiguli.SetGear(5) == true); // 2-я передача
	PrintCarState(Zhiguli);
	CHECK(Zhiguli.SetSpeed(200) == false); // такая скорость недоступна машине
	CHECK(Zhiguli.GetSpeedValue() == 150);
	PrintCarState(Zhiguli);
	CHECK(Zhiguli.SetSpeed(140) == true); // такая скорость годится
	PrintCarState(Zhiguli);
	CHECK(Zhiguli.SetSpeed(90) == true); // замедляемся
	PrintCarState(Zhiguli);
	CHECK(Zhiguli.SetGear(4) == true); // понижаем передачу
	PrintCarState(Zhiguli);
	CHECK(Zhiguli.SetSpeed(60) == true); // замедляемся
	PrintCarState(Zhiguli);
	CHECK(Zhiguli.SetGear(3) == true); // понижаем передачу
	PrintCarState(Zhiguli);
	CHECK(Zhiguli.SetSpeed(20) == false); // пытаемся замедлиться сверх возможного
	CHECK(Zhiguli.GetSpeedValue() == 30);
	PrintCarState(Zhiguli);
	CHECK(Zhiguli.SetSpeed(30) == true); // замедляемся
	PrintCarState(Zhiguli);
	CHECK(Zhiguli.SetGear(1) == true); // понижаем передачу до 1-ой
	PrintCarState(Zhiguli);
	CHECK(Zhiguli.SetSpeed(0) == true); // остановились
	PrintCarState(Zhiguli);
	CHECK(Zhiguli.TurnOffEngine() == false); // выключили двигатель, безуспешно -- нужна нейтраль
	PrintCarState(Zhiguli);
	CHECK(Zhiguli.SetGear(0) == true); // нейтраль
	PrintCarState(Zhiguli);
	CHECK(Zhiguli.TurnOffEngine() == true); // выключили двигатель, успешно
	PrintCarState(Zhiguli);
	std::cout << "Test on moving forward is Ok" << std::endl;
}

TEST_CASE("Test with reverse moving")
{
	CCar Zhiguli;
	CHECK(Zhiguli.TurnOnEngine() == true); // включаем двигатель
	PrintCarState(Zhiguli);
	CHECK(Zhiguli.SetGear(1) == true); // первая передача, стоим на месте
	CHECK(Zhiguli.GetMovingDirection() == Direction::Stop);
	PrintCarState(Zhiguli);
	CHECK(Zhiguli.SetSpeed(10) == true); // первая передача, едем вперед 10
	CHECK(Zhiguli.GetMovingDirection() == Direction::Forward);
	PrintCarState(Zhiguli);
	CHECK(Zhiguli.SetGear(-1) == false); // переключаемся на реверс -- безуспешно
	PrintCarState(Zhiguli);
	CHECK(Zhiguli.SetGear(0) == true); // переключаемся на нейтраль, но едем вперед
	CHECK(Zhiguli.GetMovingDirection() == Direction::Forward);
	PrintCarState(Zhiguli);
	CHECK(Zhiguli.SetGear(-1) == false); // переключаемся на реверс -- безуспешно
	PrintCarState(Zhiguli);
	CHECK(Zhiguli.SetSpeed(0) == true); // останавливаемся на нейтрали
	PrintCarState(Zhiguli);
	CHECK(Zhiguli.SetGear(1) == true); // первая передача, стоим на месте
	PrintCarState(Zhiguli);
	CHECK(Zhiguli.SetGear(-1) == true); // переключаемся на реверс, стоя на месте
	CHECK(Zhiguli.GetMovingDirection() == Direction::Stop);
	PrintCarState(Zhiguli);
	CHECK(Zhiguli.SetSpeed(15) == true); // едем назад 15
	CHECK(Zhiguli.GetMovingDirection() == Direction::Backward);
	PrintCarState(Zhiguli);
	CHECK(Zhiguli.SetGear(1) == false); // переключаемся на первую -- безуспешно
	PrintCarState(Zhiguli);
	CHECK(Zhiguli.SetGear(0) == true); // переключаемся на нейтраль, едем назад
	PrintCarState(Zhiguli);
	CHECK(Zhiguli.SetGear(1) == false); // переключаемся на первую -- безуспешно
	PrintCarState(Zhiguli);
	CHECK(Zhiguli.SetSpeed(12) == true);
	CHECK(Zhiguli.GetMovingDirection() == Direction::Backward);
	PrintCarState(Zhiguli);
	CHECK(Zhiguli.SetSpeed(0) == true); // останавливаемся
	CHECK(Zhiguli.GetMovingDirection() == Direction::Stop);
	PrintCarState(Zhiguli);
	CHECK(Zhiguli.SetGear(1) == true); // переключаемся на первую
	PrintCarState(Zhiguli);
	CHECK(Zhiguli.SetSpeed(20) == true); // 20 вперед
	CHECK(Zhiguli.GetMovingDirection() == Direction::Forward);
	PrintCarState(Zhiguli);
	CHECK(Zhiguli.SetGear(0) == true); // переключаемся на нейтраль, едем вперед
	PrintCarState(Zhiguli);
	CHECK(Zhiguli.SetGear(3) == false); // слишком высокая передача для данной скорости 20
	PrintCarState(Zhiguli);
	CHECK(Zhiguli.SetSpeed(0) == true); // останавливаемся
	PrintCarState(Zhiguli);
	CHECK(Zhiguli.TurnOffEngine() == true); // выключаем двигатель
	PrintCarState(Zhiguli);
	std::cout << "Test on moving with reverse is Ok" << std::endl;
}
