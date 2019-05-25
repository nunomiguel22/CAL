#include "Reader.h"
#include "Graph.h"
#include "OSMServices.h"
#include "rideshare.h"
#include "timeofday.h"

void mainMenu(Graph<idNode> graph);
void usersMenu(Graph<idNode> graph);
//void routeMenu();
void goBack(Graph<idNode> graph);
//void createNewRoute();
void createNewUser(Graph<idNode> graph);
//void showAllUsers();
//void removeUser();
//void findRide();
void printtitle();
void driverSetUp(User driver,Graph<idNode> graph);
void ClearScreen();
bool SetWindow(const int& width, const int& height);

void exit();