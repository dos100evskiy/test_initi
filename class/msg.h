#pragma once
#include "Car.h"
class msg
{
private:
	int _idRoad;
	int _curNumUpperHuman;
	int _curNumLowerHuman;
	int _curNumCar;
	int _curUpperHumanSign;
	int _curLowerHumanSign;
	int _curCarSign;
	Car* _curCar;

	bool _needSwapUpperHumanSign;
	bool _needSwapLowerHumanSign;
	bool _needSwapCarSign;

public:
	msg(int idRoad, int curNumUpperHuman, int curNumLowerHuman, int curNumCar, int curUpperHumanSign, int curLowerHumanSign, 
		int curCarSign, Car* curCar);
	msg(bool needSwapUpperHumanSign, bool needSwapLowerHumanSign, bool needSwapCarSign);

	~msg() = default;

	int getId() { return _idRoad; }
	int getCuNumrUpperHuman() { return _curNumUpperHuman; }
	int getCurNumLowerHuman() { return _curNumLowerHuman; }
	int getNumCur() { return _curNumCar; }
	int getCurUpperHumanSign() { return _curUpperHumanSign; }
	int getCurLowerHumanSign() { return _curLowerHumanSign; }
	int getCurCarSign() { return _curCarSign; };
	Car* getCar() { return _curCar; }

	bool getNeedUpperSwap() { return _needSwapUpperHumanSign; }
	bool getNeedLowerSwap() { return _needSwapLowerHumanSign; }
	bool getNeedCarSwap() { return _needSwapCarSign; }
};

