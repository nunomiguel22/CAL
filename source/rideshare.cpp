#include "rideshare.h"
#include <algorithm>

using namespace std;

bool operator<(const Vertex<idNode> &a, const Vertex<idNode> &b) {
  return (a.getDist() < b.getDist()) ? true : false;
}

list<Vertex<idNode> *> buildPath(Graph<idNode> &graph, vector<User> &users,
                                 User &driver, double &travelTimeTotal) {
  list<Vertex<idNode> *> res;
  if (users.size() == 0) {
    return res;
  }
  /** reset user state **/
  for (User &user : users) {
    user.setState(U_WAITING);
  }

  res.push_back(graph.findVertex(driver.getRoute().startNode));
  list<Vertex<idNode> *>::iterator resIt;
  travelTimeTotal = 0;
  int numberOfPassangers = 0;

  for (resIt = res.begin(); resIt != res.end(); ++resIt) {
    Vertex<idNode> *currentNode = *resIt;
    idNode currentNodeinfo = currentNode->getInfo();
    graph.dijkstraShortestPath(currentNodeinfo);

    /** select next best stop **/
    double bestWeight = INF;
    User *bestUser = NULL;
    for (User &user : users) {
      if (user.getState() == U_ARRIVED) continue;
      if (user.getState() == U_WAITING &&
          numberOfPassangers < driver.getCarCapacity()) {
        double userWeight =
            graph.findVertex(user.getRoute().startNode)->getDist();
        if (userWeight < bestWeight) {
          bestWeight = userWeight;
          bestUser = &user;
        }
      }
      if (user.getState() == U_TRAVEL) {
        double userWeight =
            graph.findVertex(user.getRoute().endNode)->getDist();
        if (userWeight < bestWeight) {
          bestWeight = userWeight;
          bestUser = &user;
        }
      }
    }

    /** none of the users could be reached from the driver's start node **/
    if (bestUser == NULL) {
      for (User &user : users) {
        if (user.getState() == U_TRAVEL) {
          res.clear();
          return res;
        }
      }
    } else {
      /** build path and update user **/
      list<Vertex<idNode> *> userPath;
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

      travelTimeTotal += userPath.back()->getDist();
      res.insert(res.end(), ++userPath.begin(), userPath.end());
      resIt = res.end();
      advance(resIt, -2);
    }
  }

  /** append path to final destination **/
  graph.dijkstraShortestPath(res.back()->getInfo());
  list<Vertex<idNode> *> finalPath =
      graph.getPath(res.back()->getInfo(), driver.getRoute().endNode);
  if (finalPath.size() == 0) {
    res.clear();
    return res;
  }

  res.insert(res.end(), ++finalPath.begin(), finalPath.end());
  return res;
}
