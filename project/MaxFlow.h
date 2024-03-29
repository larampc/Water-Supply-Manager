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
    /**
     * \brief Performs the maxFlow algorithm on the provided network Graph using the edmondsKarp algorithm.
     *
     * @param source The source vertex.
     * @param sink The sink vertex.
     * @param network The network Graph in which to perform the maxFlow.
     *
     *\par Complexity
     * O(VE^2) in which V is the number of vertex and E the number of edges of the Graph.
     */
    void maxFlow(std::string source, std::string sink, Graph& network);
    /**
     * \brief Iteratively finds augment paths from the given source and subtracts their bottleneck flow until the source's outgoing flow is zero.
     *
     * @param source The source vertex.
     * @param sink The sink vertex.
     * @param network The network Graph in which to perform the maxFlow.
     *
     *\par Complexity
     * O(VE^2) in which V is the number of vertex and E the number of edges of the Graph.
     */
    void reverseMaxFlow(std::string source, std::string sink, Graph& network);
    /********************** MaxFlow List ****************************/
    /**
     * \brief Performs the maxFlow algorithm on the provided network Graph using the edmondsKarp algorithm and saves the augmentation paths that were used.
     *
     * @param network The network Graph in which to perform the maxFlow.
     *
     *\par Complexity
     * O(VE^2) in which V is the number of vertex and E the number of edges of the Graph.
     */
    void maxFlowWithList(Graph& network);
    /**
     * \brief Auxiliary function used by maxFlowWithList to augment the path from source to target with a value, saving the path.
     *
     * @param source The source vertex.
     * @param target The target vertex.
     * @param cf The value to augment the path with.
     */
    void augmentPathList(Vertex* source, Vertex* target, double cf);
    void resetPaths(std::unordered_set<int> pathSet);
    void deleteReservoir(std::string reservoir, Graph& network);
    void deleteStation(std::string station, Graph& network);
    void deletePipe(std::string source, std::string dest, Graph& network);
    void reliabilityPrep(Graph& network);
    void reliabilityTearDown(Graph& network);

    void transformBidirectionalEdges(Graph &network);

    void balance(Graph &network);

    void balanceAdj(Vertex *v, Graph &network);

    bool findAugPath(Graph *g, Vertex *src, Vertex *target);

    double getCf(Vertex *source, Vertex *target);

    static void augmentPath(Vertex *source, Vertex *target, double cf);
};


#endif //WATERSUPPLYMANAGER_MAXFLOW_H
