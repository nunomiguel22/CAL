#include "OSMServices.h"
#include "../Graph.h"

using namespace std;

OSMCollection OSMServices::extractOSMCollectionByCity(const std::string& city) {
  OSMCollection osmCol;
  map<idNode, Position> nodesPosition = this->getNodesXYPosition(city);

  for (auto& it : nodesPosition) {
    osmCol.addNode(OSMNode::builder{}
                       .addNodeId(it.first)
                       .addXcoord(it.second.posLat)
                       .addYcoord(it.second.posLon)
                       .build());
  }

  osmCol.setEdges(this->getEdges(city));

  return osmCol;
}

map<idNode, Position> OSMServices::getNodesXYPosition(const std::string& city) {
  map<idNode, Position> nodesPositionMap;
  string file = BASE_DIR + city + "/" + LAT_LON_FILE + city + FILE_EXT;
  FileManager nodes(file);
  auto nodesXY = nodes.getVectorFileLines();
  nodesXY.erase(nodesXY.begin());
  unsigned int nodeCount = 0;
  for (string& node : nodesXY) {
    ++nodeCount;
    node.erase(node.begin());
    node.erase(node.end() - 1, node.end());
    vector<string> nodeAndPosition = nodes.explode(',', node);
    idNode id = stoi(nodeAndPosition[0]);
    Position pos;
    pos.posLat = stod(nodeAndPosition[1]);
    pos.posLon = stod(nodeAndPosition[2]);
    nodesPositionMap.insert(std::pair<idNode, Position>(id, pos));
    if (nodeCount % 1000 == 0) std::cout << ".";
  }

  return nodesPositionMap;
}

vector<pair<idNode, idNode>> OSMServices::getEdges(const std::string& city) {
  vector<pair<idNode, idNode>> edgesPairs;
  string file = BASE_DIR + city + "/" + EDGES_FILE + city + FILE_EXT;
  FileManager edges(file);
  auto edgesInOut = edges.getVectorFileLines();
  edgesInOut.erase(edgesInOut.begin());

  unsigned int edgeCount = 0;
  for (string& edge : edgesInOut) {
    ++edgeCount;
    edge.erase(edge.begin());
    edge.erase(edge.end() - 1, edge.end());

    vector<string> edgePair = edges.explode(',', edge);
    idNode inNode = stoi(edgePair[0]);
    idNode outNode = stoi(edgePair[1]);

    edgesPairs.push_back(make_pair(inNode, outNode));
    if (edgeCount % 1000 == 0) std::cout << ".";
  }

  return edgesPairs;
}

void OSMServices::generateGraph(Graph<idNode>& graph,
                                OSMCollection& osmCollection) {
  unsigned int vertexCount = 0;
  for (auto& it : osmCollection.getNodeMap()) {
    ++vertexCount;
    graph.addVertex(it.first);
    if (vertexCount % 1000 == 0) std::cout << ".";
  }

  unsigned int edgeCount = 0;
  for (auto& it : osmCollection.getEdgesVector()) {
    ++edgeCount;
    hour travelTime = osmCollection.getEdgesTravelTime(it.first, it.second);
    graph.addEdge(it.first, it.second, travelTime);
    if (edgeCount % 1000 == 0) std::cout << ".";
  }
}
