#include "User.h"

name User::getName() const { return this->userName; }
Route User::getRoute() { return this->route; }
bool User::isDriver() const { return this->driver; }
bool User::isSmoker() const { return this->smoker; }
int User::getCarCapacity() const { return this->carCapacity; }
int User::getId() const { return id; }
int User::getMinStartTime() const { return minStartTime; }
int User::getMaxEndTime() const { return maxEndTime; }
userState User::getState() const { return state; }
std::list<Vertex<idNode> *> User::getPath() { return path; }
double User::getTravelTime() const { return travelTime; }

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
  travelTime = graph.findVertex(this->route.endNode)->getDist();
  minStartTime = this->route.departureTime.toMinutes() - this->route.tolerance;
  maxEndTime = this->route.arrivalTime.toMinutes() + this->route.tolerance;
}
