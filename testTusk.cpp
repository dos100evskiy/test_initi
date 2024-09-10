#include <iostream>
#include <ctime>
#include "class/ControlBox.h"
#include "class/Road.h"

int main()
{
    srand(time(0));
    setlocale(LC_ALL, "Russian");
    Road r0(0), r1(1), r2(2), r3(3);
    std::array<Road, 4> roads = { r0, r1, r2, r3 };
    
    for(auto var : roads)
        std::cout << var.getNumOfCars() << "\t\t" << var.getNumOfLowerHuman() << "\t\t" << var.getNumOfUpperHuman() << std::endl;

    ControlBox controlBox;
    char menu;
    while (true) {
        system("cls");
        for (auto var : roads)
            controlBox.acceptMSG(var.createMSG());
        std::cout << "\n\n\n";

        if (!controlBox.culculate()) {
            std::cout << "Не смог скалькулировать =( (остановить алгоритм - \'s\')" << std::endl;
            std::cin >> menu;
            if (menu == 's')
                break;
            continue;
        }

        for (int i = 0; i < roads.size(); ++i) {
            if (!roads[i].acceptMSG(controlBox.createMSG(roads[i].getID()))) {
                std::cout << "Дорога с ID = " << roads[i].getID() << "не смогла получить сообщение (остановить алгоритм - \'s\')" << std::endl;
                std::cin >> menu;
                if (menu == 's')
                    break;
                continue;
            }
        }

        for (int i = 0; i < roads.size(); ++i) {
            roads[i].update();
            std::cout << roads[i].getNumOfCars() << "\t\t" << roads[i].getNumOfLowerHuman() << "\t\t" << roads[i].getNumOfUpperHuman() << std::endl;
            std::cout << roads[i].getSignCar() << "\t\t" << roads[i].getLowerSign() << "\t\t" << roads[i].getUpperSign() << "\n\n";
        }
        std::cout << "\n\n\n";
        std::cin >> menu;
        if (menu == 's')
            break;
    }

}
