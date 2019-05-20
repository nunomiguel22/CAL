

#include "OSMExtractor.h"
#include "Graph.h"

using namespace std;

int main(){

  Graph<idNode > graph;

  OSMExtractor osm_extractor;
  OSMCollection OSMCol = osm_extractor.extractOSMCollectionByCity("Porto");

  OSMCol.generateGraph(graph);

    return 0;
}