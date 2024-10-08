#pragma once
#include <queue>
#include "msg.h"

class Road
{
public:
	Road();
	Road(int id);
	Road(int id, int maxHuman, int maxCar, int percantRotation, int newHumanChance = 40, int newCarChance = 30);
	Road(int id, int numOfUpperHuman, int NumOfLowerHuman,int numOfCars, int percantRotation, int newHumanChance = 40, int newCarChance = 30);
	bool update();

	int getID() { return _id; }

	int getNumOfCars() { return static_cast<int>(_cars.size()); }
	Car* getFirstCar() { return _cars.empty() ? nullptr : _cars.front(); }
	int getNumOfUpperHuman() { return _upperNumOfHuman; }
	int getNumOfLowerHuman() { return _lowerNumOfHuman; }

	void needSwapCarSign() { _carNeedSwap = true; }
	void needSwapLowerHumanSign() { _humanLowerNeedSwap = true; }
	void needSwapUpperHumanSin() { _humanUpperNeedSwap = true; }

	SIGN_CAR getSignCar() { return _curSignCar; }
	SIGN_HUMAN getLowerSign() { return _curSignLowerHuman; } 
	SIGN_HUMAN getUpperSign() { return _curSignUpperHuman; }
	msg createMSG();
	[[nodiscard]] bool acceptMSG(msg inMSG);

private:
	int _id;
	void _constructor();
	std::queue<Car*> _cars;
	int _upperNumOfHuman;
	int _lowerNumOfHuman;

	SIGN_CAR _curSignCar;
	SIGN_CAR _prevSignCar;
	SIGN_HUMAN _curSignUpperHuman;
	SIGN_HUMAN _curSignLowerHuman;

	int _newHumanChance;
	int _newCarChance;
	int _percantRotation;

	bool _carNeedSwap;
	bool _humanUpperNeedSwap;
	bool _humanLowerNeedSwap;

	void _swapCarSign();
	void _swapUpperHumanSign();
	void _swapLowerHumanSign();
};

