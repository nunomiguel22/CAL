#include "menu.h"
std::vector<User *> users;
using namespace std;

void mainMenu(Graph<idNode> graph) {
	
while(true){
	SetWindow(100, 50);
	ClearScreen();
	printtitle();

	cout << endl;
	cout << " 1 - Clients Management" << endl;
	cout << " 2 - Trip Management" << endl;
	cout << " 3 - " << endl;
	cout << " 4 - Exit" << endl;
	int opcao = 0;

	cout << endl;
	cout << "Choose an option: ";
	while (opcao < 1 || opcao > 4) {
		if (cin >> opcao) {

			switch (opcao) {
			case 1:
				usersMenu(graph);
				break;
			case 2:
				//routeMenu();
				break;
			case 3:
				break;
			case 4:
				exit();
				break;
			default:
				cout << "Invalid option. Please, choose another option: ";
			}
		}

		else {
			cin.clear();
			cin.ignore(10000, '\n');
			cout << "Invalid option. Please, choose another option: ";
		}
	}
}

}

void usersMenu(Graph<idNode> graph) {

	SetWindow(100, 50);
	ClearScreen();
	printtitle();


	cout << " 1 - Create new Client" << endl;
	cout << " 2 - Remove Client" << endl;
	cout << " 3 - See All Clients" << endl;
	cout << " 4 - Return" << endl;
	cout << " 5 - Exit" << endl;

	int opcao = 0;
	cout << endl;
	cout << "Choose an option: ";
	while (opcao < 1 || opcao > 5) {
		if (cin >> opcao) {

			switch (opcao) {
			case 1:
				createNewUser(graph);
				goBack(graph);
				break;
			case 2:
				//removeUser();
				goBack(graph);
				break;
			case 3:
				//showAllUsers();
				goBack(graph);
				break;
			case 4:
				mainMenu(graph);
				break;
			case 5:
				exit();
				break;
			default:
				cout << "Invalid option. Please, choose another option: ";
			}
		} else {
			cin.clear();
			cin.ignore(10000, '\n');
			cout << "Invalid option. Please, choose another option: ";
		}
	}

}

/*
void routeMenu() {

	SetWindow(100, 50);
	ClearScreen();
	printtitle();

	cout << " 1 - Create route" << endl;
	cout << " 2 - Find Ride" << endl;
	cout << " 3 - See All Clients" << endl;
	cout << " 4 - Return" << endl;
	cout << " 5 - Exit" << endl;

	int opcao = 0;
	cout << endl;
	cout << "Choose an option: ";
	while (opcao < 1 || opcao > 5) {
		if (cin >> opcao) {

			switch (opcao) {
			case 1:
				createNewRoute();
				goBack();
				break;
			case 2:
				findRide();
				goBack();
				break;
			case 3:
				//seeAllSomething("clients");
				goBack();
				break;
			case 4:
				mainMenu(graph);
				break;
			case 5:
				exit();
				break;
			default:
				cout << "Invalid option. Please, choose another option: ";
			}
		} else {
			cin.clear();
			cin.ignore(10000, '\n');
			cout << "Invalid option. Please, choose another option: ";
		}
	}
}*/

void exit() {

	SetWindow(100, 50);
	ClearScreen();
	printtitle();

	string opcao;
	cout << endl;
	cout << "Do you wish to save your changes? (Y/N): ";
	cin.clear();
	cin.ignore(10000, '\n');
	while (opcao != "y" && opcao != "Y" && opcao != "n" && opcao != "N") {
		getline(cin, opcao);
		if (opcao == "y" || opcao == "Y") {
			//SAVE
			cout << "\nSaved changes! Leaving... \n";
			sleep(1);
			break;
		}
		if (opcao == "n" || opcao == "N") {
			cout << "\nLeaving...\n";
			sleep(1);
			break;
		} else {
			cout << "Invalid option. Please, choose another option: ";
		}
	}
	exit(0);
}

void goBack(Graph<idNode> graph) {

	SetWindow(100, 50);
	ClearScreen();
	printtitle();

	cout << endl << endl;
	cout << " 1 - Return to the Main Menu" << endl;
	cout << " 2 - Exit" << endl;

	int opcao = 0;
	cout << endl;
	cout << "Choose an option: ";
	while (opcao < 1 || opcao > 2) {
		if (cin >> opcao) {
			switch (opcao) {
			case 1:
				mainMenu(graph);
				break;
			case 2:
				exit();
				break;
			default:
				cout << "Invalid option. Please, choose another option: ";
			}"Writing this to a file.\n";
		} else {
			cin.clear();
			cin.ignore(10000, '\n');
			cout << "Invalid option. Please, choose another option: ";
		}
	}
}

void createNewUser(Graph<idNode> graph) {

	SetWindow(100, 50);
	ClearScreen();
	printtitle();

	cout << endl;

	Route route;
	string name, node, nodeA,tolerance;
	int  depTime, arrTime;
	bool smoke, hasCar;
	string option, car;
	int intDep;
	int intArr;
	int n;
	hours hour, hourA;
	minutes minutesA, minutes, tol;
	char* idNode;
	 int long origin, destiny;

	cout << "Insert the username of the new User: ";
	cin.ignore();
	getline(cin, name);

	cout << "Insert the starting point of the new User: ";
	cin >> origin;	
	cout << origin << endl;
	route.startNode=origin;

	cout << "Insert the destiny point of the new User: ";
	cin >> destiny;
	cout << destiny << endl;
	route.endNode = destiny;
	
	cout << "Insert the departure hour the new User ( e.g 1000): ";
	cin >> intDep;
	minutes=intDep%100;
	hour=intDep/100;
	cout << intDep << endl;
	route.arrivalTime.hour=hour;
	route.arrivalTime.minute=minutes;
	

	cout << "Insert the arrival time the new User ( e.g 1000): ";
	cin >> intArr;
	minutesA= intArr % 100;
	hourA=intArr/100;
	route.arrivalTime.hour=hourA;
	route.arrivalTime.minute=minutesA;

	cout << "Insert the tolerance the new User (minutes): ";
	cin.ignore();
	getline(cin, tolerance);
	tol=stoi(tolerance);
	route.tolerance=tol;

/*
	cout << "Do you smoke? (Y/N) ";
	while (option != "y" && option != "Y" && option != "n" && option != "N") {
		getline(cin, option);
	

		if (option == "y" || option == "Y") {
			smoke=true;
			break;
		}
		if (option == "n" || option == "N") {
			smoke=false;
			break;
		} else {
			cout << "Invalid option. Please, choose another: ";
		}
	}
*/
	cout << "Do you have a car? (Y/N) ";
	while (car != "y" && car != "Y" && car != "n" && car != "N") {
		getline(cin, car);

		if (car == "y" || car == "Y") {
			User driver(route, "testDriver", graph);
			driverSetUp(driver,graph);
			break;
		}
		if (car == "n" || car == "N") {
			User user(route, name, graph);
			users.push_back(&user);
			hasCar=false;
			break;
		} else {
			cout << "Invalid option. Please, choose another: ";
		}
	}

/*	ofstream myfile;
  	myfile.open ("clients.txt");
  	myfile << tmp << "," << name  << "," << std::noboolalpha << smoke 
	<< "," << std::noboolalpha << hasCar << endl;
  	myfile.close();

	id = stoi(tmp);*/
	
	
	cout << "\nUser added with success!" << endl << endl;

	sleep(20);
}
/*
void createNewRoute() {

	SetWindow(100, 50);
	ClearScreen();
	printtitle();

	string id,destiny, origin,seats,departureTime;

	cout << endl << endl;
	cout << "-----------" << endl;
	cout << "RideShare" << endl;
	cout << "-----------" << endl;
	cout << endl << endl;
	cin.clear();
	cin.ignore(10000, '\n');
	cout << "Where are you going? ";
	getline(cin, destiny);

	cout << "Insert your id";
	getline(cin, id);
    

	cout << "Where are you starting your trip? ";
	getline(cin, origin);
    
	cout << "How many available seats do you have? ";
	getline(cin, seats);

	cout << "When (e.g 9:00)? ";
	getline(cin, departureTime);
	
	//User driver(origin,destiny,graph);
	
	cout << "\Route added with success!" << endl << endl;

	sleep(1);
}

void findRide() {

	SetWindow(100, 50);
	ClearScreen();
	printtitle();

	string id,destiny, origin,toleranceTime,departureTime;

	cin.clear();
	cin.ignore(10000, '\n');

	cout << "Insert your id";
	getline(cin, id);

	cout << "Where do you wanna go? ";
	getline(cin, destiny);

	cout << "Where to pick you from? ";
	getline(cin, origin);
    
	cout << "When (e.g 9:00)? ";
	getline(cin, departureTime);
	
	cout << "Insert the tolerance time of the travel: (minutes) ";
	getline(cin, toleranceTime);

	//User user(origin,destiny,graph);
	
	//users.push_back(user);

	cout << "\Route added with success!" << endl << endl;

	sleep(1);
}*/
/*
void removeUser(){

	SetWindow(100, 50);
	ClearScreen();
	printtitle();

	cout << "Insert the id of the User to be removed: ";
	
	cin.clear();
	int uniqueID;
	string tempID;
	bool exists = false;
	cin.ignore(10000, '\n');
	getline(cin, tempID);

	uniqueID = stoi(tempID);


		for (unsigned int i = 0; i < users.size();i++) {

			if (users.at(i)->getId()== uniqueID) {
				users.erase(users.begin()+i);
				exists=true;
			}
		}
		if(!exists)
			cout << "User does't exist\n";
	
	return;
}*/
/*
void showAllUsers(){
	for(unsigned int i = 0; i < users.size(); i++)
		cout << "User: " << users.at(i)->getUserName() << ", with id = " << users.at(i)->getId() << endl;
}
*/
void printtitle(){
                                                                             
cout << ",------. ,--.,------.  ,------. ,---.  ,--.  ,--.  ,---.  ,------. ,------. " << endl <<
		"|  .--. '|  ||  .-.  | |  .---''   .-' |  '--'  | |  O  | |  .--. '|  .---' " << endl << 
		"|  '--'.'|  ||  |  | : |  `--, `.  `-. |  .--.  ||  .-.  ||  '--'.'|  `--, " << endl << 
		"|  | |  ||  ||  '--' | |  `---..-'    ||  |  |  ||  | |  ||  ||  | |  `---. "<< endl << 
		"`--' '--'`--'`-------' `------'`-----' `--'  `--'`--' `--'`--' '--'`------' "<< endl;
                                                                                                                                 
}

void ClearScreen()
	{
		cout << "\033[2J\033[1;1H";
		cout << "\033[2J\033[1;1H";
		cout << "\033[2J\033[1;1H";
		cout << "\033[2J\033[1;1H";
	}

	bool SetWindow(const int& width, const int& height)
	{
		string resul = "\e[8;";
		resul += to_string(height);
		resul += ";";
		resul += to_string(width);
		resul += "t";
		cout << resul;

		return true;
	}

	void driverSetUp(User driver, Graph<idNode> graph){
		cout << endl;
	cout << " 1 - Fast route" << endl;
	cout << " 2 - Best route" << endl;
	cout << " 3 - Exit" << endl;
	int opcao = 0;

	double tripTime;
	std::vector<User *> passangers;
	std::list<Vertex<idNode> *> result;

	cout << endl;
	cout << "Choose an option: ";
	while (opcao < 1 || opcao > 3) {
		if (cin >> opcao) {
			switch (opcao) {
			case 1:
				result = rideshareFast(graph, users, driver, tripTime, passangers);
				break;
			case 2:
				result = rideshareBest(graph, users, driver, tripTime, passangers);
				break;
			case 3:
				exit();
				break;
			default:
				cout << "Invalid option. Please, choose another option: ";
			}
		}

		else {
			cin.clear();
			cin.ignore(10000, '\n');
			cout << "Invalid option. Please, choose another option: ";
		}
	}
	cout << "HERE" << endl;
	printPath(passangers, tripTime, result, driver);
	Reader r;
	r.showRoute(result,driver,passangers);

}
