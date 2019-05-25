#include "Reader.h"
#include "graphviewer.h"
#include "Graph.h"
#include "math.h"


GraphViewer * graphViewer;

using namespace std;

Reader::Reader() {}

int node = 0;

void Reader::loadEdges() {

	char garbage;
	int origin;
	int destiny;
	string line;

	// open a file in read mode.
	ifstream infile;
	infile.open("T01/Porto/T01_edges_Porto.txt");
	if (infile.is_open()) {
		getline(infile, line);
		while (getline(infile, line)) {
		node++;
			istringstream edge(line);
			edge >> garbage;

			edge >> origin;
			edge >> garbage;

			edge >> destiny;
			edge >> garbage;

		//	graphViewer->addEdge(node,origin,destiny,EdgeType::UNDIRECTED);
		/*	this->addEdges(origin,destiny);
			this->addOrigin(origin);
			this->addDestiny(destiny);*/
		}
		// close the opened file.
		infile.close();
	} else {
		cerr << "File not found!\n";
	}
	infile.close();

}

void Reader::loadLatLon() {

	char garbage;
	int latitude;
	int longitude;
	int id;
	string line;
	// open a file in read mode.
	ifstream infile;
	infile.open("T01/Porto/T01_nodes_lat_lon_Porto.txt");
	if (infile.is_open()) {

		while (getline(infile, line)) {

			istringstream edge(line);

			edge >> id;
			edge >> garbage;

			edge >> latitude;
			edge >> garbage;

			edge >> longitude;
			edge >> garbage;
		}
		// close the opened file.
		infile.close();
	} else {
		cerr << "File not found!\n";
	}
	//cout << this->getLatLon().size();

}

void Reader::loadXY() {

	char garbage;
	double x;
	double y;
	int id;
	string line;

	
	// open a file in read mode.
	ifstream infile;
	infile.open("T01/Porto/T01_nodes_X_Y_Porto.txt");
	if (infile.is_open()) {
		getline(infile, line);
		while (getline(infile, line)) {
			istringstream node(line);
			
			node >> garbage;

	    	node >> id;
			node >> garbage;

	    	node >> x;
			node >> garbage;

			node >> y;
			node >> garbage;

		x = x + 0.5 - (x<0);
		int xInt = (int)x;
		y = y + 0.5 - (y<0);
		int yInt = (int)y;
		//	graphViewer->addNode(id,xInt,yInt);

		addNodeX(id, xInt);
		addNodeY(id, yInt);


		}
		infile.close();
	} else {
		cerr << "File not found!\n";
	}
	
}

void Reader::loadTags() {

	int size;
	string tag;
	int numberOfTags;
	int id;
	string line;
	// open a file in read mode.
	ifstream infile;
	infile.open("T01_tags_Porto.txt");
	if (infile.is_open()) {
		getline(infile, line);

		while (getline(infile, line)) {
			tag = line;
			istringstream node(line);

			node >> size;

			for (int i = 0; i < size; i++) {
				node >> id;
			//	graphViewer->setVertexLabel(id,tag);
			}
		
		}
		// close the opened file.
		infile.close();
	} else {
		cerr << "File not found!\n";
	}

}

void Reader::openMap() {

	graphViewer = new GraphViewer(1000, 1000, true);

	graphViewer->createWindow(1000, 1000);

	graphViewer->defineVertexColor("blue");
	graphViewer->defineEdgeColor("black");

}

double distanceBetweenTwoPoints(double x1, double y1, double x2, double y2){
return sqrt(pow(x1 - x2, 2) + pow(y1 - y2, 2));
}


void Reader::showRoute(list<Vertex<idNode> *> result,User driver,vector<User *> users) {

	graphViewer= new GraphViewer(700, 700, true);
	graphViewer->defineVertexColor("blue");
	graphViewer->defineEdgeColor("black");
	//graphViewer->setBackground("map.jpg");
	graphViewer->createWindow(700, 700);
	
		vector<int> ids;
		double x,y;
		int id;
		for (Vertex<idNode>* vertex : result) {
				id = vertex->getInfo();
				x = this->getX(id);
				y = this->getY(id);
				
				if (vertex->getInfo()==driver.getRoute().startNode){
					 graphViewer->setVertexColor(id, "green");
					 graphViewer->setVertexLabel(id,"Driver departure");
				}
				if (vertex->getInfo()==driver.getRoute().endNode){
					 graphViewer->setVertexColor(id, "green");
					 graphViewer->setVertexLabel(id,"Driver destination");
				}
		for(unsigned int i=0; i < users.size();i++){
			if(vertex->getInfo()==users.at(i)->getRoute().startNode){
				string tag = users.at(i)->getName() + " pickup";
				graphViewer->setVertexColor(id, "yellow");
				graphViewer->setVertexLabel(id,tag);
			}
			if(vertex->getInfo()==users.at(i)->getRoute().endNode){
				string tag = users.at(i)->getName() + " destination";
				graphViewer->setVertexColor(id, "yellow");
				graphViewer->setVertexLabel(id,tag);
			}
		}
		graphViewer->addNode(id,x,y);
		ids.push_back(id);
	}
	for(unsigned int i = 0; i < ids.size()-1;i++){
		graphViewer->addEdge(i,ids.at(i),ids.at(i+1),EdgeType::UNDIRECTED);
	}		
	graphViewer->rearrange();
}

int Reader::getX(int id){
	for(int i=0; i < this->nodeX.size();i++){
		if(this->nodeX.at(i).first==id){
			return (this->getNodeX().at(i).second);
		}
	}
}

int Reader::getY(int id){
	bool exists =false;
	int y;
	for(int i=0; i < this->getNodeY().size();i++)
		if(this->getNodeY().at(i).first==id){
			y= (this->getNodeY().at(i).second);
			exists=true;
		}
		if(exists)
		return y;
		else return -1;
}

/*
41.1588228, -8.6106784
41.1572106, -8.6113301
41.1572505, -8.6099698
41.1573499, -8.6091622
41.1589843, -8.6083976
41.1601187, -8.6079182
41.1602311, -8.6086654
41.1604412, -8.6099511
41.1603264, -8.6098901
41.1587297, -8.6099366
41.1574804, -8.6099668
41.1590119, -8.6090578
*/