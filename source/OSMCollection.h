#include <utility>

#ifndef INTERFACE__OSMNODESCOLLECTION_H_
#define INTERFACE__OSMNODESCOLLECTION_H_

#include <map>
#include <vector>

#include "OSMNode.h"
#include "Graph.h"

//Assuming that X Y coordinates will give distance in km
#define AVERAGE_SPEED 50

typedef double hour;

class OSMCollection {

 public:
  void addNode(OSMNode node);
  std::map<idNode, OSMNode> getNodeMap();
  void setEdges(std::vector<std::pair<idNode,idNode>> edges);
  std::vector<std::pair<idNode, idNode>> getEdgesVector();
  void generateGraph(Graph<idNode> &graph);
  hour getEdgesTravelTime(idNode from, idNode to);

 private:
  std::map<idNode, OSMNode> OSMNodes;
  std::vector<std::pair<idNode, idNode>> OSMEdges;
};

#endif //INTERFACE__OSMNODESCOLLECTION_H_
