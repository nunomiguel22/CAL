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
  route.departureTime.hour = 10;
  route.departureTime.minute = 0;
  route.arrivalTime.hour = 11;
  route.arrivalTime.minute = 20;
  route.startNode = 349907698;
  route.endNode = 473873457;
  User driver(route, "testDriver", graph);
  driver.setDriver(true, 2);

  route.tolerance = 10;
  route.departureTime.hour = 10;
  route.departureTime.minute = 15;
  route.arrivalTime.hour = 10;
  route.arrivalTime.minute = 40;
  route.startNode = 137994583;
  route.endNode = 349907649;
  User user1(route, "testJoao", graph);

  route.tolerance = 0;
  route.departureTime.hour = 10;
  route.departureTime.minute = 25;
  route.arrivalTime.hour = 10;
  route.arrivalTime.minute = 50;
  route.startNode = 473873465;
  route.endNode = 129548927;
  User user2(route, "testMaria", graph);

  route.tolerance = 0;
  route.departureTime.hour = 10;
  route.departureTime.minute = 20;
  route.arrivalTime.hour = 10;
  route.arrivalTime.minute = 50;
  route.startNode = 129548929;
  route.endNode = 137994720;
  User user3(route, "testAndre", graph);
  users.push_back(&user1);
  users.push_back(&user2);
  users.push_back(&user3);
  /** ! test users debug **/

  /** ! test build path **/
  double tripTime;
  std::vector<User *> passangers;
  std::list<Vertex<idNode> *> result =
      rideshareFast(graph, users, driver, tripTime, passangers);
  printPath(passangers, tripTime, result, driver);

  tripTime = 0;
  passangers.clear();
  std::list<Vertex<idNode> *> result2 =
      rideshareBest(graph, users, driver, tripTime, passangers);
  printPath(passangers, tripTime, result2, driver);
  /** ! test build path **/

  return 0;
}
