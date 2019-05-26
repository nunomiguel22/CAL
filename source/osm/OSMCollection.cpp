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

hour OSMCollection::getEdgesTravelTime(idNode from, idNode to) {
  OSMNode nodeFrom = this->OSMNodes.at(from);
  OSMNode nodeTo = this->OSMNodes.at(to);

  const double earthRadius = 6371;
  const double dToR = MATH_PI / 180;
  double lat1r, lon1r, lat2r, lon2r, u, v;
  lat1r = nodeFrom.getNodeStruct().pos.posLat * dToR;
  lon1r = nodeFrom.getNodeStruct().pos.posLon * dToR;
  lat2r = nodeTo.getNodeStruct().pos.posLat * dToR;
  lon2r = nodeTo.getNodeStruct().pos.posLon * dToR;
  u = sin((lat2r - lat1r) / 2);
  v = sin((lon2r - lon1r) / 2);
  double distance = 2.0 * earthRadius *
                    asin(sqrt(pow(u, 2) + cos(lat1r) * cos(lat2r) * pow(v, 2)));

  return (distance * AVERAGE_SPEED);
}
