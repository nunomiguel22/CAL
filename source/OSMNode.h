#ifndef __OSMNODE_H_
#define __OSMNODE_H_

#include <vector>
#include "OSMNode_structs.h"
#include "User.h"

class OSMNode {

 public:
  class builder;
  explicit OSMNode(idNode id, Node node);
  idNode getOSMNodeId();
  Node getNodeStruct();
  void addUser(User user);
  std::vector<User> getUsers();

 private:
  idNode nodeId;
  Node node;
  std::vector<User> users;
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


#endif //__OSMNODE_H_
