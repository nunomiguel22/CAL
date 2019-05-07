#include "Graph.h"
#include <string>
#include <list>
#include <stdio.h>


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
    std::string origin = "C";
    std::string destination = "D";

    std::list<Vertex<std::string>*> path = testGraph.getPath(origin, destination);
    printf("\nPath from %s to %s:\n", origin.c_str(), destination.c_str());
    int counter = 0;
    for (Vertex<std::string> *vertex : path){
        printf("Node %d: %s\n", counter, vertex->getInfo().c_str());
        ++counter;
    }


    Vertex<std::string> *test = testGraph.findVertex("E");
    Vertex<std::string> *closest = test->getNearestVertex();
    printf("\n\nClosest Vertex:%s\n", closest->getInfo().c_str());


    return 0;
}