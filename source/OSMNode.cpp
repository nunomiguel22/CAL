#include <utility>

#include "OSMNode.h"

OSMNode::OSMNode(idNode id, Node node) {
  this->nodeId = id;
  this->node = std::move(node);
}

idNode OSMNode::getOSMNodeId() {

  return this->nodeId;
}

Node OSMNode::getNodeStruct() {

  return this->node;
}

OSMNode::builder& OSMNode::builder::addNodeId(idNode nodeID) {

  this->id = nodeID;
  return *this;
}

OSMNode::builder& OSMNode::builder::addXcoord(coordinate nodeXCoord) {
  this->xCoord = nodeXCoord;
  return *this;
}

OSMNode::builder & OSMNode::builder::addYcoord(coordinate yCoord) {
  this->yCoord = yCoord;
  return *this;
}

OSMNode::builder & OSMNode::builder::addType(std::string nodeType) {
  this->type = std::move(nodeType);
  return *this;
}

OSMNode OSMNode::builder::build() {

  Node tmpNode;
  tmpNode.id = this->id;
  tmpNode.pos.posX = this->xCoord;
  tmpNode.pos.posY = this->yCoord;
  tmpNode.type = this->type;
  return OSMNode{this->id, tmpNode};
}

