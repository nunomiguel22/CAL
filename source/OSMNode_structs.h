#ifndef __OSMNODE_STRUCTS_H_
#define __OSMNODE_STRUCTS_H_

#include <string>

typedef unsigned long long int idNode;
typedef double coordinate;

typedef struct {
  coordinate posLat;
  coordinate posLon;
} Position;

typedef struct {
  idNode id;
  Position pos;
  std::string tag;
  std::string name;
} Node;

#endif  // __OSMNODE_STRUCTS_H_
