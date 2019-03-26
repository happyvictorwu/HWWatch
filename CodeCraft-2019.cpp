#include "iostream"
#include "SparseGraph.h"
#include "io/ReadGraph.h"
#include "Dijkstra/Dijkstra.h"
#include "io/WriteAnswer.h"

using namespace std;


const int numberOfCross = 100;  // Cross的个数

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

    SparseGraph<int> g = SparseGraph<int>(numberOfCross+1, true); // 初始化图g，（节点个数， 有向图）


    ReadGraph<SparseGraph<int>, double> readGraph(g, carPath, crossPath, roadPath); // 读文件三个文件

    g.show();   // 显示一下图的内容



    // TODO: process

    // MARK: - 拿到每个车辆的最短路径， 和最早出发时间

    vector<vector<int> > resArr( g.carList.size() );  // resArr 是保存答案的二维数组存着每辆车的出发信息

    for (int i = 0; i < g.carList.size(); i++) {

        Car originCar = g.carList[i];

        Dijkstra<SparseGraph<int>, int> dij(g, originCar.getFrom());    // 对于图g，从车的起点组做Dijkstra

        // 如当前的起点有去终点，就把答案放入resArr答案数组中，否则程序有异常
        if( dij.hasPathTo( originCar.getTo() ) ) {

            //头两个元素分别是 车辆的时间 , 实际的出发时间
            resArr[i].push_back(originCar.getId());
            resArr[i].push_back(originCar.getPlanTime());

            dij.showPath( originCar.getTo(), resArr[i] ); // (到车的终点to， 保存结果的数组resArr)

            // 输出最短路径为多少
            cout << originCar.getFrom() << " -> " << originCar.getTo() << " 最短路径长度为 "
                 << dij.shortestPathTo( originCar.getTo() ) << endl;

        } else {
            cout << g.carList[i].getFrom() << " 没有路径去 " << g.carList[i].getTo() << "异常" <<endl;
            exit(1);
        }     
        cout << "----------" << endl;

        // MARK: - 拿每辆车路程时间


    }




    // TODO:write output file
    WriteAnswer writeAnswer(resArr, answerPath);

    // 输出数组：
//    printf("#(carId,StartTime,RoadId...)\n");
//    for (int i = 0; i < resArr.size(); i++) {
//        printf("(");
//        for (int j = 0; j < resArr[i].size(); j++) {
//            printf("%d", resArr[i][j]);
//            if (j != resArr[i].size() - 1)
//                printf(",");
//        }
//        printf(")\n");
//    }
    assert(resArr.size() == g.carList.size());
    cout << "一共有 " << resArr.size() << " 辆车"<< endl;
    cout << "运行结束" << endl;

	return 0;
}