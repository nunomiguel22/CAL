
#include <queue>
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
  OSMCollection OSMCol = osmServices.extractOSMCollectionByCity("Porto");
  osmServices.generateGraph(graph, OSMCol);
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
