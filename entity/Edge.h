//
// Created by Victor Wu on 2019-03-25.
//

#ifndef CODECRAFT_2019_EDGE_H
#define CODECRAFT_2019_EDGE_H

#include <iostream>
#include <cassert>
#include <vector>

using namespace std;

// 边
template<typename Weight>
class Edge{
private:
    int a,b;    // 边的两个端点
    Weight weight;  // 边的权值
    int road;   //拥有的道路

public:
    // 构造函数
    Edge(int a, int b, Weight weight){
        this->a = a;
        this->b = b;
        this->weight = weight;
    }

    Edge(int a, int b, Weight weight, int roadId){
        this->a = a;
        this->b = b;
        this->weight = weight;
        this->road = roadId;
    }

    // 空的构造函数, 所有的成员变量都取默认值
    Edge(){}

    ~Edge(){}


    // 返回第一个顶点
    int v(){ return a;}
    // 返回第二个顶点
    int w(){ return b;}
    // 返回权值
    Weight wt(){ return weight;}

    void setWt(Weight w) { weight = w; }

    int getRoad(){ return road; }

    void addRoad(int road) {
        this->road = road;
    }


    // 给定一个顶点, 返回另一个顶点
    int other(int x){
        assert( x == a || x == b );
        return x == a ? b : a;
    }

    // 输出边的信息
    friend ostream& operator<<(ostream &os, const Edge &e){
        os<<e.a<<"-"<<e.b<<": "<<e.weight;
        return os;
    }

    // 边的大小比较, 是对边的权值的大小比较
    bool operator<(Edge<Weight>& e){
        return weight < e.wt();
    }
    bool operator<=(Edge<Weight>& e){
        return weight <= e.wt();
    }
    bool operator>(Edge<Weight>& e){
        return weight > e.wt();
    }
    bool operator>=(Edge<Weight>& e){
        return weight >= e.wt();
    }
    bool operator==(Edge<Weight>& e){
        return weight == e.wt();
    }
};

#endif //CODECRAFT_2019_EDGE_H
