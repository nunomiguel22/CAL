/*
 * Graph.h
 */
#ifndef GRAPH_H_
#define GRAPH_H_

#include <cmath>
#include <iostream>
#include <limits>
#include <list>
#include <queue>
#include <vector>
#include "MutablePriorityQueue.h"

template <class T>
class Edge;
template <class T>
class Graph;
template <class T>
class Vertex;

#define INF std::numeric_limits<double>::max()

/************************* Vertex  **************************/

template <class T>
class Vertex {
 private:
  T info;                    // contents
  std::vector<Edge<T>> adj;  // outgoing edges
  bool visited;              // auxiliary field
  double dist = 0;
  Vertex<T> *path = NULL;
  int queueIndex = 0;  // required by MutablePriorityQueue

  bool processing = false;
  void addEdge(Vertex<T> *dest, double w);

 public:
  Vertex(T in);
  bool operator<(
      Vertex<T> &vertex) const;  // // required by MutablePriorityQueue
  T getInfo() const;
  double getDist() const;
  Vertex *getPath() const;
  Vertex *getNearestVertex() const;
  std::vector<Edge<T>> getAdjEdges() const;
  friend class Graph<T>;
  friend class MutablePriorityQueue<Vertex<T>>;
};

template <class T>
Vertex<T>::Vertex(T in) : info(in) {}

/*
 * Auxiliary function to add an outgoing edge to a vertex (this),
 * with a given destination vertex (d) and edge weight (w).
 */
template <class T>
void Vertex<T>::addEdge(Vertex<T> *d, double w) {
  adj.push_back(Edge<T>(d, w));
}

template <class T>
bool Vertex<T>::operator<(Vertex<T> &vertex) const {
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
std::vector<Edge<T>> Vertex<T>::getAdjEdges() const {
  return this->adj;
}

template <class T>
Vertex<T> *Vertex<T>::getNearestVertex() const {
  if (adj.size() == 0) return NULL;
  double adjDist = INF;
  Vertex<T> *nearest;
  for (Edge<T> edge : adj) {
    if (edge.weight < adjDist) {
      nearest = edge.dest;
      adjDist = edge.weight;
    }
  }
  return nearest;
}

/********************** Edge  ****************************/

template <class T>
class Edge {
 private:
  Vertex<T> *dest;  // destination vertex
  double weight;    // edge weight
 public:
  Edge(Vertex<T> *dest, double w);
  friend class Graph<T>;
  friend class Vertex<T>;
  Vertex<T> *getDest() const;
  double getWeight() const;
};

template <class T>
Edge<T>::Edge(Vertex<T> *d, double w) : dest(d), weight(w) {}

template <class T>
Vertex<T> *Edge<T>::getDest() const {
  return dest;
}

template <class T>
double Edge<T>::getWeight() const {
  return weight;
}

/*************************** Graph  **************************/
template <class T>
class Graph {
 private:
  std::vector<Vertex<T> *> vertexSet;  // vertex set
  unsigned int numberOfedges = 0;
  void depthFirstSearch(Vertex<T> *vertex, std::vector<T> &result);

 public:
  ~Graph<T>();
  Vertex<T> *findVertex(const T &in) const;
  Edge<T> findEdge(const T &sourc, const T &dest);
  bool addVertex(const T &in);
  bool addEdge(const T &sourc, const T &dest, double w);
  unsigned int vertexSetSize() const;
  unsigned int edgeCount() const;
  std::vector<Vertex<T> *> getVertexSet() const;
  /** path **/
  void dijkstraShortestPath(const T &s);
  std::list<Vertex<T> *> getPath(const T &origin, const T &dest);
  /** connectivity **/
  std::vector<T> depthFirstSearch();
  bool isStronglyConnected();
};
/** METHODS **/
/*
 * Graph destructor
 */
template <class T>
Graph<T>::~Graph<T>() {
  for (Vertex<T> *vertex : vertexSet) delete vertex;
}

/*
 * Auxiliary function to find a vertex with a given content.
 */
template <class T>
Vertex<T> *Graph<T>::findVertex(const T &in) const {
  for (auto v : vertexSet)
    if (v->info == in) return v;
  return NULL;
}
/*
 * Auxiliary function to find an edge between two vertices.
 * if no such edge is found an empty edge is returned
 */
template <class T>
Edge<T> Graph<T>::findEdge(const T &sourc, const T &dest) {
  Vertex<T> *origin = findVertex(sourc);
  Vertex<T> *destination = findVertex(dest);
  Edge<T> edge(NULL, 0);

  if (origin == NULL || destination == NULL) return edge;

  for (Edge<T> adjEdge : origin->adj)
    if (adjEdge.dest->info == dest) edge = adjEdge;

  return edge;
}
/*
 *  Adds a vertex with a given content or info (in) to a graph (this).
 *  Returns true if successful, and false if a vertex with that content already
 * exists.
 */
template <class T>
bool Graph<T>::addVertex(const T &in) {
  if (findVertex(in) != NULL) return false;
  vertexSet.push_back(new Vertex<T>(in));
  return true;
}
/*
 * Adds an edge to a graph (this), given the contents of the source and
 * destination vertices and the edge weight (w).
 * Returns true if successful, and false if the source or destination vertex
 * does not exist.
 */
template <class T>
bool Graph<T>::addEdge(const T &sourc, const T &dest, double w) {
  auto v1 = findVertex(sourc);
  auto v2 = findVertex(dest);
  if (v1 == NULL || v2 == NULL) return false;
  v1->addEdge(v2, w);
  ++numberOfedges;
  return true;
}
/*
 * Returns the number of vertices in the graph
 */
template <class T>
unsigned int Graph<T>::vertexSetSize() const {
  return vertexSet.size();
}
/*
 * Returns the number of total edges in the graph
 */
template <class T>
unsigned int Graph<T>::edgeCount() const {
  return numberOfedges;
}
/*
 * Returns a vector with all vertices on the graph
 */
template <class T>
std::vector<Vertex<T> *> Graph<T>::getVertexSet() const {
  return vertexSet;
}

/**************** dijkstra shortest path algorithm ************/

template <class T>
void Graph<T>::dijkstraShortestPath(const T &origin) {
  MutablePriorityQueue<Vertex<T>> vertexQueue;
  /**
   * set every vertex distance to infinity and path to null
   */
  for (Vertex<T> *vertex : vertexSet) {
    vertex->dist = INF;
    vertex->path = NULL;
  }
  /**
   * initiate origin vertex and set all others to infinite distance
   * add origin vertex as the start point of the vertex queue
   */
  Vertex<T> *originVertex = findVertex(origin);
  if (originVertex == NULL) return;

  originVertex->dist = 0;
  originVertex->path = originVertex;
  vertexQueue.insert(originVertex);
  /**
   * check every path until the queue is empty
   */
  while (!vertexQueue.empty()) {
    Vertex<T> *minVertex = vertexQueue.extractMin();

    for (Edge<T> adjacentEdge : minVertex->adj) {
      Vertex<T> *adjacentVertex = adjacentEdge.dest;
      double currentPathDistance = minVertex->dist + adjacentEdge.weight;
      double adjacentVertexDistance = adjacentVertex->dist;
      /**
       * update adjacent vertex if the current path has less distance than the
       * previous paths
       */
      if (adjacentVertexDistance > currentPathDistance) {
        adjacentVertex->dist = currentPathDistance;
        adjacentVertex->path = minVertex;
        /**
         * if the adjacent vertex distance is infinity add to queue
         * else update the adjacent vertex position in queue to match the new
         * distance
         */

        if (adjacentVertexDistance == INF)
          vertexQueue.insert(adjacentVertex);
        else
          vertexQueue.decreaseKey(adjacentVertex);
      }
    }
  }
}
/*
 * Returns the best path between two vertices.
 *
 * Calling dijkstraShortestPath on the origin vertex is needed first to get a
 * correct result
 *
 * The result is given in the form of an ordered list of vertexfrom origin to
 * destination
 *
 * If no path exists or the input value are invalid an empty list is
 * returned
 */
template <class T>
std::list<Vertex<T> *> Graph<T>::getPath(const T &origin, const T &dest) {
  std::list<Vertex<T> *> res;
  Vertex<T> *originVertex = findVertex(origin);
  if (originVertex == NULL) return res;
  if (originVertex->dist != 0) return res;

  Vertex<T> *tempVertex = findVertex(dest);
  while (tempVertex != NULL && tempVertex != originVertex) {
    res.push_front(tempVertex);
    tempVertex = tempVertex->getPath();
  }
  if (tempVertex == NULL)
    res.clear();
  else
    res.push_front(tempVertex);

  return res;
}

/** depth first search algorithm **/
template <class T>
void Graph<T>::depthFirstSearch(Vertex<T> *vertex, std::vector<T> &result) {
  vertex->visited = true;
  result.push_back(vertex->info);

  for (Edge<T> edge : vertex->getAdjEdges()) {
    if (!edge.dest->visited) {
      depthFirstSearch(edge.dest, result);
    }
  }
}

template <class T>
std::vector<T> Graph<T>::depthFirstSearch() {
  /** reset all vertices **/
  std::vector<T> result;
  for (Vertex<T> *vertex : vertexSet) vertex->visited = false;

  for (Vertex<T> *vertex : vertexSet) {
    if (!vertex->visited) {
      depthFirstSearch(vertex, result);
    }
  }
  return result;
}

/** connectivity check using dfs algorithm **/
template <class T>
bool Graph<T>::isStronglyConnected() {
  if (this->depthFirstSearch().size() != this->vertexSetSize()) return false;

  /** invert graph **/
  Graph<T> gr;
  for (Vertex<T> *vertex : vertexSet) {
    for (Edge<T> edge : vertex->getAdjEdges()) {
      T originVertex = vertex->getInfo();
      T destVertex = edge.getDest()->getInfo();

      gr.addVertex(originVertex);
      gr.addVertex(destVertex);
      gr.addEdge(destVertex, originVertex, edge.getWeight());
    }
  }

  if (gr.depthFirstSearch().size() != vertexSetSize()) return false;

  return true;
}

#endif /* GRAPH_H_ */
