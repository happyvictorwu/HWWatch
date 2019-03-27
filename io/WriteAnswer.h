//
// Created by Victor Wu on 2019-03-25.
//

#ifndef CODECRAFT_2019_WRITEANSWER_H
#define CODECRAFT_2019_WRITEANSWER_H

#include <iostream>
#include <string>
#include <fstream>
#include <sstream>
#include <cassert>

using namespace std;

class WriteAnswer {
public:
    WriteAnswer(const vector<Car> &res, const string &answerPath) {
        FILE *fp;
        fp = fopen(answerPath.c_str(), "w+");
        fprintf(fp, "#(carId,StartTime,RoadId...)\n" );
        for (int i = 0; i < res.size(); i++) {
            fprintf(fp, "(");
            Car car = res[i];
            fprintf(fp, "%d,%d,", car.getId(), car.getStartTime());
            for (int j = 0; j < car.roadList.size(); j++) {
                fprintf(fp, "%d", car.roadList[j]);
                if (j != car.roadList.size() - 1)
                    fprintf(fp, ",");
            }
            fprintf(fp, ")\n");
        }
    }
};

#endif //CODECRAFT_2019_WRITEANSWER_H
