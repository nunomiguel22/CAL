
#include <iostream>
#include "Graph.h"
#include "User.h"
#include "graphviewer/graphviewer.h"
#include "menu.h"
#include "osm/OSMServices.h"
#include "rideshare.h"

int main() {
  /** generate graph of porto **/
  Graph<idNode> graph;
  OSMServices osmServices;
  std::cout << "Reading OSM data:";
  OSMCollection OSMCol = osmServices.extractOSMCollectionByCity("Porto");
  std::cout << std::endl << "Building Graph:";
  osmServices.generateGraph(graph, OSMCol);
  std::cout << std::endl << std::endl;
  /** read users **/
  std::vector<User *> users;
  readUsers(users, graph);
  /** launch menu **/
  mainMenu(graph, users);
  /** save and delete users **/
  saveUsers(users);
  for (User *user : users) delete user;
  return 0;
}
