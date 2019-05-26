#include <queue>
#include "Graph.h"
#include "User.h"
#include "osm/OSMNode.h"

std::vector<User *> getPotentialPassangers(Graph<idNode> &graph,
                                           std::vector<User *> &users,
                                           User &driver);

std::list<Vertex<idNode> *> rideshareFast(Graph<idNode> &graph,
                                          std::vector<User *> &users,
                                          User &driver, double &travelTime,
                                          std::vector<User *> &passengers);

std::list<Vertex<idNode> *> rideshareBest(Graph<idNode> &graph,
                                          std::vector<User *> &users,
                                          User &driver, double &travelTime,
                                          std::vector<User *> &passengers);

std::list<Vertex<idNode> *> buildPath(Graph<idNode> &graph,
                                      std::vector<User *> &users, User &driver,
                                      double &travelTimeTotal);

void printPath(std::vector<User *> &users, double travelTime,
               std::list<Vertex<idNode> *> &path, User &driver,
               Graph<idNode> &graph);

void displayPath(std::vector<User *> &passengers,
                 std::list<Vertex<idNode> *> &path, User &driver);
