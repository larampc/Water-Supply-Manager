#ifndef DA_TP_CLASSES_GRAPH
#define DA_TP_CLASSES_GRAPH

#include <iostream>
#include <vector>
#include <queue>
#include <limits>
#include <algorithm>
#include <unordered_map>
#include <unordered_set>
#include <list>
#include <stack>

class Edge;

#define INF std::numeric_limits<double>::max()


/************************* Vertex  **************************/

/**
 * \class Vertex
 * \brief A custom class to represent a Graph's Vertex.
 *
 * This class stores all information and functions of a Graph's Vertex.
 */
class Vertex {
public:
    /**
     * \brief Vertex constructor.
     *
     * @param in The Vertex info.
     */
    explicit Vertex(std::string in);
    /**
     * \brief Less than operator to compare Vertex dists.
     *
     * @param vertex The Vertex to compare.
     * @return True if this Vertex dist is lower than the dist of the given Vertex.
     */
    bool operator<(Vertex & vertex) const; // required by MutablePriorityQueue

    /**
     * \brief Gets the Vertex info.
     *
     * @return The Vertex info.
     */
    std::string getInfo() const;
    /**
     * \brief Gets all outgoing Edge from the Vertex.
     *
     * @return All outgoing Edge from the Vertex.
     */
    std::vector<Edge*> getAdj() const;
    /**
     * \brief Gets the Vertex visited state.
     *
     * @return The Vertex visited state.
     */
    bool isVisited() const;
    /**
     * \brief Gets the Vertex processing state.
     *
     * @return The Vertex processing state.
     */
    bool isProcessing() const;
    /**
     * \brief Gets the number of incoming Edge to the Vertex.
     *
     * @return The number of incoming Edge to the Vertex.
     */
    unsigned int getIndegree() const;
    /**
     * \brief Gets the Vertex dist.
     *
     * @return The Vertex dist.
     */
    double getDist() const;
    /**
     * \brief Sets the Vertex dist.
     *
     * @param dist The Vertex dist to set.
     */
    void setDist(double dist);

    /**
     * \brief Gets the Vertex path.
     *
     * @return The Vertex path.
     */
    Edge *getPath() const;
    /**
     * \brief Gets all incoming Edge to the Vertex.
     *
     * @return All incoming Edge to the Vertex.
     */
    std::vector<Edge *> getIncoming() const;

    /**
     * \brief Sets the Vertex info.
     *
     * @param info The Vertex info to set.
     */
    void setInfo(std::string info);
    /**
     * \brief Sets the Vertex visited state.
     *
     * @param visited The Vertex visited state to set.
     */
    void setVisited(bool visited);
    /**
     * \brief Sets the Vertex processing state.
     *
     * @param processing The Vertex processing state to set.
     */
    void setProcessing(bool processing);
    /**
     * \brief Sets the Vertex indegree.
     *
     * @param indegree The Vertex indegree to set.
     */
    void setIndegree(unsigned int indegree);
    /**
     * \brief Sets the Vertex path.
     *
     * @param path The Vertex path to set.
     */
    void setPath(Edge *path);
    /**
     * \brief Creates a new Edge from this Vertex to the given Vertex with the given weight.
     *
     * @param dest The destination vertex of the new Edge.
     * @param w The weight of the new Edge.
     * @return The new Edge.
     */
    Edge * addEdge(Vertex *dest, double w);
    /**
     * \brief Deletes all Edge from this Vertex to the Vertex with the given info.
     *
     * @param in The info of the destination Vertex of the Edge to delete.
     * @return True if deleted any Edge, false otherwise.
     */
    bool removeEdge(const std::string& in);
    /**
     * \brief Deletes all Edge that are outgoing from this Vertex.
     */
    void removeOutgoingEdges();
    /**
     * \brief Gets the Vertex paths.
     *
     * @return The Vertex paths.
     */
    std::unordered_set<int> getPaths();
    /**
     * \brief Adds a new path to paths.
     *
     * @param p The new path to add.
     */
    void addPath(int p);
    /**
     * \brief Removes the given path from paths.
     *
     * @param p The path to remove.
     */
    void removePath(int p);
    /**
     * \brief Removes all path from paths.
     */
    void resetPath();
    /**
     * \brief Sets the Vertex active state to false.
     */
    void desactivate();
    /**
     * \brief Sets the Vertex active state to true.
     */
    void activate();
    /**
     * \brief Gets the Vertex active state.
     *
     * @return The Vertex active state.
     */
    bool checkActive();
    /**
     * \brief Removes incoming Edge from the Vertex.
     *
     * @param edge The Edge to remove.
     */
    void deleteEdge(Edge *edge);
    int queueIndex = 0;
protected:
    std::string info;                // info node
    std::vector<Edge *> adj;  // outgoing edges

    // auxiliary fields
    bool visited = false; // used by DFS, BFS, Prim ...
    bool processing = false; // used by isDAG (in addition to the visited attribute)
    unsigned int indegree = 0; // used by topsort
    double dist = 0;
    Edge *path = nullptr;

    std::vector<Edge *> incoming; // incoming edges

    std::unordered_set<int> paths;
    bool isActive = true;

};

/********************** Edge  ****************************/

/**
 * \class Edge
 * \brief A custom class to represent a Graph's Edge.
 *
 * This class stores all information and functions of a Graph's Edge.
 */
class Edge {
public:
    /**
     * \brief Edge constructor.
     *
     * @param orig The Edge origin Vertex.
     * @param dest The Edge destination Vertex.
     * @param w The Edge weight.
     */
    Edge(Vertex *orig, Vertex *dest, double w);

    /**
     * \brief Gets the Edge destination Vertex.
     *
     * @return The Edge destination Vertex.
     */
    Vertex * getDest() const;
    /**
     * \brief Gets the Edge weight.
     *
     * @return The Edge weight.
     */
    double getWeight() const;
    /**
     * \brief Gets the Edge origin Vertex.
     *
     * @return The Edge origin Vertex.
     */
    Vertex * getOrig() const;
    /**
     * \brief Gets the reverse Edge of this Edge (the Edge that connects the same two Vertex but is in the opposite direction).
     *
     * @return The the reverse Edge of this Edge.
     */
    Edge *getReverse() const;
    /**
     * \brief Gets the Edge flow.
     *
     * @return The Edge flow.
     */
    double getFlow() const;
    /**
     * \brief Sets the reverse Edge of this Edge (the Edge that connects the same two Vertex but is in the opposite direction).
     *
     * @param reverse The the reverse Edge of this Edge to set.
     */
    void setReverse(Edge *reverse);
    /**
     * \brief Sets the Edge flow.
     *
     * @param flow The Edge flow to set.
     */
    void setFlow(double flow);
    /**
     * \brief Sets the Edge weight.
     *
     * @param weight The Edge weight to set.
     */
    void setWeight(double weight);
    /**
     * \brief Gets the Edge paths.
     *
     * @return The Edge paths.
     */
    std::unordered_set<int> getPaths();
    /**
     * \brief Adds a new path to paths.
     *
     * @param p The new path to add.
     */
    void addPath(int p);
    /**
     * \brief Removes the given path from paths.
     *
     * @param p The path to remove.
     */
    void removePath(int p);
    /**
     * \brief Removes all path from paths.
     */
    void resetPath();
    /**
     * \brief Checks if the given path is in paths.
     *
     * @param p The path to check.
     * @return True if the given path is in paths, false otherwise.
     */
    bool hasPath(int p);
    /**
     * \brief Sets the Edge active state to false.
     */
    void desactivate();
    /**
     * \brief Sets the Edge active state to true.
     */
    void activate();
    /**
     * \brief Gets the Edge active state.
     *
     * @return The Edge active state.
     */
    bool checkActive() const;
    bool checkVisited() const;
    void setVisited(bool newVisited);
protected:
    Vertex * dest; // destination vertex
    double weight; // edge weight, can also be used for capacity

    // used for bidirectional edges
    Vertex *orig;
    Edge *reverse = nullptr;

    double flow = 0; // for flow-related problems
    std::unordered_set<int> paths;
    bool isActive = true;
    bool visited = false;
};

/********************** Graph  ****************************/

/**
 * \class Graph
 * \brief A custom class to represent a Graph.
 *
 * This class stores all information and functions of a Graph.
 */
class Graph {
public:
    /**
     * \brief Graph constructor.
     */
    ~Graph();
    /**
     * \brief Auxiliary function to find a Vertex with the given info.
     *
     * @param in The info of the Vertex to find.
     * @return The Vertex with the given info.
     */
    Vertex *findVertex(const std::string &in) const;
    /**
     * \brief Auxiliary function to find an Edge with the given origin and destination Vertex.
     *
     * @param source The Edge's origin Vertex.
     * @param dest The Edge's destination Vertex.
     * @return The Edge with the given origin and destination Vertex.
     */
    Edge *findEdge(const std::string &source, const std::string &dest) const;
    /**
     * \brief Adds a new Vertex with the given info to this Graph.
     *
     * @param in The info of the Vertex to add.
     * @return True if Vertex was added, false otherwise.
     */
    bool addVertex(const std::string &in);
    /**
     * \brief Deletes the Vertex with the given info from this Graph.
     *
     * @param in The info of the Vertex to delete.
     * @return True if Vertex was deleted, false otherwise.
     */
    bool removeVertex(const std::string &in);

    /**
     * \brief Adds a new Edge with the given weight from the Vertex with the given origin info to the Vertex with the given destination info to this Graph.
     *
     * @param sourc The info of the origin Vertex of the Edge to add.
     * @param dest The info of the destination Vertex of the Edge to add.
     * @param w The weight of the Edge to add.
     * @return True if Edge was added, false otherwise.
     */
    bool addEdge(const std::string &sourc, const std::string &dest, double w) const;
    /**
     * \brief Adds two new Edge with the given weight from the Vertex with the given origin info to the Vertex with the given destination info and vice-versa to this Graph.
     *
     * @param sourc The info of the origin Vertex of one Edge and destination Vertex of the other Edge to add.
     * @param dest The info of the destination Vertex of one Edge and origin Vertex of the other Edge to add.
     * @param w The weight of the two Edge to add.
     * @return True if both Edge were added, false otherwise.
     */
    bool addBidirectionalEdge(const std::string &sourc, const std::string &dest, double w) const;

    /**
     * \brief Gets the number of Vertex in this Graph.
     *
     * @retuurn The number of Vertex in this Graph.
     */
    int getNumVertex() const;
    /**
     * \brief Gets the VertexSet of this Graph.
     *
     * @return The VertexSet of this Graph.
     */
    std::unordered_map<std::string, Vertex*> getVertexSet() const;

    /**
     * \brief Checks if this Graph is a DAG (Directed Acyclic Graph).
     *
     * @return True if this Graph is a DAG, false otherwise.
     */
    bool isDAG() const;
    /**
     * \brief Auxiliary dfs function to check if this Graph is a DAG (Directed Acyclic Graph) from the given starting Vertex.
     *
     * @param v The starting Vertex.
     * @return True if this Graph is a DAG, false otherwise.
     */
    bool dfsIsDAG(Vertex *v) const;
    /**
     * \brief Sorts all Vertex in this Graph in topological order.
     *
     * @return All Vertex in this Graph in topological order.
     */
    std::vector<std::string> topSort() const;
    /**
     * \brief Resets all Edge's flow of this Graph to 0.
     */
    void resetFlow();

    std::list<std::list<std::string>> scc();
    void dfs_scc(Vertex *v, std::list<std::list<std::string >> &l, std::stack<std::string>& aux,  std::unordered_map<std::string, int>& ids, int* low, int* num, int &i);
protected:
    std::unordered_map<std::string, Vertex *> vertexSet;    // vertex set
};



#endif /* DA_TP_CLASSES_GRAPH */