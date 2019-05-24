#include <queue>
#include "Graph.h"
#include "OSMNode.h"
#include "User.h"

std::list<Vertex<idNode> *> buildPath(Graph<idNode> &graph,
                                      std::vector<User> &users, User &driver,
                                      double &travelTimeTotal);

void printPath(std::vector<User> &users, minutes travelTime,
               std::list<Vertex<idNode> *> &path, User &driver);
