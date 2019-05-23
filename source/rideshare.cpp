#include "rideshare.h"
#include <algorithm>
#include "User.h"

using namespace std;

bool operator<(const Vertex<idNode> &a, const Vertex<idNode> &b) {
  return (a.getDist() < b.getDist()) ? true : false;
}

list<Vertex<idNode> *> buildPath(Graph<idNode> &graph, vector<User> &users,
                                 User &driver, double &travelTimeTotal) {
  list<Vertex<idNode> *> res;
  if (users.size() == 0) {
    res = driver.path;
    return res;
  }
  /** reset user state **/
  for (User &user : users) {
    user.state = U_WAITING;
  }

  res.push_back(graph.findVertex(driver.startNode));
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
      if (user.state == U_ARRIVED) continue;
      if (user.state == U_WAITING && numberOfPassangers < driver.carSize) {
        double userWeight = graph.findVertex(user.startNode)->getDist();
        if (userWeight < bestWeight) {
          bestWeight = userWeight;
          bestUser = &user;
        }
      }
      if (user.state == U_TRAVEL) {
        double userWeight = graph.findVertex(user.endNode)->getDist();
        if (userWeight < bestWeight) {
          bestWeight = userWeight;
          bestUser = &user;
        }
      }
    }

    /** none of the users could be reached from the driver's start node **/
    if (bestUser == NULL) {
      for (User &user : users) {
        if (user.state == U_TRAVEL) {
          res = driver.path;
          return res;
        }
      }
    } else {
      /** build path and update user **/
      list<Vertex<idNode> *> userPath;
      if (bestUser->state == U_WAITING) {
        bestUser->state = U_TRAVEL;
        userPath = graph.getPath(currentNodeinfo, bestUser->startNode);
        ++numberOfPassangers;
      } else if (bestUser->state == U_TRAVEL) {
        bestUser->state = U_ARRIVED;
        userPath = graph.getPath(currentNodeinfo, bestUser->endNode);
        --numberOfPassangers;
      }

      travelTimeTotal += userPath.back()->getDist();
      res.insert(res.end(), ++userPath.begin(), userPath.end());
      resIt = res.end();
      advance(resIt, -2);
    }

    Vertex<idNode> *debugNode = *resIt;  // DEBUG
  }

  /** append path to final destination **/
  graph.dijkstraShortestPath(res.back()->getInfo());
  list<Vertex<idNode> *> finalPath =
      graph.getPath(res.back()->getInfo(), driver.endNode);
  if (finalPath.size() == 0) {
    res.clear();
    return res;
  }

  res.insert(res.end(), ++finalPath.begin(), finalPath.end());
  return res;
}
