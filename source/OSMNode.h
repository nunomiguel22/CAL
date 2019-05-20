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
  builder& addTag(std::string tag);
  builder& addName(std::string name);
  OSMNode build();

 private:
  idNode idBuilder = 1;
  coordinate xCoordBuilder = 0;
  coordinate yCoordBuilder = 0;
  std::string tagBuilder = "amenity=car_sharing";
  std::string nameBuilder = "default";
};


#endif //INTERFACE__OSMNODE_H_
