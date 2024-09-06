#include "msg.h"

msg::msg(int idRoad, int curNumUpperHuman, int curNumLowerHuman, int curNumCar, int curUpperHumanSign, int curLowerHumanSign,
	int curCarSign, Car* curCar) {
	_idRoad = idRoad;
	_curNumUpperHuman = curNumUpperHuman;
	_curNumLowerHuman = curNumLowerHuman;
	_curNumCar = curNumCar;
	_curUpperHumanSign = curUpperHumanSign;
	_curLowerHumanSign = curLowerHumanSign;
	_curCarSign = curCarSign;
	_curCar = curCar;
}

msg::msg(bool needSwapUpperHumanSign, bool needSwapLowerHumanSign, bool needSwapCarSign) {
	_needSwapUpperHumanSign = needSwapUpperHumanSign;
	_needSwapLowerHumanSign = needSwapLowerHumanSign;
	_needSwapCarSign = needSwapCarSign;
}