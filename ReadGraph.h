//
// Created by Victor Wu on 2019-03-25.
//

#ifndef CODECRAFT_2019_READGRAPH_H
#define CODECRAFT_2019_READGRAPH_H

#include <iostream>
#include <string>
#include <fstream>
#include <sstream>
#include <cassert>
#include <vector>

using namespace std;

template <typename Graph, typename Weight>
class ReadGraph {
public:
    // 从文件filename中读取图的信息, 存储进图graph中
    ReadGraph(Graph &graph, const string &carPath, const string &crossPath, const string &roadPath){
        readRoad(graph, roadPath);
        readCar(graph, carPath);    
    }
private:

    void readRoad(Graph &graph, const string &roadPath) {
        FILE *fp;
        fp = fopen(roadPath.c_str(), "r");
        int id, length, speed, channel, from, to, isDuplex;
        char str1[100];
        fscanf(fp, "%s\n", str1);
        cout << str1 << endl;
        while ( fscanf(fp, "(%d, %d, %d, %d, %d, %d, %d)\n",
                       &id, &length, &speed, &channel, &from, &to, &isDuplex) != EOF) {
            printf("%d %d %d %d %d %d %d\n", id, length, speed, channel, from, to, isDuplex);
            int a = from;
            int b = to;
            Weight wt = (double)length / speed;

            assert( a > 0 && a <= graph.V() );
            assert( b > 0 && b <= graph.V() );

            graph.addEdge( a, b, wt);

            if (isDuplex) {
                graph.addEdge( b, a, wt );
            }
        }
    }

    void readCar(Graph &graph, const string &carPath) {
        FILE *fp;
        fp = fopen(carPath.c_str(), "r");
        int id, from, to, speed, planTime;
        char str[100];
        fscanf(fp, "%s\n", str);
        cout << str << endl;
        while ( fscanf(fp, "(%d, %d, %d, %d, %d)\n", &id, &from, &to, &speed, &planTime) != EOF) {
            printf("%d %d %d %d %d\n", id, from, to, speed, planTime);
            graph.carList.push_back( Car(id, from, to, speed, planTime) );
        }
    }

//#(id,roadId,roadId,roadId,roadId)
//    (1, 5000, 5005, -1, -1)
    void readCross(Graph &graph, const string &crossPath) {
        FILE *fp;
        fp = fopen(crossPath.c_str(), "r");
        vector<int> road;
        int crossId, roadId1, roadId2, roadId3, roadId4;
        char str[100];
        fscanf(fp, "%s\n", str);
        cout << str << endl;
        while ( fscanf(fp, "(%d, %d, %d, %d, %d)\n", &crossId, &roadId1, &roadId2, &roadId3, &roadId4) ) {
            printf("%d %d %d %d %d\n", crossId, roadId1, roadId2, roadId3, roadId4);
            road.push_back(roadId1);
            road.push_back(roadId2);
            road.push_back(roadId3);
            road.push_back(roadId4);
            graph.addEdgeRoad(crossId, road);
            road.clear();
        }
    }

    


};

#endif //CODECRAFT_2019_READGRAPH_H
