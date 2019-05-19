

int main(){

  OSMExtractor osm_extractor;
  OSMCollection OSMCol = osm_extractor.extractOSMCollectionByCity("Porto");

// GET nodes:: OSMCol.getNodeMap;
// GET Edges:: OSMCol.getEdges

    return 0;
}