// lab031c.cpp: определяет точку входа для консольного приложения.
//

#include "stdafx.h"
#include "CCar.h"

enum OperaType
{
	NotOperation = 0,
	Exit,
	Info,
	EngOn,
	EngOff,
	SetGear,
	SetSpeed
};

struct CarOperation
{
	OperaType operaType; // действия при вождении машины
	int numeric; // числовой показатель для значения номера передачи, для значения скорости
};

static const std::vector<std::string> CommandPrefixes = { std::string("Exit"), std::string("Info"), std::string("EngineOn"), std::string("EngineOff"), std::string("SetGear"), std::string("SetSpeed") };

void PrintCarState(CCar aCar)
{
	std::cout << "Engine: " << aCar.GetEngineState() << "  ";
	std::cout << "Moving direction: " << static_cast<int>(aCar.GetMovingDirection()) << "  ";
	std::cout << "Gear mode: " << aCar.GetGearNum() << "  ";
	std::cout << "Speed: " << aCar.GetSpeedValue() << std::endl;
}

void PrintHelp()
{
	std::cout << "Drive the car. Enter \"EngineOn\" to turn on the engine," << std::endl;
	std::cout << "\"EngineOff\" to turn off the engine." << std::endl;
	std::cout << "Enter \"SetGear 2\" to use 2nd gear (-1 is reverse, 0 is neutral)." << std::endl;
	std::cout << "Enter \"SetSpeed 100\" to try reach speed of 100." << std::endl;
	std::cout << "Enter \"Info\" to see car parameters state" << std::endl;
	std::cout << "Enter \"Exit\" to finish driving." << std::endl;
}

int IntFromString(const std::string& str) // защищенное чтение числового параметра
{
	const char* cstr = str.c_str();
	if (cstr[0] == '-')
		return -1; // корректный отрицательный параметр -- это обязательно номер передачи -1
	return (isdigit(cstr[0])) ? stoi(str) : 0;
}

CarOperation ReadOperation(std::string const& Phrase)
{
	CarOperation result = { NotOperation, 0 };
	std::stringstream inputLine(Phrase);
	std::string partOfPhrase;
	inputLine >> partOfPhrase;

	auto it = std::find(CommandPrefixes.begin(), CommandPrefixes.end(), partOfPhrase);
	if (it == CommandPrefixes.end())
	{
		return result;
	}

	if (*it == "Exit")
	{
		result.operaType = Exit;
	}
	if (*it == "Info")
	{
		result.operaType = Info;
	}
	if (*it == "EngineOn")
	{
		result.operaType = EngOn;
	}
	if (*it == "EngineOff")
	{
		result.operaType = EngOff;
	}
	if ((*it == "SetGear") || (*it == "SetSpeed"))
	{
		inputLine >> partOfPhrase;
		int numData = IntFromString(partOfPhrase);
		result.operaType = (*it == "SetGear") ? SetGear : SetSpeed;
		result.numeric = numData;
	}
	return result;
}

bool DriveCar(const CarOperation& operation, CCar& car)
{
	bool keepOn = true;
	switch (operation.operaType)
	{
	case Exit:
		keepOn = false;
		break;
	case Info:
		PrintCarState(car);
		break;
	case EngOn:
		if (!car.TurnOnEngine())
			std::cout << car.GetErrorMessage() << std::endl;
		break;
	case EngOff:
		if (!car.TurnOffEngine())
			std::cout << car.GetErrorMessage() << std::endl;
		break;
	case SetGear:
		if (!car.SetGear(operation.numeric))
			std::cout << car.GetErrorMessage() << std::endl;
		break;
	case SetSpeed:
		if (!car.SetSpeed(operation.numeric))
			std::cout << car.GetErrorMessage() << std::endl;
		break;
	default:
		PrintHelp();
	}
	return keepOn;
}

int main(int argc, char* argv[])
{
	CCar testCar;
	CarOperation driveElem;
	while (DriveCar(driveElem, testCar))
	{
		if (driveElem.operaType != Info)
        {
		    PrintCarState(testCar);
		}
		std::cout << "> ";
		std::string inputPhrase;
		if (getline(std::cin, inputPhrase))
		{
			driveElem = ReadOperation(inputPhrase);
		}
		else
		{
			break;
		}
	}
	std::cout << "Thank you!" << std::endl;

	return 0;
}
