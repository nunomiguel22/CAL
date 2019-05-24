#include "rideshare.h"
#include <algorithm>

bool operator<(const Vertex<idNode> &a, const Vertex<idNode> &b) {
  return (a.getDist() < b.getDist()) ? true : false;
}

std::vector<User *> getPotentialPassangers(Graph<idNode> &graph,
                                           std::vector<User *> &users,
                                           User &driver) {
  std::vector<User *> potentialPassangers;

  for (User *user : users) {
    /** update graph to driver start node **/
    graph.dijkstraShortestPath(driver.getRoute().startNode);
    /** get user information **/
    Vertex<idNode> *userStart = graph.findVertex(user->getRoute().startNode);
    double timeToUserStart = driver.getMinStartTime() + userStart->getDist();
    double minTimeToUserEnd = timeToUserStart + user->getTravelTime();
    double userDepartureTime = user->getRoute().departureTime.toMinutes();

    /** discard passanger if there is no path available to pickup **/
    if (userStart->getDist() == INF) continue;
    /** discard passanger if user can't reach pickup before his end time **/
    if (driver.getMaxEndTime() < userDepartureTime) continue;
    /** discard passanger if driver can't reach pickup in time **/
    if (timeToUserStart > userDepartureTime) continue;
    /** discard passanger if passanger doesnt reach his destination in time **/
    if (minTimeToUserEnd > user->getMaxEndTime()) continue;
    /** discard passanger if driver can't reach his destination in time **/
    if (minTimeToUserEnd > driver.getMaxEndTime()) continue;
    /** check path from user destination to driver destination **/
    graph.dijkstraShortestPath(user->getRoute().endNode);
    Vertex<idNode> *driverEnd = graph.findVertex(driver.getRoute().endNode);
    double timeFromUserToDriverDest = driverEnd->getDist();
    /** discard passanger if no path exists to driver destination **/
    if (timeFromUserToDriverDest == INF) continue;
    /** discard passanger if driver can't reach destination in time**/
    if (minTimeToUserEnd + timeFromUserToDriverDest > driver.getMaxEndTime())
      continue;
    /** potential passanger **/
    potentialPassangers.push_back(user);
  }
  return potentialPassangers;
}

std::list<Vertex<idNode> *> rideshareFast(Graph<idNode> &graph,
                                          std::vector<User *> &users,
                                          User &driver, double &travelTime,
                                          std::vector<User *> &passangers) {
  std::vector<User *> potentialPassangers =
      getPotentialPassangers(graph, users, driver);
  if (potentialPassangers.size() == 0) return driver.getPath();

  std::list<Vertex<idNode> *> path = driver.getPath();
  double timeToDriverDest;
  for (User *passanger : potentialPassangers) {
    std::list<Vertex<idNode> *> userPath;
    passangers.push_back(passanger);
    userPath = buildPath(graph, passangers, driver, timeToDriverDest);

    if (userPath.size() == 0 ||
        timeToDriverDest + driver.getMinStartTime() > driver.getMaxEndTime())
      passangers.pop_back();
    else {
      path = userPath;
      travelTime = timeToDriverDest;
    }
  }
  return path;
}

std::list<Vertex<idNode> *> rideshareBest(Graph<idNode> &graph,
                                          std::vector<User *> &users,
                                          User &driver, double &travelTime,
                                          std::vector<User *> &passangers) {
  std::vector<User *> potentialPassangers =
      getPotentialPassangers(graph, users, driver);
  if (potentialPassangers.size() == 0) return driver.getPath();

  std::list<Vertex<idNode> *> bestPath = driver.getPath();
  unsigned int iterations = 0;

  while (iterations == passangers.size()) {
    ++iterations;
    double timeToDriverDest;
    double bestTime = INF;
    User *bestUser = NULL;
    for (User *passanger : potentialPassangers) {
      std::list<Vertex<idNode> *> userPath;
      passangers.push_back(passanger);
      userPath = buildPath(graph, passangers, driver, timeToDriverDest);

      if (userPath.size() == 0 || timeToDriverDest + driver.getMinStartTime() >
                                      driver.getMaxEndTime()) {
        potentialPassangers.erase(
            std::remove(potentialPassangers.begin(), potentialPassangers.end(),
                        passanger),
            potentialPassangers.end());
      } else if (timeToDriverDest < bestTime) {
        bestPath = userPath;
        travelTime = timeToDriverDest;
        bestUser = passanger;
      }
      passangers.pop_back();
    }
    if (bestUser != NULL) {
      passangers.push_back(bestUser);
      potentialPassangers.erase(
          std::remove(potentialPassangers.begin(), potentialPassangers.end(),
                      bestUser),
          potentialPassangers.end());
    }
  }
  return bestPath;
}

/** build path given a set of users **/
std::list<Vertex<idNode> *> buildPath(Graph<idNode> &graph,
                                      std::vector<User *> &users, User &driver,
                                      double &travelTimeTotal) {
  std::list<Vertex<idNode> *> res;
  if (users.size() == 0) {
    return res;
  }
  /** reset user state **/
  for (User *user : users) {
    user->setState(U_WAITING);
  }

  res.push_back(graph.findVertex(driver.getRoute().startNode));
  std::list<Vertex<idNode> *>::iterator resIt;
  travelTimeTotal = 0;
  int numberOfPassangers = 0;

  for (resIt = res.begin(); resIt != res.end(); ++resIt) {
    Vertex<idNode> *currentNode = *resIt;
    idNode currentNodeinfo = currentNode->getInfo();
    graph.dijkstraShortestPath(currentNodeinfo);

    /** select next best stop **/
    double bestWeight = INF;
    User *bestUser = NULL;
    for (User *user : users) {
      if (user->getState() == U_ARRIVED) continue;
      if (user->getState() == U_WAITING &&
          numberOfPassangers < driver.getCarCapacity()) {
        double userWeight =
            graph.findVertex(user->getRoute().startNode)->getDist();
        double userPickupTime =
            driver.getMinStartTime() + userWeight + travelTimeTotal;

        if (userPickupTime < user->getMinStartTime())
          userWeight = user->getMinStartTime() - driver.getMinStartTime();

        if (userWeight < bestWeight) {
          bestWeight = userWeight;
          bestUser = user;
        }
      }
      if (user->getState() == U_TRAVEL) {
        double userWeight =
            graph.findVertex(user->getRoute().endNode)->getDist();
        /** user not viable if can't reach his destination in time **/
        double userDestTime =
            driver.getMinStartTime() + userWeight + travelTimeTotal;
        if (userDestTime > user->getMaxEndTime()) {
          res.clear();
          return res;
        }
        if (userWeight < bestWeight) {
          bestWeight = userWeight;
          bestUser = user;
        }
      }
    }

    /** none of the users could be reached from the driver's start node **/
    if (bestUser == NULL) {
      for (User *user : users) {
        if (user->getState() == U_TRAVEL) {
          res.clear();
          return res;
        }
      }
    } else {
      /** build path and update user **/
      std::list<Vertex<idNode> *> userPath;
      if (bestUser->getState() == U_WAITING) {
        bestUser->setState(U_TRAVEL);
        userPath =
            graph.getPath(currentNodeinfo, bestUser->getRoute().startNode);
        ++numberOfPassangers;
      } else if (bestUser->getState() == U_TRAVEL) {
        bestUser->setState(U_ARRIVED);
        userPath = graph.getPath(currentNodeinfo, bestUser->getRoute().endNode);
        --numberOfPassangers;
      }
      if (userPath.size() == 0) {
        res.clear();
        return res;
      }

      travelTimeTotal += bestWeight;
      res.insert(res.end(), ++userPath.begin(), userPath.end());
      resIt = res.end();
      advance(resIt, -2);
    }
  }

  /** append path to final destination **/
  graph.dijkstraShortestPath(res.back()->getInfo());
  std::list<Vertex<idNode> *> finalPath =
      graph.getPath(res.back()->getInfo(), driver.getRoute().endNode);
  if (finalPath.size() == 0) {
    res.clear();
    return res;
  }

  res.insert(res.end(), ++finalPath.begin(), finalPath.end());
  return res;
}

void printPath(std::vector<User *> &users, minutes travelTime,
               std::list<Vertex<idNode> *> &path, User &driver) {
  if (path.size() == 0) {
    std::cout << "Path not possible" << std::endl;
    return;
  }

  for (User *user : users) user->setState(U_WAITING);

  std::cout << "Path      -  Description" << std::endl;
  std::list<Vertex<idNode> *>::iterator pathIterator;

  for (pathIterator = path.begin(); pathIterator != path.end();
       ++pathIterator) {
    Vertex<idNode> *node = *pathIterator;
    std::cout << node->getInfo();

    if (pathIterator == path.begin())
      std::cout << " - Driver '" << driver.getName() << "' departure";
    if (pathIterator == --path.end())
      std::cout << " - Driver '" << driver.getName() << "' destination";

    for (User *user : users) {
      if (user->getState() == U_ARRIVED) continue;

      if (node->getInfo() == user->getRoute().startNode &&
          user->getState() == U_WAITING) {
        std::cout << " - User '" << user->getName() << "' pickup";
        user->setState(U_TRAVEL);
      }

      if (node->getInfo() == user->getRoute().endNode &&
          user->getState() == U_TRAVEL) {
        std::cout << " - User '" << user->getName() << "' destination";
        user->setState(U_ARRIVED);
      }
    }
    std::cout << std::endl;
  }

  std::cout << "Time: " << travelTime << std::endl;
}
