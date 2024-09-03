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

	Direction getDir() { return direction; }

	bool setDir(Direction inDirection) { direction = inDirection; }

private:

	Direction direction;

	
};

