#pragma once
enum Direction
{
	FORWARD,
	RIGHT
};

class Car
{
public:
	Car();
	Car(Direction inDirection);

	Direction getDir() { return _direction; }

	bool setDir(Direction inDirection) { _direction = inDirection; }

private:

	Direction _direction;

	
};

