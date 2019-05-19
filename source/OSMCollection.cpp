
#include "OSMCollection.h"

void OSMCollection::addNode(OSMNode node) {

  this->OSMNodes.insert(std::pair<idNode ,OSMNode>(node.getOSMNodeId(), node));
}

std::map<idNode, OSMNode> OSMCollection::getNodeMap() {

  return this->OSMNodes;
}

void OSMCollection::setEdges(std::vector<std::pair<idNode, idNode>> edges) {

  this->OSMEdges = edges;

}

std::vector<std::pair<idNode, idNode>> OSMCollection::getEdgesVector() {

  return this->OSMEdges;
}


