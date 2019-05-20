#include <math.h>
#define MATH_PI 3.14159265358979323846

#include "OSMCollection.h"

void OSMCollection::addNode(OSMNode node) {
  this->OSMNodes.insert(std::pair<idNode, OSMNode>(node.getOSMNodeId(), node));
}

std::map<idNode, OSMNode> OSMCollection::getNodeMap() { return this->OSMNodes; }

void OSMCollection::setEdges(std::vector<std::pair<idNode, idNode>> edges) {
  this->OSMEdges = std::move(edges);
}

std::vector<std::pair<idNode, idNode>> OSMCollection::getEdgesVector() {
  return this->OSMEdges;
}

// TODO: Check if collection has data and send exception
void OSMCollection::generateGraph(Graph<idNode> &graph) {
  for (auto &it : this->OSMNodes) {
    graph.addVertex(it.first);
  }

  for (auto &it : this->OSMEdges) {
    hour travelTime = this->getEdgesTravelTime(it.first, it.second);
    graph.addEdge(it.first, it.second, travelTime);
  }
}
hour OSMCollection::getEdgesTravelTime(idNode from, idNode to) {
  OSMNode nodeFrom = this->OSMNodes.at(from);
  OSMNode nodeTo = this->OSMNodes.at(to);
  coordinate lonDistance =
      nodeFrom.getNodeStruct().pos.posLat - nodeTo.getNodeStruct().pos.posLat;
  coordinate latDistance =
      nodeFrom.getNodeStruct().pos.posLon - nodeTo.getNodeStruct().pos.posLon;

  const double earthRadius = 6371;
  const double dToR = MATH_PI / 180;

  double dLat = latDistance * dToR;
  double dLon = lonDistance * dToR;
  double a = pow(sin(dLat / 2), 2) +
             cos(nodeFrom.getNodeStruct().pos.posLat * dToR) *
                 cos(nodeTo.getNodeStruct().pos.posLat * dToR) *
                 +pow(sin(dLon / 2), 2);

  double c = 2 * atan2(sqrt(a), sqrt(1 - a));
  double distance = earthRadius * c;

  // double distance = sqrt(pow(xDistance, 2.0) + pow(yDistance, 2.0));

  return (distance / AVERAGE_SPEED);
}
