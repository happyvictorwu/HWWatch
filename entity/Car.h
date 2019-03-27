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
    int startTime;
    int finishTime;

public:
    vector<int> roadList;

    Car(int id, int from, int to, int speed, int planTime) {
        this->id = id;
        this->from = from;
        this->to = to;
        this->speed = speed;
        this->planTime = planTime;
        this->startTime = planTime;
        this->finishTime = -1;
    }

    Car() {}


    // Getter
    int getId(){ return id; }
    int getFrom() { return from; }
    int getTo() { return to; }
    int getSpeed() { return speed; }
    int getPlanTime() { return planTime; }
    int getStartTime() { return startTime; }
    int getFinishTime() { return finishTime; }  // 如何finishingTime是 -1 说明初始化没有计算到完成时间.

    // Setter
    void setStartTime(int time) {
        assert(time >= planTime);
        startTime = time;
    }

    void setFinishTime(int time) {
        assert(time > startTime);
        finishTime = time;
    }

};

#endif //CODECRAFT_2019_CAR_H
