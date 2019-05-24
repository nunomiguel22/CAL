#ifndef __OSMNODE_H_
#define __OSMNODE_H_

#include <string>
#include <vector>

typedef unsigned long int idNode;
typedef double coordinate;

typedef struct {
  coordinate posLat;
  coordinate posLon;
} Position;

typedef struct {
  idNode id;
  Position pos;
  std::string name;
} Node;

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
  builder& addName(std::string name);
  OSMNode build();

 private:
  idNode idBuilder = 1;
  coordinate xCoordBuilder = 0;
  coordinate yCoordBuilder = 0;
  std::string nameBuilder = "default";
};

#endif  //__OSMNODE_H_
