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
    WriteAnswer(const vector<vector<int> > &res, const string &answerPath) {
        FILE *fp;
        fp = fopen(answerPath.c_str(), "w+");

        for (int i = 0; i < res.size(); i++) {
            fprintf(fp, "(");
            for (int j = 0; j < res[i].size(); j++) {
                fprintf(fp, "%d", res[i][j]);
                if (j != res[i].size() - 1)
                    fprintf(fp, ",");
            }
            fprintf(fp, ")\n");
        }

    }
};

#endif //CODECRAFT_2019_WRITEANSWER_H
