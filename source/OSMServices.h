#ifndef __OSMEXTRACTOR_H_
#define __OSMEXTRACTOR_H_

#include <map>
#include "Graph.h"
#include "OSMCollection.h"
#include "utils/FileManager.h"

class OSMServices {
 public:
  OSMCollection extractOSMCollectionByCity(const std::string &city);
  void generateGraph(Graph<idNode> &graph, OSMCollection &osmCollection);

 private:
  std::map<idNode, Position> getNodesXYPosition(const std::string &city);
  std::vector<std::pair<idNode, idNode>> getEdges(const std::string &city);
};

#endif  //__OSMEXTRACTOR_H_
