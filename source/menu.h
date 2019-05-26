#include "Graph.h"
#include "User.h"
#include "osm/OSMServices.h"

void readUsers(std::vector<User *> &users, Graph<idNode> &graph);
void saveUsers(std::vector<User *> &users);
void addDriver(std::vector<User *> &users);
void removeDriver(std::vector<User *> &users);
void generatePathFast(Graph<idNode> &graph, std::vector<User *> &users);
void generatePathBest(Graph<idNode> &graph, std::vector<User *> &users);
void printGraphInfo(Graph<idNode> &graph);
void mainMenu(Graph<idNode> &graph, std::vector<User *> &users);
void createNewUser(Graph<idNode> &graph, std::vector<User *> &users);

void printTitle();
