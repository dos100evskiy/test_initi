#include <iostream>
#include <ctime>
#include "class/Road.h"

int main()
{
    srand(time(0));


    Road *road = new Road();
    std::cout << road->getNumOfCars() << std::endl;
    if (road->getFirstCar())
        std::cout << road->getFirstCar()->getDir();
}
