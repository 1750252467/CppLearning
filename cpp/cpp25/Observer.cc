#include "Observer.hpp"
#include "Subject.hpp"

#include <stdlib.h>
#include <iostream>

using std::cout;
using std::endl;

void Baby::update()
{
   srand(clock());
    int randNumber = rand() % 100;
    if(randNumber < 70){
        cout << "Baby" << _name
            << "is starting crying loudly!" << endl;
    }else{
        cout << "Baby " << _name
            << "is starting sleeping sweetly!" << endl;
    }

}

void Nurse::update()
{
    srand(clock());
    int randNumber = rand() % 100;
    if(randNumber < 70) {
        cout << "Nurse" << _name
            << "is ready to open the door!" << endl;

    }else{
        cout << "Nurser" << _name
            << "is sleeping sweetly" << endl;
    }

}

void Guest::knockAt(Ring &ring)
{
    cout << "Guest" << _name << "knock at the door!" << endl;

    ring.bePressed();
    ring.setState(new RingState(false));
}

