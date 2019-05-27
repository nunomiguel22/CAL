#ifndef __SOURCE_USER_H_
#define __SOURCE_USER_H_

#include <list>
#include "Graph.h"
#include "osm/OSMNode.h"
#include "timeofday.h"

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
  int minStartTime;
  int maxEndTime;
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
  int getMinStartTime() const;
  int getMaxEndTime() const;
  userState getState() const;
  std::list<Vertex<idNode>*> getPath();
  double getTravelTime() const;

  void setState(userState state);
  void setSmoker(bool smoker);
  void setDriver(bool driver, int capacity);
  void setId(int id);
};

bool userPointerCompare(User* a, User* b);

#endif  // __SOURCE_USER_H_
