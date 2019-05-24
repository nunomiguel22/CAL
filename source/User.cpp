#include "User.h"

name User::getName() const { return this->userName; }

Route User::getRoute() { return this->route; }

bool User::isDriver() const { return this->driver; }

bool User::isSmoker() const { return this->smoker; }

int User::getCarCapacity() const { return this->carCapacity; }

int User::getId() const { return id; }

userState User::getState() const { return state; }

void User::setSmoker(bool smoker) { this->smoker = smoker; }
void User::setDriver(bool driver, int capacity) {
  this->driver = driver;
  carCapacity = capacity;
}
void User::setState(userState state) { this->state = state; }

User::User(Route route, std::string name, Graph<idNode> &graph) {
  state = U_WAITING;
  this->route = route;
  this->userName = name;
  graph.dijkstraShortestPath(this->route.startNode);
  path = graph.getPath(this->route.startNode, this->route.endNode);
  travelTime = graph.findVertex(this->route.startNode)->getDist();
}
