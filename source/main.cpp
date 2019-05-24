#include <queue>
#include "Graph.h"
#include "OSMServices.h"
#include "User.h"
#include "rideshare.h"

using namespace std;

int main() {
  Graph<idNode> graph;

  OSMServices osmServices;
  OSMCollection OSMCol = osmServices.extractOSMCollectionByCity("Porto");
  osmServices.generateGraph(graph, OSMCol);

  /** ! test users debug **/

  std::vector<User> users;
  Route route;
  route.departureTime.hour = 10;
  route.departureTime.minutes = 0;
  route.arrivalTime.hour = 10;
  route.arrivalTime.minutes = 55;
  route.startNode = 137992808;
  route.endNode = 137994720;
  User driver(route, "testDriver", graph);
  driver.setDriver(true, 2);

  route.departureTime.hour = 10;
  route.departureTime.minutes = 10;
  route.arrivalTime.hour = 11;
  route.arrivalTime.minutes = 55;
  route.startNode = 137992807;
  route.endNode = 349907649;
  User user1(route, "testJoao", graph);
  users.push_back(user1);

  /** ! test users debug **/

  /** ! test build path **/
  double tripTime;
  list<Vertex<idNode> *> result = buildPath(graph, users, driver, tripTime);

  if (result.size() == 0) {
    std::cout << "path not possible" << std::endl;
    return 0;
  }

  std::cout << "Vertex" << endl;
  for (Vertex<idNode> *vertex : result) {
    std::cout << vertex->getInfo();
    if (vertex->getInfo() == driver.getRoute().startNode)
      std::cout << " - driver start";
    if (vertex->getInfo() == driver.getRoute().endNode)
      std::cout << " - driver destination";

    for (User &user : users) {
      if (vertex->getInfo() == user.getRoute().startNode) {
        std::cout << " - user " << user.getName() << " pickup";
      }
      if (vertex->getInfo() == user.getRoute().endNode) {
        std::cout << " - user " << user.getName() << " destination";
      }
    }
    std::cout << std::endl;
  }

  std::cout << "Time: " << tripTime << std::endl;
  /** ! test build path **/

  return 0;
}
