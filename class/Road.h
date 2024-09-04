#pragma once
#include <vector>
#include "Car.h"

class Road
{
public:
	Road();
	Road(int maxHuman, int maxCar, int percantRotation, int newHumanChance = 40, int newCarChance = 30);
	Road(int numOfUpperHuman, int NumOfLowerHuman,int numOfCars, int percantRotation, int newHumanChance = 40, int newCarChance = 30);
	bool update();
	
	int numOfCars() { return _cars.size(); }
	int numOfUpperHuman() { return _upperNumOfHuman; }
	int numOfLowerHuman() { return _lowerNumOfHuman; }

private:
	std::vector<Car*> _cars;
	int _upperNumOfHuman;
	int _lowerNumOfHuman;

	int _newHumanChance;
	int _newCarChance;
};

