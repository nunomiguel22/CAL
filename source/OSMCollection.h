#include <utility>

#ifndef INTERFACE__OSMNODESCOLLECTION_H_
#define INTERFACE__OSMNODESCOLLECTION_H_

#include <map>
#include <vector>

#include "OSMNode.h"

class OSMCollection {

 public:
  void addNode(OSMNode node);
  std::map<idNode, OSMNode> getNodeMap();
  void setEdges(std::vector<std::pair<idNode,idNode>> edges);
  std::vector<std::pair<idNode, idNode>> getEdgesVector();

 private:
  std::map<idNode, OSMNode> OSMNodes;
  std::vector<std::pair<idNode, idNode>> OSMEdges;
};

#endif //INTERFACE__OSMNODESCOLLECTION_H_
