#include "OSMNode.h"
#include <iomanip>
#include <iostream>

OSMNode::OSMNode(idNode id, Node node) {
  this->nodeId = id;
  this->node = std::move(node);
}

idNode OSMNode::getOSMNodeId() const { return this->nodeId; }

Node OSMNode::getNodeStruct() { return this->node; }

std::string OSMNode::getName() const { return node.name; }

OSMNode::builder& OSMNode::builder::addNodeId(idNode nodeID) {
  this->idBuilder = nodeID;
  return *this;
}

OSMNode::builder& OSMNode::builder::addXcoord(coordinate nodeXCoord) {
  this->xCoordBuilder = nodeXCoord;
  return *this;
}

OSMNode::builder& OSMNode::builder::addYcoord(coordinate yCoord) {
  this->yCoordBuilder = yCoord;
  return *this;
}

void OSMNode::setName(std::string name) { node.name = name; }

std::ostream& operator<<(std::ostream& os, const OSMNode& node) {
  os << std::left << std::setw(11) << node.getOSMNodeId() << " - "
     << std::setw(40) << node.getName();
  return os;
}

OSMNode OSMNode::builder::build() {
  Node tmpNode;
  tmpNode.id = this->idBuilder;
  tmpNode.pos.posLat = this->xCoordBuilder;
  tmpNode.pos.posLon = this->yCoordBuilder;
  tmpNode.name = this->nameBuilder;
  return OSMNode{this->idBuilder, tmpNode};
}
