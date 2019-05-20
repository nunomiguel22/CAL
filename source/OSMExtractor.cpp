#include <utility>

#include "OSMExtractor.h"

using namespace std;

OSMCollection OSMExtractor::extractOSMCollectionByCity(
    const std::string& city) {
  OSMCollection osmCol;
  map<idNode, Position> nodesPosition = this->getNodesXYPosition(city);

  // TODO: add tags to nodes
  for (auto& it : nodesPosition) {
    osmCol.addNode(OSMNode::builder{}
                       .addNodeId(it.first)
                       .addXcoord(it.second.posX)
                       .addYcoord(it.second.posY)
                       .build());
  }

  osmCol.setEdges(this->getEdges(city));

  return osmCol;
}

map<idNode, Position> OSMExtractor::getNodesXYPosition(
    const std::string& city) {
  map<idNode, Position> nodesPositionMap;
  string file = BASE_DIR + city + "/" + NODES_X_Y_FILE + city + FILE_EXT;
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
    pos.posX = stod(nodeAndPosition[1]);
    pos.posY = stod(nodeAndPosition[2]);

    nodesPositionMap.insert(std::pair<idNode, Position>(id, pos));
  }

  return nodesPositionMap;
}

vector<pair<idNode, idNode>> OSMExtractor::getEdges(const std::string& city) {
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
