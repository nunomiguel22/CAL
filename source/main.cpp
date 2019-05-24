#include <queue>
#include "Graph.h"
#include "OSMServices.h"
#include "User.h"
#include "rideshare.h"

/**
 * TODO: Sort users by smoker
 * TODO: Test path against all users
 * TODO: Time restrictions
 * TODO: Graphviewer display
 * TODO: Node names
 * TODO: Node search
 *
 * TODO: Report
 */

int main() {
  /** generate graph of porto **/
  Graph<idNode> graph;
  OSMServices osmServices;
  OSMCollection OSMCol = osmServices.extractOSMCollectionByCity("Porto");
  osmServices.generateGraph(graph, OSMCol);

  /** ! test users debug **/
  std::vector<User *> users;
  Route route;
  route.tolerance = 10;
  route.departureTime.hour = 9;
  route.departureTime.minute = 0;
  route.arrivalTime.hour = 10;
  route.arrivalTime.minute = 15;
  route.startNode = 137992808;
  route.endNode = 137994720;
  User driver(route, "testDriver", graph);
  driver.setDriver(true, 2);

  route.tolerance = 0;
  route.departureTime.hour = 9;
  route.departureTime.minute = 14;
  route.arrivalTime.hour = 9;
  route.arrivalTime.minute = 40;
  route.startNode = 137992807;
  route.endNode = 349907649;
  User user1(route, "testJoao", graph);
  users.push_back(&user1);
  /** ! test users debug **/

  /** ! test build path **/
  double tripTime;
  std::list<Vertex<idNode> *> result =
      rideshareFast(graph, users, driver, tripTime);

  printPath(users, tripTime, result, driver);
  /** ! test build path **/

  return 0;
}
