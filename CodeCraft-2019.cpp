#include "iostream"
#include "SparseGraph.h"
#include "ReadGraph.h"
#include "Dijkstra.h"

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
	int V = 36;
    SparseGraph<int> g = SparseGraph<int>(V, true);
    ReadGraph<SparseGraph<int>, int> readGraph(g, carPath, crossPath, roadPath);
    g.show();

    // TODO:process

    cout<<"Test Dijkstra:"<<endl<<endl;
    Dijkstra<SparseGraph<int>, int> dij(g,1);
    for( int i = 1 ; i <= V ; i ++ ){
        if(dij.hasPathTo(i)){
            cout<<"Shortest Path to "<<i<<" : "<<dij.shortestPathTo(i)<<endl;
            dij.showPath(i);
        }
        else
            cout<<"No Path to "<<i<<endl;

        cout<<"----------"<<endl;
    }


    // TODO:write output file
	
	return 0;
}