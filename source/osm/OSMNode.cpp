#include "OSMNode.h"

OSMNode::OSMNode(idNode id, Node node) {
  this->nodeId = id;
  this->node = std::move(node);
}

idNode OSMNode::getOSMNodeId() { return this->nodeId; }

Node OSMNode::getNodeStruct() { return this->node; }

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

OSMNode OSMNode::builder::build() {
  Node tmpNode;
  tmpNode.id = this->idBuilder;
  tmpNode.pos.posLat = this->xCoordBuilder;
  tmpNode.pos.posLon = this->yCoordBuilder;
  tmpNode.name = this->nameBuilder;
  return OSMNode{this->idBuilder, tmpNode};
}
