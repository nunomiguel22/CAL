#include "Graph.h"
#include "OSMServices.h"

using namespace std;

int main() {
  Graph<idNode> graph;

  OSMServices osmServices;
  OSMCollection OSMCol = osmServices.extractOSMCollectionByCity("Porto");
  osmServices.generateGraph(graph, OSMCol);

  list<Vertex<idNode>*> result = graph.getPath(1296455226, 111447975);

  cout << "Vertex     -     Time Traveled" << endl;
  double travelTime = 0;
  for (Vertex<idNode>* vertex : result) {
    travelTime += vertex->getDist();
    cout << vertex->getInfo() << ":"
         << "        " << travelTime << endl;
  }

  return 0;
}
