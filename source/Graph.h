/*
 * Graph.h
 */
#ifndef GRAPH_H_
#define GRAPH_H_

#include <iostream>
#include <vector>
#include <queue>
#include <list>
#include <limits>
#include <cmath>
#include "MutablePriorityQueue.h"

template <class T> class Edge;
template <class T> class Graph;
template <class T> class Vertex;

#define INF std::numeric_limits<double>::max()

/************************* Vertex  **************************/

template <class T>
class Vertex {
	T info;                // contents
	std::vector<Edge<T> > adj;  // outgoing edges
	bool visited;          // auxiliary field
	double dist = 0;
	Vertex<T> *path = NULL;
	int queueIndex = 0; 		// required by MutablePriorityQueue

	bool processing = false;
	void addEdge(Vertex<T> *dest, double w);

public:
	Vertex(T in);
	bool operator<(Vertex<T> & vertex) const; // // required by MutablePriorityQueue
	T getInfo() const;
	double getDist() const;
	Vertex* getPath() const;
	Vertex* getNearestVertex() const;
	friend class Graph<T>;
	friend class MutablePriorityQueue<Vertex<T>>;
};


template <class T>
Vertex<T>::Vertex(T in): info(in) {}

/*
 * Auxiliary function to add an outgoing edge to a vertex (this),
 * with a given destination vertex (d) and edge weight (w).
 */
template <class T>
void Vertex<T>::addEdge(Vertex<T> *d, double w) {
	adj.push_back(Edge<T>(d, w));
}

template <class T>
bool Vertex<T>::operator<(Vertex<T> & vertex) const {
	return this->dist < vertex.dist;
}

template <class T>
T Vertex<T>::getInfo() const {
	return this->info;
}

template <class T>
double Vertex<T>::getDist() const {
	return this->dist;
}

template <class T>
Vertex<T> *Vertex<T>::getPath() const {
	return this->path;
}

template <class T>
Vertex<T> *Vertex<T>::getNearestVertex() const {
	if (adj.size() == 0)
		return NULL;
	double adjDist = INF;
	Vertex<T> *nearest;
	for (Edge<T> edge : adj){
		if (edge.weight < adjDist){
			nearest = edge.dest;
			adjDist = edge.weight;
		}
	}
	return nearest;
}

/********************** Edge  ****************************/

template <class T>
class Edge {
	Vertex<T> *dest;      // destination vertex
	double weight;         // edge weight
public:
	Edge(Vertex<T> *dest, double w);
	friend class Graph<T>;
	friend class Vertex<T>;
};

template <class T>
Edge<T>::Edge(Vertex<T> *d, double w): dest(d), weight(w) {}


/*************************** Graph  **************************/

template <class T>
class Graph {
	std::vector<Vertex<T> *> vertexSet;    // vertex set

public:
	Vertex<T> *findVertex(const T &in) const;
	bool addVertex(const T &in);
	bool addEdge(const T &sourc, const T &dest, double w);
	int getNumVertex() const;
	std::vector<Vertex<T> *> getVertexSet() const;

	void dijkstraShortestPath(const T &s);
	std::list<Vertex<T>*> getPath(const T &origin, const T &dest);
	void print() const; //TEMP DEBUG
};

template <class T>
int Graph<T>::getNumVertex() const {
	return vertexSet.size();
}

template <class T>
std::vector<Vertex<T> *> Graph<T>::getVertexSet() const {
	return vertexSet;
}

/*
 * Auxiliary function to find a vertex with a given content.
 */
template <class T>
Vertex<T> * Graph<T>::findVertex(const T &in) const {
	for (auto v : vertexSet)
		if (v->info == in)
			return v;
	return NULL;
}

/*
 *  Adds a vertex with a given content or info (in) to a graph (this).
 *  Returns true if successful, and false if a vertex with that content already exists.
 */
template <class T>
bool Graph<T>::addVertex(const T &in) {
	if ( findVertex(in) != NULL)
		return false;
	vertexSet.push_back(new Vertex<T>(in));
	return true;
}

/*
 * Adds an edge to a graph (this), given the contents of the source and
 * destination vertices and the edge weight (w).
 * Returns true if successful, and false if the source or destination vertex does not exist.
 */
template <class T>
bool Graph<T>::addEdge(const T &sourc, const T &dest, double w) {
	auto v1 = findVertex(sourc);
	auto v2 = findVertex(dest);
	if (v1 == NULL || v2 == NULL)
		return false;
	v1->addEdge(v2,w);
	return true;
}


/**************** Single Source Shortest Path algorithms ************/

template<class T>
void Graph<T>::dijkstraShortestPath(const T &origin) {
	MutablePriorityQueue <Vertex<T>> vertexQueue;
	/**
	 * set every vertex distance to infinity
	 */
	for (Vertex<T> *vertex : vertexSet)
		vertex->dist = INF;
	/**
	 * initiate origin vertex and set all others to infinite distance
	 * add origin vertex as the start point of the vertex queue
	 */
	Vertex<T> *originVertex = findVertex(origin);
	originVertex->dist = 0;
	originVertex->path = originVertex;
	vertexQueue.insert(originVertex);
	/**
	 * check every path until the queue is empty 
	 */
	while(!vertexQueue.empty()){
		Vertex<T> *minVertex = vertexQueue.extractMin();

		for (Edge<T> adjacentEdge: minVertex->adj){
			Vertex<T> *adjacentVertex = adjacentEdge.dest;
			double currentPathDistance = minVertex->dist + adjacentEdge.weight;
			double adjacentVertexDistance = adjacentVertex->dist;
			/**
			 * update adjacent vertex if the current path has less distance than the previous paths
			 */ 
			if (adjacentVertexDistance > currentPathDistance){
				adjacentVertex->dist = currentPathDistance;
				adjacentVertex->path = minVertex;
				/**
				 * if the adjacent vertex distance is infinity add to queue
				 * else update the adjacent vertex position in queue to match the new distance
				 */ 

				if (adjacentVertexDistance == INF) 
					vertexQueue.insert(adjacentVertex); 
				else vertexQueue.decreaseKey(adjacentVertex);
			}
		}
	}
}

template<class T>
std::list<Vertex<T>*> Graph<T>::getPath(const T &origin, const T &dest){
	std::list<Vertex<T>*> res;
	this->dijkstraShortestPath(origin);
	Vertex<T> *originVertex = findVertex(origin);
	Vertex<T> *tempVertex = findVertex(dest);
	while (tempVertex != NULL && tempVertex != originVertex){
		res.push_front(tempVertex);
		tempVertex = tempVertex->getPath();
	}
	if (tempVertex == NULL)
		res.clear();
	else res.push_front(tempVertex);

	return res;
}




template<class T>
void Graph<T>::print() const{
	std::cout << "Node   Weight   Parent\n";

	for (Vertex<T> *vertex : vertexSet){
		std::string parent = "NULL";
		if (vertex->path != NULL)
			parent = vertex->path->info;
		std::cout << vertex->info << "         " << vertex->dist << "         " << parent << std::endl;
	}
}

#endif /* GRAPH_H_ */
