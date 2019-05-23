#include <queue>
#include "Graph.h"
#include "OSMServices.h"
#include "rideshare.h"

using namespace std;

int main() {
  Graph<idNode> graph;

  OSMServices osmServices;
  OSMCollection OSMCol = osmServices.extractOSMCollectionByCity("Porto");
  osmServices.generateGraph(graph, OSMCol);

  /** test data **/
  User driver(349907698, 473873457, graph);
  driver.startTolerance = 2;
  driver.endTolerance = 100;
  driver.startTime = 0;
  driver.endTime = 10;
  driver.carSize = 2;
  driver.startTime = 0;
  driver.id = 0;
  /** test data **/

  /** test data **/
  std::vector<User> users;
  User user1(137994583, 129548929, graph);
  user1.startTolerance = 2;
  user1.endTolerance = 1;
  user1.startTime = 0;
  user1.endTime = 20;
  user1.id = 2;
  users.push_back(user1);
  /** test data **/

  double tripTime;
  list<Vertex<idNode> *> result = buildPath(graph, users, driver, tripTime);

  std::cout << "Vertex" << endl;
  for (Vertex<idNode> *vertex : result) {
    std::cout << vertex->getInfo() << endl;
  }

  std::cout << "Time: " << tripTime << std::endl;

  return 0;
}
