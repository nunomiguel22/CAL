
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
  std::cout << "Reading OSM data:";
  OSMCollection osmCol = OSMServices::extractOSMCollectionByCity("Porto");
  std::cout << std::endl << "Building Graph:";
  OSMServices::generateGraph(graph, osmCol);
  std::cout << std::endl << std::endl;
  OSMServices::addStreetNames(osmCol);

  /** read users **/
  std::vector<User *> users;
  readUsers(users, graph);
  /** launch menu **/
  mainMenu(graph, users, osmCol);
  /** save and delete users **/
  saveUsers(users);
  for (User *user : users) delete user;
  return 0;
}
