#include "iostream"
#include "SparseGraph.h"
#include "io/ReadGraph.h"
#include "Dijkstra/Dijkstra.h"
#include "io/WriteAnswer.h"
#include "entity/Car.h"

#define WeightType double

using namespace std;


const int numberOfCross = 100;  // Cross的个数


void calculateCarsTime(SparseGraph<WeightType> &graph, vector<Car> &resArr);

int main(int argc, char *argv[])
{
    std::cout << "Begin" << std::endl;
	
	if(argc < 5){
		std::cout << "please input args: carPath, roadPath, crossPath, answerPath" << std::endl;
		exit(1);
	}
	
	std::string carPath(argv[1]);
	std::string roadPath(argv[2]);
	std::string crossPath(argv[3]);
	std::string answerPath(argv[4]);
	
	std::cout << "carPath is " << carPath << std::endl;
	std::cout << "roadPath is " << roadPath << std::endl;
	std::cout << "crossPath is " << crossPath << std::endl;
	std::cout << "answerPath is " << answerPath << std::endl;
	
	// TODO: read input filebuf

    SparseGraph<WeightType> g = SparseGraph<WeightType>(numberOfCross+1, true); // 初始化图g，（节点个数， 有向图）


    ReadGraph<SparseGraph<WeightType>, WeightType> readGraph(g, carPath, crossPath, roadPath); // 读文件三个文件

    g.show();   // 显示一下图的内容



    // TODO: process

    // MARK: - 拿到每个车辆的最短路径， 和最早出发时间

    vector<Car> resArr;  // resArr 是保存答案的二维数组存着每辆车的出发信息

    for (int i = 0; i < g.carList.size(); i++) {
        Car originCar = g.carList[i];
        Dijkstra<SparseGraph<WeightType>, WeightType> dij(g, originCar.getFrom());    // 对于图g，从车的起点组做Dijkstra

        // 如当前的起点有去终点，就把答案放入resArr答案数组中，否则程序有异常
        if( dij.hasPathTo(originCar.getTo()) ) {

            dij.showPath( originCar.getTo(), originCar ); // (到车的终点to， 保存结果roadList到originCar中)
            resArr.push_back(originCar);

            // 输出最短路径为多少
            // cout << originCar.getFrom() << " -> " << originCar.getTo() << " 最短路径长度为 "
            //      << dij.shortestPathTo( originCar.getTo() ) << endl;

        } else {
            // 应该不会触发
            cout << g.carList[i].getFrom() << " 没有路径去 " << g.carList[i].getTo() << "异常" <<endl;
            exit(1);
        }     
        // cout << "----------" << endl;
    }

    // TODO: - 计算每一辆车到终点的时间，放在与resArr的每一个Car中
    // 按起始时间从小到大排序， 计算每一辆开始时间和终止时间，保存到resArr中
    calculateCarsTime(g, resArr);

    // TODO： - 按车辆id从小到大排序



    // TODO:write output file
    WriteAnswer writeAnswer(resArr, answerPath);

    assert(resArr.size() == g.carList.size());
    cout << "一共有 " << resArr.size() << " 辆车"<< endl;
    cout << "运行结束" << endl;

	return 0;
}
bool cmpPlanTime(Car& c1,Car& c2){
    return c1.getPlanTime() < c2.getPlanTime();
}
bool cmpId(Car& c1,Car& c2){
    return c1.getId() < c2.getId();
}
void calculateCarsTime(SparseGraph<WeightType> &graph, vector<Car> &resArr) {

    sort(resArr.begin(),resArr.end(),cmpPlanTime);
    int prevFinshedTime = 0;
    for (int i = 0; i < resArr.size(); ++i) {
        Car& c = resArr[i];
        int costTime = 0;
        c.setStartTime(max(prevFinshedTime,c.getPlanTime()));
        for(int i : c.roadList){
            Edge<WeightType > *r = graph.getEdge(i);
            int curtime = r->getLength() / r->getSpeed() + 1;
            costTime += curtime;
        }
        prevFinshedTime = c.getStartTime() + costTime;
    }
    sort(resArr.begin(),resArr.end(),cmpId);
}


