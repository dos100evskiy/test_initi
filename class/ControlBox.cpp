#include "ControlBox.h"

void ControlBox::acceptMSG(msg inMSG) {
	auto iter = std::find_if(_msgs.begin(), _msgs.end(), [&inMSG](msg val) { return (val.getId() == inMSG.getId()); });
	if (iter != _msgs.end()) {
		delete &iter;
		_msgs.erase(iter);
	}

	_msgs.push_back(inMSG);
}

msg ControlBox::sendMSG(int id) {
	auto iter = std::find_if(_msgs.begin(), _msgs.end(), [id](msg val) {return (val.getId() == id); });
	if (iter != _msgs.end())
		return *iter;
	
	return msg();
}

ControlBox::ControlBox() {
	_curCarSign = { C_RED, C_RED, C_RED, C_RED };
	_curHumanLowerSign = { H_RED, H_RED, H_RED, H_RED };
	_curHumanUpperSign = { H_RED, H_RED, H_RED, H_RED };

	_carSignDuration = { 0, 0, 0, 0 };
	_humanLowerSignDuration = { 0, 0, 0, 0 };
	_humanUpperSignDuration = { 0, 0, 0, 0 };

	_koefs = { {
		{{0, 0, 0}},
		{{0, 0, 0}},
		{{0, 0, 0}},
		{{0, 0, 0}}
		} };

	_ansCarSign = { C_RED, C_RED, C_RED, C_RED };
	_ansHumanLowerSign = { H_RED, H_RED, H_RED, H_RED };
	_ansHumanUpperSign = { H_RED, H_RED, H_RED, H_RED };
}

void ControlBox::_updateArrays() {
	for (auto msg : _msgs) {
		int id = msg.getId();

		if (_curCarSign[id] != msg.getCurCarSign()) {
			_curCarSign[id] = msg.getCurCarSign();
			_carSignDuration[id] = 1;
		}
		else
			_carSignDuration[id]++;

		if (_curHumanLowerSign[id] != msg.getCurLowerHumanSign()) {
			_curHumanLowerSign[id] = msg.getCurLowerHumanSign();
			_humanLowerSignDuration[id] = 1;
		}
		else
			_humanLowerSignDuration[id]++;

		if (_curHumanUpperSign[id] != msg.getCurUpperHumanSign()) {
			_curHumanUpperSign[id] = msg.getCurUpperHumanSign();
			_humanUpperSignDuration[id] = 1;
		}
		else
			_humanUpperSignDuration[id]++;
	}
}		

[[nodiscard]] bool ControlBox::culculate() {
	if (_msgs.size() != 4)
		return false;

	_updateArrays();
	for (int i = 0; i < _msgs.size(); ++i)
		_culcKoefRoad(i);
	std::pair<int, std::pair<int, int>> configuration = _culcMaxSum();

	if (configuration.first == 0) {
		auto iter = find_if(_msgs.begin(), _msgs.end(), [](msg val) {return val.getId() == 0; });
		iter->controlBoxUpdate(iter->getCurCarSign() != C_GREEN,
			iter->getCurLowerHumanSign() == configuration.second.first, iter->getCurUpperHumanSign() == configuration.second.second);

		iter = find_if(_msgs.begin(), _msgs.end(), [](msg val) {return val.getId() == 1; });
		iter->controlBoxUpdate(iter->getCurCarSign() != (configuration.second.first == 1 ? C_GREEN : C_RED),
			iter->getCurLowerHumanSign() != H_RED, iter->getCurUpperHumanSign() != H_RED);

		iter = find_if(_msgs.begin(), _msgs.end(), [](msg val) {return val.getId() == 2; });
		iter->controlBoxUpdate(iter->getCurCarSign() != C_GREEN,
			iter->getCurLowerHumanSign() == configuration.second.second, iter->getCurUpperHumanSign() == configuration.second.first);

		iter = find_if(_msgs.begin(), _msgs.end(), [](msg val) {return val.getId() == 3; });
		iter->controlBoxUpdate(iter->getCurCarSign() != (configuration.second.second == 1 ? C_GREEN : C_RED),
			iter->getCurLowerHumanSign() != H_RED, iter->getCurUpperHumanSign() != H_RED);

	} 
	else {
		auto iter = find_if(_msgs.begin(), _msgs.end(), [](msg val) {return val.getId() == 0; });
		iter->controlBoxUpdate(iter->getCurCarSign() != (configuration.second.first == 1 ? C_GREEN : C_RED),
			iter->getCurLowerHumanSign() != H_RED, iter->getCurUpperHumanSign() == H_RED);

		iter = find_if(_msgs.begin(), _msgs.end(), [](msg val) {return val.getId() == 1; });
		iter->controlBoxUpdate(iter->getCurCarSign() != C_GREEN,
			iter->getCurLowerHumanSign() == configuration.second.first , iter->getCurUpperHumanSign() == configuration.second.second);

		iter = find_if(_msgs.begin(), _msgs.end(), [](msg val) {return val.getId() == 2; });
		iter->controlBoxUpdate(iter->getCurCarSign() != (configuration.second.second == 1 ? C_GREEN : C_RED),
			iter->getCurLowerHumanSign() != H_RED, iter->getCurUpperHumanSign() != H_RED);

		iter = find_if(_msgs.begin(), _msgs.end(), [](msg val) {return val.getId() == 3; });
		iter->controlBoxUpdate(iter->getCurCarSign() != C_GREEN,
			iter->getCurLowerHumanSign() == configuration.second.second, iter->getCurUpperHumanSign() == configuration.second.second);
	}

	return true;
}

void ControlBox::_culcKoefRoad(int id) {
	auto iter = find_if(_msgs.begin(), _msgs.end(), [id](msg val) {return val.getId() == id; });
	
	_koefs[id][0] = iter->getCurCarSign() == C_YELLOW ? 0 :(0.2 * exp(0.3 * (double)(iter->getNumCurCar())) - 0.2) * (iter->getCurCarSign() == C_GREEN ?
		1.8 * exp(-0.25 * (double)_carSignDuration[id]) : 0.4 * exp(0.3 * (double)_carSignDuration[id]));

	_koefs[id][1] = (0.2 * exp(0.3 * (double)(iter->getCurNumUpperHuman())) - 0.2) * (iter->getCurNumUpperHuman() == H_GREEN ?
		2 * exp(-0.6 * (double)_humanUpperSignDuration[id]) : 0.4 * exp(0.4 * (double)_humanUpperSignDuration[id]));

	_koefs[id][2] = (0.2 * exp(0.3 * (double)(iter->getCurNumLowerHuman())) - 0.2) * (iter->getCurNumLowerHuman() == H_GREEN ?
		2 * exp(-0.6 * (double)_humanLowerSignDuration[id]) : 0.4 * exp(0.4 * (double)_humanLowerSignDuration[id]));

}

std::pair<int, std::pair<int, int>> ControlBox::_culcMaxSum() {
	std::pair<int, std::pair<int,int>> variantVertical = std::make_pair(0, std::make_pair(-1,-1)),
		variantHorizontal = std::make_pair(1, std::make_pair(-1, -1));
	double vertical = _koefs[0][0] + _koefs[2][0];
	double horizontal = _koefs[1][0] + _koefs[3][0];
	
	for (auto var : _msgs) {
		//for vertical
		if (var.getId() == 1) {
			if (var.getCar()->getDir() == RIGHT && (_koefs[0][1] + _koefs[2][2] < _koefs[1][0])) {
					vertical += _koefs[1][0];
					variantVertical.second.first = 1;
			}
			else {
				vertical += _koefs[0][1] + _koefs[2][2];
				variantVertical.second.first = 0;
			}
		}
		else if (var.getId() == 3) {
			if (var.getCar()->getDir() == RIGHT && (_koefs[0][2] + _koefs[2][1] < _koefs[3][0])) {
				vertical += _koefs[3][0];
				variantVertical.second.second = 1;
			}
			else {
				vertical += _koefs[0][2] + _koefs[2][1];
				variantVertical.second.second = 0;
			}
		}
		// for horizontal
		if (var.getId() == 0) {
			if (var.getCar()->getDir() == RIGHT && (_koefs[1][2] + _koefs[3][1] < _koefs[0][0])) {
				horizontal += _koefs[0][0];
				variantHorizontal.second.first = 1;
			}
			else {
				horizontal += _koefs[1][2] + _koefs[3][1];
				variantHorizontal.second.first = 0;
			}
		}
		else if (var.getId() == 2) {
			if (var.getCar()->getDir() == RIGHT && (_koefs[1][1] + _koefs[3][2] < _koefs[2][0])) {
				horizontal += _koefs[2][0];
				variantHorizontal.second.second = 1;
			}
			else {
				horizontal += _koefs[1][1] + _koefs[3][2];
				variantHorizontal.second.second = 0;
			}
		}
		else
			throw 1;
	}

	return (horizontal > vertical ? variantHorizontal : variantVertical);
}