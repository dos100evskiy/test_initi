#pragma once
#include "Road.h"
#include <vector>
#include <array>

class ControlBox
{
private:
	std::array<SIGN_CAR, 4> _curCarSign;
	std::array<int, 4> _carSignDuration;

	std::array<SIGN_HUMAN, 4> _curHumanUpperSign;
	std::array<int, 4> _humanUpperSignDuration;

	std::array<SIGN_HUMAN, 4> _curHumanLowerSign;
	std::array<int, 4> _humanLowerSignDuration;

	std::array<std::array<double, 3>, 4> _koefs;

	void _updateArrays();

	void _culcKoefRoad(int id);

	std::pair<int, std::pair<int, int>> _culcMaxSum();

	std::array<SIGN_CAR, 4> _ansCarSign;
	std::array<SIGN_HUMAN, 4> _ansHumanUpperSign;
	std::array<SIGN_HUMAN, 4> _ansHumanLowerSign;

	std::vector<msg> _msgs;

public:
	ControlBox();

	void acceptMSG(msg msg);
	msg sendMSG(int id);
	
	[[nodiscard]] bool culculate();

};

