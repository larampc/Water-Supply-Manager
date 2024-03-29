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
    /**
     * \brief Removes the given paths from the currently used augmentation paths, updating the network.
     *
     * @param pathSet The set of indexes of the paths to remove.
     *
     * \par Complexity
     * O(NL) in which N is the number of paths to delete and L is the length of the longest path to delete.
     */
    void resetPaths(const std::unordered_set<int>& pathSet);
    /**
     * \brief Deletes the given reservoir from the given network Graph, updating the network's flow.
     *
     * @param reservoir The reservoir to delete.
     * @param network The network Graph to remove the reservoir from.
     *
     * \par Complexity
     * O(NL + VE^2) where NL is the complexity of removing the used augmentation paths from the reservoir and VE^2 is the complexity of updating the existing network flow.
     */
    void deleteReservoir(const std::string& reservoir, Graph& network);
    /**
     * \brief Deletes the given station from the given network Graph, updating the network's flow.
     *
     * @param station The station to delete.
     * @param network The network Graph to remove the reservoir from.
     *
     * \par Complexity
     * O(NL + VE^2) where NL is the complexity of removing the used augmentation paths containing the given station and VE^2 is the complexity of updating the existing network flow.
     */
    void deleteStation(const std::string& station, Graph& network);
    /**
     * \brief Deletes the given station from the given network Graph, updating the network's flow.
     *
     * @param source The source vertex of the pipe to delete.
     * @param dest The destination vertex of the pipe to delete.
     * @param network The network Graph to remove the pipe from.
     *
     * \par Complexity
     * O(NL + VE^2) where NL is the complexity of removing the used augmentation paths containing the given pipe and VE^2 is the complexity of updating the existing network flow.
     */
    void deletePipe(const std::string& source, const std::string& dest, Graph& network);
    /**
     * \brief Prepares the given network for reliability testing initializing its flow and used augmentation paths by calling maxFlowWithLists.
     *
     * @param network The network Graph that will be tested.
     *
     * \par Complexity
     * O(VE^2) The complexity of maxFlowWithLists.
     */
    void reliabilityPrep(Graph& network);
    void reliabilityTearDown(Graph& network);

    void transformBidirectionalEdges(Graph &network);

    void balance(Graph &network);

    void balanceAdj(Vertex *v, Graph &network);

    bool findAugPath(Graph *g, Vertex *src, Vertex *target);
    /**
     * \brief Finds the bottleneck of the path from source to target.
     *
     * @param source The source vertex.
     * @param target The target vertex.
     * @return The path's bottleneck.
     */
    double getCf(Vertex *source, Vertex *target);
    /**
     * \brief Augments the path from source to target with a value.
     *
     * @param source The source vertex.
     * @param target The target vertex.
     * @param cf The value to augment the path with.
     */
    static void augmentPath(Vertex *source, Vertex *target, double cf);
};


#endif //WATERSUPPLYMANAGER_MAXFLOW_H
