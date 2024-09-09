#include "msg.h"

msg::msg() {
	_idRoad = -1;
}

msg::msg(int idRoad, int curNumUpperHuman, int curNumLowerHuman, int curNumCar, SIGN_HUMAN curUpperHumanSign, SIGN_HUMAN curLowerHumanSign,
	SIGN_CAR curCarSign, Car* curCar) {
	_idRoad = idRoad;
	_curNumUpperHuman = curNumUpperHuman;
	_curNumLowerHuman = curNumLowerHuman;
	_curNumCar = curNumCar;
	_curUpperHumanSign = curUpperHumanSign;
	_curLowerHumanSign = curLowerHumanSign;
	_curCarSign = curCarSign;
	_curCar = curCar;

	_needSwapUpperHumanSign = false;
	_needSwapLowerHumanSign = false;
	_needSwapCarSign = false;
}

void msg::controlBoxUpdate(bool needSwapUpperHumanSign, bool needSwapLowerHumanSign, bool needSwapCarSign) {
	_needSwapUpperHumanSign = needSwapUpperHumanSign;
	_needSwapLowerHumanSign = needSwapLowerHumanSign;
	_needSwapCarSign = needSwapCarSign;
}