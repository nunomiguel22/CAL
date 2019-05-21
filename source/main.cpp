//#include "Graph.h"
//#include "OSMExtractor.h"

#include "Graph.h"
#include "OSMExtractor.h"

using namespace std;

int main() {
  Graph<idNode> graph;

  OSMExtractor osm_extractor;
  OSMCollection OSMCol = osm_extractor.extractOSMCollectionByCity("Porto");

  graph.generateGraph(OSMCol);


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
