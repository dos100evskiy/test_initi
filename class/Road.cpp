#include "Road.h"

Road::Road() {
	_upperNumOfHuman = rand() % 5;
	_lowerNumOfHuman = rand() % 5;
	int j = rand() % 5;
	for (int i = 0; i < j; ++i)
		_cars.push(new Car(rand() % 10 < 6 ? RIGHT : FORWARD));

	_newHumanChance = 40;
	_newCarChance = 30;
	_percantRotation = 35;

	_constructor();
}

Road::Road(int maxHuman, int maxCar, int percantRotation, int newHumanChance, int newCarChance) {
	_upperNumOfHuman = rand() % (maxHuman + 1);
	_lowerNumOfHuman = rand() % (maxHuman + 1);
	_newCarChance = newCarChance > 100 ? 100 : newCarChance;
	_newHumanChance = _newHumanChance > 100 ? 100 : newHumanChance;
	_percantRotation = percantRotation > 100 ? 100 : percantRotation;

	int j = rand() % (maxCar + 1);
	for (int i = 0; i < j; ++i)
		_cars.push(new Car(rand() % 100 < percantRotation ? RIGHT : FORWARD));

	_constructor();
}

Road::Road(int numOfUpperHuman, int NumOfLowerHuman, int numOfCars, int percantRotation, int newHumanChance, int newCarChance) {
	_upperNumOfHuman = numOfUpperHuman;
	_lowerNumOfHuman = NumOfLowerHuman;
	_newCarChance = newCarChance > 100 ? 100 : newCarChance;
	_newHumanChance = _newHumanChance > 100 ? 100 : newHumanChance;
	_percantRotation = percantRotation > 100 ? 100 : percantRotation;


	for (int i = 0; i < numOfCars; ++i)
		_cars.push(new Car(rand() % 100 < percantRotation  ? RIGHT : FORWARD));

	_constructor();
}

void Road::_constructor() {
	_curSignCar = C_RED;
	_prevSignCar = C_RED;
	_curSignUpperHuman = H_RED;
	_curSignLowerHuman = H_RED;

	_carNeedSwap = false;
	_humanUpperNeedSwap = false;
	_humanLowerNeedSwap = false;
}

bool Road::update() {

	if (rand() % 100 < _newCarChance)
		_cars.push(new Car(rand() % 100 < _percantRotation ? RIGHT : FORWARD));
	
	if (rand() % 100 < _newHumanChance)
		_upperNumOfHuman++;
	if (rand() % 100 < _newHumanChance)
		_lowerNumOfHuman++;

	if (_curSignCar == C_GREEN && !_cars.empty())
		_cars.pop();
	if (_curSignUpperHuman == H_GREEN && _upperNumOfHuman > 0)
		_upperNumOfHuman -= 1;
	if (_curSignLowerHuman == H_GREEN && _lowerNumOfHuman > 0)
		_lowerNumOfHuman -= 1;

	_prevSignCar = _curSignCar;

	if (_carNeedSwap) _swapCarSign();
	if (_humanUpperNeedSwap) _swapUpperHumanSign();
	if (_humanLowerNeedSwap) _swapLowerHumanSign();
	return true;
}

void Road::_swapCarSign() {
	if (_curSignCar != C_YELLOW)
		_curSignCar = C_YELLOW;
	else {
		_prevSignCar == C_GREEN ? _curSignCar = C_RED : _curSignCar = C_GREEN;
		_carNeedSwap = false;
	}
}

void Road::_swapUpperHumanSign() {
	_curSignUpperHuman == H_GREEN ? H_RED : H_GREEN;
}

void Road::_swapLowerHumanSign() {
	_curSignLowerHuman == H_GREEN ? H_RED : H_GREEN;
}