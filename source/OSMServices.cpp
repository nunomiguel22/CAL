#include "OSMServices.h"
#include "Graph.h"

using namespace std;

OSMCollection OSMServices::extractOSMCollectionByCity(const std::string& city) {
  OSMCollection osmCol;
  map<idNode, Position> nodesPosition = this->getNodesXYPosition(city);

  // TODO: add tags to nodes
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
  // TODO: use the first line to check if the number of edges is correct
  nodesXY.erase(nodesXY.begin());

  for (string& node : nodesXY) {
    node.erase(node.begin());
    node.erase(node.end() - 1, node.end());
    vector<string> nodeAndPosition = nodes.explode(',', node);
    idNode id = stoi(nodeAndPosition[0]);
    Position pos;
    pos.posLat = stod(nodeAndPosition[1]);
    pos.posLon = stod(nodeAndPosition[2]);

    nodesPositionMap.insert(std::pair<idNode, Position>(id, pos));
  }

  return nodesPositionMap;
}

vector<pair<idNode, idNode>> OSMServices::getEdges(const std::string& city) {
  vector<pair<idNode, idNode>> edgesPairs;
  string file = BASE_DIR + city + "/" + EDGES_FILE + city + FILE_EXT;
  FileManager edges(file);
  auto edgesInOut = edges.getVectorFileLines();
  // TODO: use the first line to check if the number of edges is correct
  edgesInOut.erase(edgesInOut.begin());

  for (string& edge : edgesInOut) {
    edge.erase(edge.begin());
    edge.erase(edge.end() - 1, edge.end());
    //}
    vector<string> edgePair = edges.explode(',', edge);
    idNode inNode = stoi(edgePair[0]);
    idNode outNode = stoi(edgePair[1]);

    edgesPairs.push_back(make_pair(inNode, outNode));
  }

  return edgesPairs;
}

void OSMServices::generateGraph(Graph<idNode>& graph,
                                OSMCollection& osmCollection) {
  for (auto& it : osmCollection.getNodeMap()) {
    graph.addVertex(it.first);
  }

  for (auto& it : osmCollection.getEdgesVector()) {
    hour travelTime = osmCollection.getEdgesTravelTime(it.first, it.second);
    graph.addEdge(it.first, it.second, travelTime);
  }
}
