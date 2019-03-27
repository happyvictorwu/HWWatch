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
    int road_length;    //道路长度
    int road_speed; // 道路最高速度
    int road_channel;    // 车道数目


public:
    // 构造函数
    Edge(int a, int b, Weight weight){
        this->a = a;
        this->b = b;
        this->weight = weight;
    }

    Edge(int a, int b, Weight weight, int roadId, int road_length, int road_speed, int road_channel){
        this->a = a;
        this->b = b;
        this->weight = weight;
        this->road = roadId;
        this->road_length = road_length;
        this->road_speed = road_speed;
        this->road_channel = road_channel;
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


    // Getter
    int v(){ return a;} // 返回第一个顶点 from
    int w(){ return b;} // 返回第二个顶点 to
    Weight wt(){ return weight;}    // 返回权值
    int getRoad(){ return road; }   // 返回道路id
    int getSpeed() { return road_speed; }   //返回道路最高速度
    int getLength() { return road_length; } //返回道路长度
    int getChannel() { return road_channel; }   //返回车道数

    // Setter
    void setWt(Weight w) { weight = w; }

    // Method
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
