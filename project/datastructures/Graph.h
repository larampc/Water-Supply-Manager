#ifndef DA_TP_CLASSES_GRAPH
#define DA_TP_CLASSES_GRAPH

#include <iostream>
#include <vector>
#include <queue>
#include <limits>
#include <algorithm>
#include <unordered_map>
#include <unordered_set>

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
    Vertex(std::string in);
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
    bool removeEdge(std::string in);
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
     * \brief Gets the sum of the flow of all incoming Edge to this Vertex.
     *
     * @return The sum of the flow of all incoming Edge to this Vertex.
     */
    double getIncomingFlow();
    /**
     * \brief Gets the sum of the weight of all outgoing Edge from this Vertex.
     *
     * @return The sum of the weight of all outgoing Edge from this Vertex.
     */
    double outWeight();
protected:
    std::string info;                // info node
    std::vector<Edge *> adj;  // outgoing edges

    // auxiliary fields
    bool visited = false; // used by DFS, BFS, Prim ...
    bool processing = false; // used by isDAG (in addition to the visited attribute)
    unsigned int indegree; // used by topsort
    double dist = 0;
    Edge *path = nullptr;

    std::vector<Edge *> incoming; // incoming edges

    int queueIndex = 0; 		// required by MutablePriorityQueue and UFDS

    void deleteEdge(Edge *edge);
    std::unordered_set<int> paths;
    bool isActive = true;

};

/********************** Edge  ****************************/


class Edge {
public:
    Edge(Vertex *orig, Vertex *dest, double w);

    Vertex * getDest() const;
    double getWeight() const;
    bool isSelected() const;
    Vertex * getOrig() const;
    Edge *getReverse() const;
    double getFlow() const;

    void setSelected(bool selected);
    void setReverse(Edge *reverse);
    void setFlow(double flow);
    void setWeight(double weight);
    std::unordered_set<int> getPaths();
    void addPath(int p);
    void removePath(int p);
    void resetPath();
    bool hasPath(int p);
    void desactivate();
    void activate();
    bool checkActive();
protected:
    Vertex * dest; // destination vertex
    double weight; // edge weight, can also be used for capacity

    // auxiliary fields
    bool selected = false;

    // used for bidirectional edges
    Vertex *orig;
    Edge *reverse = nullptr;

    double flow; // for flow-related problems
    std::unordered_set<int> paths;
    bool isActive = true;
};

/********************** Graph  ****************************/


class Graph {
public:
    ~Graph();
    /*
    * Auxiliary function to find a vertex with a given the content.
    */
    Vertex *findVertex(const std::string &in) const;
    /*
    * Auxiliary function to find a vertex with a given the content.
    */
    Edge *findEdge(const std::string &source, const std::string &dest) const;
    /*
     *  Adds a vertex with a given content or info (in) to a graph (this).
     *  Returns true if successful, and false if a vertex with that content already exists.
     */
    bool addVertex(const std::string &in);
    bool removeVertex(const std::string &in);

    /*
     * Adds an edge to a graph (this), given the contents of the source and
     * destination vertices and the edge weight (w).
     * Returns true if successful, and false if the source or destination vertex does not exist.
     */
    bool addEdge(const std::string &sourc, const std::string &dest, double w);
    bool removeEdge(const std::string &source, const std::string &dest);
    bool addBidirectionalEdge(const std::string &sourc, const std::string &dest, double w);

    int getNumVertex() const;
    std::unordered_map<std::string, Vertex*> getVertexSet() const;

    std::vector<std::string> dfs() const;
    std::vector<std::string> dfs(const std::string & source) const;
    void dfsVisit(Vertex *v,  std::vector<std::string> & res) const;
    std::vector<std::string> bfs(const std::string & source) const;

    bool isDAG() const;
    bool dfsIsDAG(Vertex *v) const;
    std::vector<std::string> topsort() const;
    void resetFlow();
protected:
    std::unordered_map<std::string, Vertex *> vertexSet;    // vertex set

    double ** distMatrix = nullptr;   // dist matrix for Floyd-Warshall
    int **pathMatrix = nullptr;   // path matrix for Floyd-Warshall

    /*
     * Finds the index of the vertex with a given content.
     */
    int findVertexIdx(const std::string& in) const;
};

void deleteMatrix(int **m, int n);
void deleteMatrix(double **m, int n);



#endif /* DA_TP_CLASSES_GRAPH */