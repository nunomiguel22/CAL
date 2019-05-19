//
// Created by Ricardo Ferreira on 2019-05-18.
//

#ifndef INTERFACE__OSMNODE_H_
#define INTERFACE__OSMNODE_H_

#include "OSMNode_structs.h"

class OSMNode {

 public:
  class builder;
  explicit OSMNode(idNode id, Node node);
  idNode getOSMNodeId();
  Node getNodeStruct();

 private:
  idNode nodeId;
  Node node;
};

class OSMNode::builder {

 public:
  builder& addNodeId(idNode id);
  builder& addXcoord(coordinate xCoord);
  builder& addYcoord(coordinate yCoord);
  builder& addType(std::string type);
  OSMNode build();

 private:
  idNode id = 1;
  coordinate xCoord = 0;
  coordinate yCoord = 0;
  std::string type = "default";
};


#endif //INTERFACE__OSMNODE_H_
