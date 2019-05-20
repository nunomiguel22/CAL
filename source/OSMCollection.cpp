#include <utility>


#include "OSMCollection.h"

void OSMCollection::addNode(OSMNode node) {

  this->OSMNodes.insert(std::pair<idNode ,OSMNode>(node.getOSMNodeId(), node));
}

std::map<idNode, OSMNode> OSMCollection::getNodeMap() {

  return this->OSMNodes;
}

void OSMCollection::setEdges(std::vector<std::pair<idNode, idNode>> edges) {

  this->OSMEdges = std::move(edges);

}

std::vector<std::pair<idNode, idNode>> OSMCollection::getEdgesVector() {

  return this->OSMEdges;
}

//TODO: Check if collection has data and send exception
void OSMCollection::generateGraph(Graph<idNode> &graph) {

  for (auto & it : this->OSMNodes) {

    graph.addVertex(it.first);
  }

  for (auto & it: this->OSMEdges) {
    hour travelTime = this->getEdgesTravelTime(it.first, it.second);
    graph.addEdge(it.first, it.second, travelTime);
  }
}
hour OSMCollection::getEdgesTravelTime(idNode from, idNode to) {

  OSMNode nodeFrom = this->OSMNodes.at(from);
  OSMNode nodeTo = this->OSMNodes.at(to);
  coordinate xDistance = nodeFrom.getNodeStruct().pos.posX - nodeTo.getNodeStruct().pos.posX;
  coordinate yDistance = nodeFrom.getNodeStruct().pos.posY - nodeTo.getNodeStruct().pos.posY;
  double distance = sqrt(pow(xDistance, 2.0)+pow(yDistance, 2.0));

  return (distance / AVERAGE_SPEED);

}



