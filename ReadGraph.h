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
        readCross(graph, crossPath, carPath);
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
        fclose(fp);
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
        fclose(fp);
    }

//#(id,roadId,roadId,roadId,roadId)
//    (1, 5000, 5005, -1, -1)
    void readCross(Graph &graph, const string &crossPath, const string &roadPath) {
        FILE *fp;
        fp = fopen(crossPath.c_str(), "r");
//        vector<int> road;
        int crossId, roadId1, roadId2, roadId3, roadId4;
        char str[100];
        fscanf(fp, "%s\n", str);
        cout << str << endl;
        while ( fscanf(fp, "(%d, %d, %d, %d, %d)\n", &crossId, &roadId1, &roadId2, &roadId3, &roadId4) ) {
            printf("%d %d %d %d %d\n", crossId, roadId1, roadId2, roadId3, roadId4);

            // road表,如何有crossId是from， 道路id为roadId的，检查一条边w为road.txt的to
            FILE *fp2;
            fp2 = fopen(roadPath.c_str(), "r");
//(id,length,speed,channel,from,to,isDuplex)
            int id, a2, a3, a4, from, to, a7;   // from 对应crossId
            char str1[100];
            fscanf(fp2, "%s\n", str1);
            while ( fscanf(fp2, "(%d, %d, %d, %d, %d, %d, %d)\n",
                           &id, &a2, &a3, &a4, &from, &to, &a7) != EOF) {
                if (id == roadId1) {
                    assert(from == crossId);
                    graph.addEdgeRoad(roadId1, crossId, to);
                    cout << from << " connect to " << to << " with " << roadId1;
                } else if (id == roadId2) {
                    assert(from == crossId);
                    graph.addEdgeRoad(roadId2, crossId, to);
                    cout << from << " connect to " << to << " with " << roadId2;
                } else if (id == roadId3) {
                    assert(from == crossId);
                    graph.addEdgeRoad(roadId3, crossId, to);
                    cout << from << " connect to " << to << " with " << roadId3;
                } else if (id == roadId4) {
                    assert(from == crossId);
                    graph.addEdgeRoad(roadId4, crossId, to);
                    cout << from << " connect to " << to << " with " << roadId4;
                }

            }
            fclose(fp2);

        }
    }

    


};

#endif //CODECRAFT_2019_READGRAPH_H
