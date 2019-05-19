#ifndef INTERFACE__OSMEXTRACTOR_H_
#define INTERFACE__OSMEXTRACTOR_H_

#include <map>
#include "OSMCollection.h"
#include "utils/FileManager.h"

class OSMExtractor {

 public:
  OSMCollection extractOSMCollectionByCity(const std::string &city);

 private:
  std::map<idNode, Position> getNodesXYPosition(const std::string& city);
  std::vector<std::pair<idNode, idNode>> getEdges(const std::string& city);
};

#endif //INTERFACE__OSMEXTRACTOR_H_
