#include "Graph.h"
#include "User.h"
#include "osm/OSMServices.h"

void readUsers(std::vector<User *> &users, Graph<idNode> &graph);
void saveUsers(std::vector<User *> &users);

void mainMenu(Graph<idNode> &graph, std::vector<User *> &users);
void createNewUser(Graph<idNode> &graph, std::vector<User *> &users);

void printtitle();
void driverSetUp(User &driver, Graph<idNode> &graph,
                 std::vector<User *> &users);

void exit();
