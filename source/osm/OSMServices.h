#ifndef __OSMEXTRACTOR_H_
#define __OSMEXTRACTOR_H_

#include <map>
#include "../Graph.h"
#include "../utils/FileManager.h"
#include "OSMCollection.h"

class OSMServices {
 public:
  static OSMCollection extractOSMCollectionByCity(const std::string &city);
  static void generateGraph(Graph<idNode> &graph, OSMCollection &osmCollection);
  static void addStreetNames(OSMCollection &osmCollection);

 private:
  static std::map<idNode, Position> getNodesXYPosition(const std::string &city);
  static std::vector<std::pair<idNode, idNode>> getEdges(
      const std::string &city);
};

#endif  //__OSMEXTRACTOR_H_
