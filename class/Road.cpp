#include "Road.h"

Road::Road() {
	_upperNumOfHuman = rand() % 5;
	_lowerNumOfHuman = rand() % 5;
	int j = rand() % 5;
	for (int i = 0; i < j; ++i)
		_cars.push_back((rand() % 10 > 6 ? new Car(RIGHT) : new Car(FORWARD)));

	_newHumanChance = 40;
	_newCarChance = 30;
}

Road::Road(int maxHuman, int maxCar, int percantRotation, int newHumanChance, int newCarChance) {
	_upperNumOfHuman = rand() % (maxHuman + 1);
	_lowerNumOfHuman = rand() % (maxHuman + 1);
	_newCarChance = newCarChance > 100 ? 100 : newCarChance;
	_newHumanChance = _newHumanChance > 100 ? 100 : newHumanChance;

	int j = rand() % (maxCar + 1);
	for (int i = 0; i < j; ++i) {
		_cars.push_back((rand() % 100 < percantRotation ? new Car(RIGHT) : new Car(FORWARD)));
	}
}

Road::Road(int numOfUpperHuman, int NumOfLowerHuman, int numOfCars, int percantRotation, int newHumanChance, int newCarChance) {
	_upperNumOfHuman = numOfUpperHuman;
	_lowerNumOfHuman = NumOfLowerHuman;
	_newCarChance = newCarChance > 100 ? 100 : newCarChance;
	_newHumanChance = _newHumanChance > 100 ? 100 : newHumanChance;

	for(int i = 0; i < numOfCars; ++i) 
		_cars.push_back((rand() % 100 < percantRotation ? new Car(RIGHT) : new Car(FORWARD)));

}