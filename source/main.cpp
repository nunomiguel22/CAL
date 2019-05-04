#include "Graph.h"
#include <string>


int main(){

    Graph<std::string> testGraph;
    
    /**
     * test graph
     * 
     *  * - Direction
     * 
     *  A*---3---*C  
     *  *        ** 10
     *  |      /  |   *
     *  5     1   6    E
     *  |   /     |   * 
     *  * *       * 3
     *  B*---2---*D* 
     *  
     */


    //Vertexes
    testGraph.addVertex("A");
    testGraph.addVertex("B");
    testGraph.addVertex("C");
    testGraph.addVertex("D");
    testGraph.addVertex("E");

    //Edges
    testGraph.addEdge("A", "B", 5);
    testGraph.addEdge("B", "A", 5);
    testGraph.addEdge("A", "C", 3);
    testGraph.addEdge("C", "A", 3);
    testGraph.addEdge("C", "B", 1);
    testGraph.addEdge("B", "C", 1);
    testGraph.addEdge("B", "D", 2);
    testGraph.addEdge("C", "D", 6);
    testGraph.addEdge("D", "C", 6);
    testGraph.addEdge("C", "E", 10);
    testGraph.addEdge("D", "E", 3);
    testGraph.addEdge("E", "D", 3);

    testGraph.dijkstraShortestPath("A");

    testGraph.print();

    return 0;
}