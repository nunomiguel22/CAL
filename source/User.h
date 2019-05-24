#ifndef __SOURCE_USER_H_
#define __SOURCE_USER_H_

#include <list>
#include "Graph.h"
#include "OSMNode.h"

typedef double hours;
typedef double minutes;
typedef struct timeOfDay {
  hours hour;
  minutes minutes;
} timeOfDay;

typedef std::string name;

typedef struct {
  idNode startNode;
  idNode endNode;
  timeOfDay departureTime;
  timeOfDay arrivalTime;
  minutes tolerance;
} Route;

typedef enum { U_WAITING, U_TRAVEL, U_ARRIVED } userState;

class User {
 private:
  name userName;
  Route route;
  bool driver;
  bool smoker;
  int carCapacity;
  int id;
  userState state;
  std::list<Vertex<idNode>*> path;
  double travelTime;

 public:
  User(Route route, std::string name, Graph<idNode>& graph);
  name getName() const;
  Route getRoute();
  bool isDriver() const;
  bool isSmoker() const;
  int getCarCapacity() const;
  int getId() const;
  userState getState() const;
  void setState(userState state);
  void setSmoker(bool smoker);
  void setDriver(bool driver, int capacity);

  std::list<Vertex<idNode>*> getPath();
  double getTravelTime() const;
};

#endif  // __SOURCE_USER_H_
