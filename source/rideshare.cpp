#include "rideshare.h"
#include <algorithm>
#include <sstream>
#include "graphviewer/graphviewer.h"

bool operator<(const Vertex<idNode> &a, const Vertex<idNode> &b) {
  return (a.getDist() < b.getDist()) ? true : false;
}

std::vector<User *> getPotentialPassengers(Graph<idNode> &graph,
                                           std::vector<User *> &users,
                                           User &driver) {
  std::vector<User *> potentialPassengers;

  for (User *user : users) {
    if (user == &driver) continue;

    /** update graph to driver start node **/
    graph.dijkstraShortestPath(driver.getRoute().startNode);
    /** get user information **/
    Vertex<idNode> *userStart = graph.findVertex(user->getRoute().startNode);
    double timeToUserStart = driver.getMinStartTime() + userStart->getDist();
    double minTimeToUserEnd = timeToUserStart + user->getTravelTime();
    double userDepartureTime = user->getRoute().departureTime.toMinutes();

    /** discard passenger if there is no path available to pickup **/
    if (userStart->getDist() == INF) continue;
    /** discard passenger if user can't reach pickup before his end time **/
    if (driver.getMaxEndTime() < userDepartureTime) continue;
    /** discard passenger if driver can't reach pickup in time **/
    if (timeToUserStart > userDepartureTime) continue;
    /** discard passenger if passenger doesnt reach his destination in time **/
    if (minTimeToUserEnd > user->getMaxEndTime()) continue;
    /** discard passenger if driver can't reach his destination in time **/
    if (minTimeToUserEnd > driver.getMaxEndTime()) continue;
    /** check path from user destination to driver destination **/
    graph.dijkstraShortestPath(user->getRoute().endNode);
    Vertex<idNode> *driverEnd = graph.findVertex(driver.getRoute().endNode);
    double timeFromUserToDriverDest = driverEnd->getDist();
    /** discard passenger if no path exists to driver destination **/
    if (timeFromUserToDriverDest == INF) continue;
    /** discard passenger if driver can't reach destination in time**/
    if (minTimeToUserEnd + timeFromUserToDriverDest > driver.getMaxEndTime())
      continue;
    /** potential passenger **/
    potentialPassengers.push_back(user);
  }
  return potentialPassengers;
}

std::list<Vertex<idNode> *> rideshareFast(Graph<idNode> &graph,
                                          std::vector<User *> &users,
                                          User &driver, double &travelTime,
                                          std::vector<User *> &passengers) {
  std::vector<User *> potentialPassengers =
      getPotentialPassengers(graph, users, driver);
  if (potentialPassengers.size() == 0) return driver.getPath();

  if (!driver.isSmoker())
    std::sort(potentialPassengers.begin(), potentialPassengers.end(),
              userPointerCompare);

  std::list<Vertex<idNode> *> path = driver.getPath();
  double timeToDriverDest;
  for (User *passenger : potentialPassengers) {
    std::list<Vertex<idNode> *> userPath;
    passengers.push_back(passenger);
    userPath = buildPath(graph, passengers, driver, timeToDriverDest);

    if (userPath.size() == 0 ||
        timeToDriverDest + driver.getMinStartTime() > driver.getMaxEndTime())
      passengers.pop_back();
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
                                          std::vector<User *> &passengers) {
  std::vector<User *> potentialPassengers =
      getPotentialPassengers(graph, users, driver);
  if (potentialPassengers.size() == 0) return driver.getPath();

  std::list<Vertex<idNode> *> bestPath = driver.getPath();
  unsigned int iterations = 0;

  while (iterations == passengers.size()) {
    ++iterations;
    double timeToDriverDest;
    double bestTime = INF;
    User *bestUser = NULL;
    for (User *passenger : potentialPassengers) {
      std::list<Vertex<idNode> *> userPath;
      passengers.push_back(passenger);
      userPath = buildPath(graph, passengers, driver, timeToDriverDest);

      if (userPath.size() == 0 || timeToDriverDest + driver.getMinStartTime() >
                                      driver.getMaxEndTime()) {
        potentialPassengers.erase(
            std::remove(potentialPassengers.begin(), potentialPassengers.end(),
                        passenger),
            potentialPassengers.end());
      } else if (timeToDriverDest < bestTime) {
        bestPath = userPath;
        travelTime = timeToDriverDest;
        bestUser = passenger;
      }
      passengers.pop_back();
    }
    if (bestUser != NULL) {
      passengers.push_back(bestUser);
      potentialPassengers.erase(
          std::remove(potentialPassengers.begin(), potentialPassengers.end(),
                      bestUser),
          potentialPassengers.end());
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
  for (User *user : users) user->setState(U_WAITING);

  res.push_back(graph.findVertex(driver.getRoute().startNode));
  std::list<Vertex<idNode> *>::iterator resIt;
  travelTimeTotal = 0;
  int numberOfPassengers = 0;

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
          numberOfPassengers < driver.getCarCapacity()) {
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
        ++numberOfPassengers;
      } else if (bestUser->getState() == U_TRAVEL) {
        bestUser->setState(U_ARRIVED);
        userPath = graph.getPath(currentNodeinfo, bestUser->getRoute().endNode);
        --numberOfPassengers;
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
  travelTimeTotal += finalPath.back()->getDist();
  res.insert(res.end(), ++finalPath.begin(), finalPath.end());
  return res;
}

void printPath(std::vector<User *> &users, OSMCollection &osmCol,
               std::list<Vertex<idNode> *> &path, User &driver,
               Graph<idNode> &graph) {
  if (path.size() == 0) {
    std::cout << "Path not possible" << std::endl;
    return;
  }

  for (User *user : users) user->setState(U_WAITING);
  std::cout << "Driver time tolerance:" << driver.getRoute().tolerance
            << std::endl;
  std::cout << "Driver departure time: " << driver.getRoute().departureTime.hour
            << ":" << driver.getRoute().departureTime.minute << std::endl;
  std::cout << "Driver arrival time: " << driver.getRoute().arrivalTime.hour
            << ":" << driver.getRoute().arrivalTime.minute << std::endl;
  std::cout << "Maximum travel time: "
            << driver.getMaxEndTime() - driver.getMinStartTime() << std::endl
            << std::endl;

  std::cout << "Path        - Description" << std::endl;
  std::list<Vertex<idNode> *>::iterator pathIterator;
  idNode previousNode;
  double weight = 0;

  for (pathIterator = path.begin(); pathIterator != path.end();
       ++pathIterator) {
    std::stringstream ss;
    Vertex<idNode> *node = *pathIterator;
    OSMNode *osmNode = osmCol.getNode(node->getInfo());

    ss << *osmNode;
    /** get edge weight **/

    if (pathIterator != path.begin()) {
      Edge<idNode> edge = graph.findEdge(previousNode, node->getInfo());
      if (edge.getDest() != NULL) weight += edge.getWeight();
    }
    previousNode = node->getInfo();

    if (pathIterator == path.begin()) {
      ss << " - Driver '" << driver.getName() << "' departure";
    }
    if (pathIterator == --path.end())
      ss << " - Driver '" << driver.getName() << "' destination"
         << "; Time:" << weight;

    for (User *user : users) {
      if (user->getState() == U_ARRIVED) continue;

      if (node->getInfo() == user->getRoute().startNode &&
          user->getState() == U_WAITING) {
        double userStartTime = user->getRoute().departureTime.toMinutes() -
                               driver.getRoute().departureTime.toMinutes();
        std::string des = "";
        if (weight < userStartTime) {
          weight = userStartTime;
          des = ", Waited for passenger";
        }
        ss << " - User '" << user->getName() << "' pickup"
           << "; Time:" << weight << des;
        user->setState(U_TRAVEL);
      }

      if (node->getInfo() == user->getRoute().endNode &&
          user->getState() == U_TRAVEL) {
        ss << " - User '" << user->getName() << "' destination"
           << "; Time:" << weight;
        user->setState(U_ARRIVED);
      }
    }
    std::cout << ss.str() << std::endl;
  }
}

void displayPath(std::vector<User *> &passengers,
                 std::list<Vertex<idNode> *> &path, User &driver) {
  /** reset user state **/
  for (User *passenger : passengers) passenger->setState(U_WAITING);

  GraphViewer *gViewer = new GraphViewer(600, 400, true, 5000);
  gViewer->createWindow(600, 400);
  int itCounter = 0;

  std::list<Vertex<idNode> *>::iterator pathIterator;
  for (pathIterator = path.begin(); pathIterator != path.end();
       ++pathIterator) {
    Vertex<idNode> *node = *pathIterator;
    gViewer->addNode(itCounter);
    std::string nodeInfo = to_string(node->getInfo());

    if (pathIterator == path.begin()) {
      nodeInfo += " - " + driver.getName() + " - S";
      gViewer->setVertexColor(itCounter, "white");
    }
    if (pathIterator == --path.end()) {
      nodeInfo += " - " + driver.getName() + " - E";
      gViewer->setVertexColor(itCounter, "black");
    }

    for (User *passenger : passengers) {
      if (passenger->getState() == U_ARRIVED) continue;

      if (node->getInfo() == passenger->getRoute().startNode &&
          passenger->getState() == U_WAITING) {
        nodeInfo += " - " + passenger->getName() + " - P";
        gViewer->setVertexColor(itCounter, "green");
        passenger->setState(U_TRAVEL);
      }

      if (node->getInfo() == passenger->getRoute().endNode &&
          passenger->getState() == U_TRAVEL) {
        nodeInfo += " - " + passenger->getName() + " - D";
        gViewer->setVertexColor(itCounter, "blue");
        passenger->setState(U_ARRIVED);
      }
    }
    gViewer->setVertexLabel(itCounter, nodeInfo);
    ++itCounter;
  }

  for (unsigned int i = 0; i < path.size() - 1; ++i) {
    gViewer->addEdge(i, i, i + 1, EdgeType::DIRECTED);
  }

  gViewer->rearrange();

  std::cout << std::endl
            << "Press Enter to close graphviewer and continue" << std::endl;
  std::cin.ignore();
  std::cin.get();

  gViewer->closeWindow();
  delete (gViewer);
}
