#ifndef __SOURCE_USER_H_
#define __SOURCE_USER_H_

#include "OSMNode_structs.h"

typedef double hour;
typedef std::string name;

typedef struct {
  idNode startPoint;
  idNode endPoint;
  hour departureTime;
  hour arrivalTime;
  hour tolerance;
} Route;

class User {

 public:
  class builder;
  name getUserName();
  Route getUserRoute();
  bool isDriver();
  bool isSmoker();
  int getCarCapacity();

 private:
  name userName;
  Route route;
  bool driver = false;
  bool smoker = false;
  int carCapacity = 0;
};

class User::builder {

 public:
  builder& setName(name name);
  builder& addStartPoint(idNode sPoint);
  builder& addEndPoint(idNode ePoint);
  builder& addDepartureTime(hour dTime);
  builder& addArrivalTime(hour aTime);
  builder& addTolerance(hour tol);

 private:
  name nameBuilder = "John Doe";
  idNode sPointBuilder = 0;
  idNode ePointBuilder = 0;
  hour dTimeBuilder = 0;
  hour aTimeBuilder = 0;
  hour tolBuilder = 0.0;
};

#endif // __SOURCE_USER_H_
