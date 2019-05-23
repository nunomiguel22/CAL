#include "User.h"

name User::getUserName() { return this->userName; }

Route User::getUserRoute() { return this->route; }

bool User::isDriver() { return this->driver; }

bool User::isSmoker() { return this->smoker; }

int User::getCarCapacity() { return this->carCapacity; }

User::builder &User::builder::setName(name name) {
  this->nameBuilder = std::move(name);
  return *this;
}

User::builder &User::builder::addStartPoint(idNode sPoint) {
  this->sPointBuilder = sPoint;
  return *this;
}

User::builder &User::builder::addEndPoint(idNode ePoint) {
  this->ePointBuilder = ePoint;
  return *this;
}

User::builder &User::builder::addDepartureTime(hour dTime) {
  this->dTimeBuilder = dTime;
  return *this;
}

User::builder &User::builder::addArrivalTime(hour aTime) {
  this->aTimeBuilder = aTime;
  return *this;
}

User::builder &User::builder::addTolerance(hour tol) {
  this->tolBuilder = tol;
  return *this;
}

User::User(idNode sNode, idNode eNode, Graph<idNode> &graph) {
  startNode = sNode;
  endNode = eNode;
  graph.dijkstraShortestPath(sNode);
  path = graph.getPath(sNode, eNode);
  bestTravelTime = graph.findVertex(sNode)->getDist();
}
