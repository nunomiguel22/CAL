#include <utility>

#ifndef __OSMCOLLECTION_H_
#define __OSMCOLLECTION_H_

#include <math.h>
#include <map>
#include <vector>
#include "OSMNode.h"

#define MATH_PI 3.14159265358979323846

// Assuming that X Y coordinates will give distance in km
#define AVERAGE_SPEED 50

class OSMCollection {
 public:
  void addNode(OSMNode node);
  std::map<idNode, OSMNode> getNodeMap();
  OSMNode* getNode(idNode node);
  void setEdges(std::vector<std::pair<idNode, idNode>> edges);
  std::vector<std::pair<idNode, idNode>> getEdgesVector();
  double getEdgesTravelTime(idNode from, idNode to);

 private:
  std::map<idNode, OSMNode> OSMNodes;
  std::vector<std::pair<idNode, idNode>> OSMEdges;
};

#endif  // __OSMNCOLLECTION_H_
