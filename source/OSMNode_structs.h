#ifndef INTERFACE__OSMNODE_STRUCTS_H_
#define INTERFACE__OSMNODE_STRUCTS_H_

#include <string>

typedef unsigned long long int idNode;
typedef long double coordinate;

typedef struct {
  coordinate posX;
  coordinate posY;
} Position;

typedef struct {
  idNode id;
  Position pos;
  std::string type;
} Node;

#endif //INTERFACE__OSMNODE_STRUCTS_H_
