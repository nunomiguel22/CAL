#include <queue>
#include "Graph.h"
#include "OSMServices.h"
#include "User.h"
#include "rideshare.h"

int main() {
  /** generate graph of porto **/
  Graph<idNode> graph;
  OSMServices osmServices;
  OSMCollection OSMCol = osmServices.extractOSMCollectionByCity("Porto");
  osmServices.generateGraph(graph, OSMCol);

  /** ! test users debug **/
  std::vector<User> users;
  Route route;
  route.departureTime.hour = 10;
  route.departureTime.minute = 0;
  route.arrivalTime.hour = 10;
  route.arrivalTime.minute = 55;
  route.startNode = 137992808;
  route.endNode = 137994720;
  User driver(route, "testDriver", graph);
  driver.setDriver(true, 2);

  route.departureTime.hour = 10;
  route.departureTime.minute = 10;
  route.arrivalTime.hour = 11;
  route.arrivalTime.minute = 55;
  route.startNode = 137992807;
  route.endNode = 349907649;
  User user1(route, "testJoao", graph);
  users.push_back(user1);
  /** ! test users debug **/

  /** ! test build path **/
  double tripTime;
  std::list<Vertex<idNode> *> result =
      buildPath(graph, users, driver, tripTime);

  printPath(users, tripTime, result, driver);
  /** ! test build path **/

  return 0;
}
