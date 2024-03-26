#ifndef WATERSUPPLYMANAGER_MAXFLOW_H
#define WATERSUPPLYMANAGER_MAXFLOW_H

#include <unordered_map>
#include <vector>
#include "datastructures/Graph.h"

class MaxFlow {
private:
    std::unordered_map<unsigned int, std::pair<double, std::vector<std::pair<bool, Edge*>>>> paths;
    std::vector<unsigned int> free;
public:
    void maxFlow(std::string source, std::string sink, Graph& network);
    void reverseMaxFlow(std::string source, std::string sink, Graph& network);
    /********************** MaxFlow List ****************************/

    void maxFlowWithList(Graph& network);
    void augmentPathList(Vertex* source, Vertex* target, double cf);
    void resetPaths(std::unordered_set<int> pat);
    void deleteReservoir(std::string reservoir, Graph& network);
    void deleteStation(std::string station, Graph& network);
    void deletePipe(std::string source, std::string dest, Graph& network);
    void reliabilityPrep(Graph& network);
    void reliabilityTearDown(Graph& network);

    bool findAugPath(Graph *g, Vertex *src, Vertex *target);

    double getCf(Vertex *source, Vertex *target);
};


#endif //WATERSUPPLYMANAGER_MAXFLOW_H
