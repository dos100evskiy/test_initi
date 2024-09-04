#include "Car.h"

Car::Car() {
	_direction = FORWARD;
}

Car::Car(Direction inDirection) {
	_direction = inDirection;
}