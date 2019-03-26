//
// Created by Victor Wu on 2019-03-25.
//

#ifndef CODECRAFT_2019_CAR_H
#define CODECRAFT_2019_CAR_H

#include <iostream>
#include <cassert>

using namespace std;

class Car {
private:
    int id;
    int from;
    int to;
    int speed;
    int planTime;

public:
    Car(int id, int from, int to, int speed, int planTime) {
        this->id = id;
        this->from = from;
        this->to = to;
        this->speed = speed;
        this->planTime = planTime;
    }

    int getId(){ return id; }
    int getFrom() { return from; }
    int getTo() { return to; }
    int getSpeed() { return speed; }
    int getPlanTime() { return planTime; }

};

#endif //CODECRAFT_2019_CAR_H
