#include <iostream>
#include <string>
#include <vector>
#include <fstream>
#include <sstream>
#include <cstdio>
#include <utility> 

#include "graphviewer.h"
#include "OSMServices.h"
#include "User.h"


class Reader{
private:
	vector<pair<string,string>> edges;
	vector<string> origins;
	vector<string> destinies;
	vector<pair<int,int>> nodeX;
	vector<pair<int,int>> nodeY;

//	vector<string> latLon;
//	vector<string> xy;
//	vector<pair<string,int>> tagsID;
//	vector <string> tags;


public:
	Reader();
	void loadEdges();
	void loadLatLon();
	void loadXY();
	void loadTags();
	void openMap();
	//void showRoute(vector<int> path);


	void addNodeX(int id, int x){nodeX.push_back(make_pair(id,x));}
	void addNodeY(int id, int y){nodeY.push_back(make_pair(id,y));}
	vector<pair<int,int>> getNodeX(){return this->nodeX;}
	vector<pair<int,int>> getNodeY(){return this->nodeY;}
	
	int getX(int id);
	int getY(int id);
	void showRoute(list<Vertex<idNode> *> result,User driver,vector<User *> users);


};



/*	void addEdges(string origin, string destiny){edges.push_back(make_pair(origin,destiny));}
	void addOrigin(string origin){origins.push_back(origin);}
	void addDestiny(string destiny){destinies.push_back(destiny);}

	vector<pair<string,string>> getEdges(){return this->edges;}
	vector<string> getOrigins(){return this->origins;}
	vector<string> getDestiny(){return this->destinies;}

	void addLatLon(string latlon){latLon.push_back(latlon);}
	vector<string> getLatLon(){return latLon;}

	void addXY(string xY){xy.push_back(xY);}
	vector<string> getXY(){return xy;}

	void addTagId(string tag, int id){tagsID.push_back(make_pair(tag,id));}
	void addTag(string tag){tags.push_back(tag);}
	vector<pair<string,int>> getTagsId(){return tagsID;}
	vector<string> getTags(){return tags;}*/