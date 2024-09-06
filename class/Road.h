#pragma once
#include <queue>
#include "msg.h"
enum SIGN_CAR {
	C_RED,
	C_YELLOW,
	C_GREEN
};

enum SIGN_HUMAN {
	H_RED,
	H_GREEN
};

class Road
{
public:
	Road();
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
	msg* createMSG();
	[[nodiscard]] bool acceptMSG(msg* inMSG);

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

