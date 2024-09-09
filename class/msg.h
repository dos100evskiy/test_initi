#pragma once
#include "Car.h"

class msg
{
private:
	int _idRoad;
	int _curNumUpperHuman;
	int _curNumLowerHuman;
	int _curNumCar;
	SIGN_HUMAN _curUpperHumanSign;
	SIGN_HUMAN _curLowerHumanSign;
	SIGN_CAR _curCarSign;
	Car* _curCar;

	bool _needSwapUpperHumanSign;
	bool _needSwapLowerHumanSign;
	bool _needSwapCarSign;

public:
	msg();
	msg(int idRoad, int curNumUpperHuman, int curNumLowerHuman, int curNumCar, SIGN_HUMAN curUpperHumanSign, SIGN_HUMAN curLowerHumanSign,
		SIGN_CAR curCarSign, Car* curCar);
	void controlBoxUpdate(bool needSwapUpperHumanSign, bool needSwapLowerHumanSign, bool needSwapCarSign);

	~msg() = default;

	int getId() { return _idRoad; }
	int getCurNumUpperHuman() { return _curNumUpperHuman; }
	int getCurNumLowerHuman() { return _curNumLowerHuman; }
	int getNumCurCar() { return _curNumCar; }
	SIGN_HUMAN getCurUpperHumanSign() { return _curUpperHumanSign; }
	SIGN_HUMAN getCurLowerHumanSign() { return _curLowerHumanSign; }
	SIGN_CAR getCurCarSign() { return _curCarSign; };
	Car* getCar() { return _curCar; }

	bool getNeedUpperSwap() { return _needSwapUpperHumanSign; }
	bool getNeedLowerSwap() { return _needSwapLowerHumanSign; }
	bool getNeedCarSwap() { return _needSwapCarSign; }
};

