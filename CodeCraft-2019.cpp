#include "iostream"
#include "SparseGraph.h"
#include "ReadGraph.h"
#include "Dijkstra/Dijkstra.h"
#include "WriteAnswer.h"

using namespace std;

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
	
	// TODO:read input filebuf
    cout << "\t--- READ INPUT FILEBUF ---" << endl;
	int V = 1000;
    SparseGraph<int> g = SparseGraph<int>(V, true);
    ReadGraph<SparseGraph<int>, int> readGraph(g, carPath, crossPath, roadPath);
    g.show();
    cout << "\n\tEND OF READ INPUT FILEBUF" << endl;

    // TODO:process
    cout << "\t--- PROCESS ---" << endl;
    cout<<"Test Dijkstra:"<<endl<<endl;

    vector<vector<int> > resArr(g.carList.size());
    for (int i = 0; i < g.carList.size(); i++) {

        Dijkstra<SparseGraph<int>, int> dij(g, g.carList[i].getFrom());
        if(dij.hasPathTo(g.carList[i].getTo())){
            resArr[i].push_back(g.carList[i].getId());
            resArr[i].push_back(g.carList[i].getPlanTime());
            cout<< g.carList[i].getFrom()<<" -> "<< g.carList[i].getTo() << " Shortest Path is " <<dij.shortestPathTo(g.carList[i].getTo())<<endl;
            dij.showPath(resArr[i], g.carList[i].getTo());
        }
        else {
            cout<<g.carList[i].getFrom()<<"No Path to "<<g.carList[i].getTo()<<endl;
        }     
        cout<<"----------"<<endl;
    }
    cout << "\n\tEND OF PROCESS" << endl;

    // TODO:write output file
    cout << "\t--- WRITE OUTPUT FILE ---" << endl;

    for (int i = 0; i < resArr.size(); i++) {
        for (int j = 0; j < resArr[i].size(); j++) {
            cout << resArr[i][j] << " ";
        }
        cout << endl;
    }

    cout << "last number is" << resArr.size() << endl;

    WriteAnswer writeAnswer(resArr, answerPath);
    cout << "\n\tEND OF WRITE OUTPUT FILE" << endl;

	return 0;
}