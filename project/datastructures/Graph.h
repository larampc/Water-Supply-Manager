//
// Created by larap on 05/03/2024.
//

#ifndef WATERSUPPLYMANAGER_GRAPH_H
#define WATERSUPPLYMANAGER_GRAPH_H

#include <cstddef>
#include <vector>
#include <queue>
#include <stack>
#include <list>
#include <algorithm>
#include <unordered_map>
#include <unordered_set>
#include "../Node.h"

using namespace std;

class Edge;
class Graph;

/****************** Provided structures  ********************/

/**
 * \class Vertex
 * \brief This is a class for representing a graph Vertex.
 *
 * This class keeps track of the Vertex Airport, Edges, in degree, number, low and if it was visited or is processing.
 */
class Vertex {
    Node info;               // contents
    vector<Edge> adj;           // list of outgoing edges
    bool visited;               // auxiliary field
    bool processing;            // auxiliary field
    int indegree = 0;               // auxiliary field
    int num = 0;                    // auxiliary field
    int low = 0;                    // auxiliary field

    /**
     * \brief Adds a new Edge to the Vertex.
     *
     * @param dest The destination Vertex of the new Edge.
     * @param w The weight (Airline code) of the new Edge.
     *
     * \par Complexity
     * O(1)
     */
    void addEdge(Vertex *dest, std::string w);
    /**
     * \brief Removes the Edge with the given destination Vertex.
     *
     * @param d The destination Vertex of the Edge to remove.
     * @return True if removed an Edge, false otherwise.
     *
     * \par Complexity
     * O(E) in which E is the number of edges of the vertex
     */
    bool removeEdgeTo(Vertex *d, const string& airline);
public:
    /**
     * \brief Creates a new Vertex.
     *
     * @param in The Airport of the Vertex.
     */
    Vertex(Node in);
    /**
     * \brief Gets the Airport of the Vertex.
     *
     * @return The Airport of the Vertex.
     *
     * \par Complexity
     * O(1)
     */
    Node getInfo() const;
    /**
     * \brief Sets the Airport of the Vertex.
     *
     * @param in The Airport to set.
     *
     * \par Complexity
     * O(1)
     */
    void setInfo(Node in);
    /**
     * \brief Gets the visited status of the Vertex.
     *
     * @return True is is visited, false otherwise.
     *
     * \par Complexity
     * O(1)
     */
    bool isVisited() const;
    /**
     * \brief Sets the visited status of the Vertex.
     *
     * @param v The visited status to set.
     *
     * \par Complexity
     * O(1)
     */
    void setVisited(bool v);
    /**
     * \brief Gets the processing status of the Vertex.
     *
     * @return True is is processing, false otherwise.
     *
     * \par Complexity
     * O(1)
     */
    bool isProcessing() const;
    /**
     * \brief Sets the processing status of the Vertex.
     *
     * @param p The processing status to set.
     *
     * \par Complexity
     * O(1)
     */
    void setProcessing(bool p);
    /**
     * \brief Gets the Edges of the Vertex.
     *
     * @return The Edges of the Vertex.
     *
     * \par Complexity
     * O(1)
     */
    const vector<Edge> &getAdj() const;
    /**
     * \brief Sets the Edges of the Vertex.
     *
     * @param adj The Edges to set.
     *
     * \par Complexity
     * O(1)
     */
    void setAdj(const vector<Edge> &adj);

    /**
     * \brief Gets the in degree of the Vertex.
     *
     * @return The in degree of the Vertex.
     *
     * \par Complexity
     * O(1)
     */
    int getIndegree() const;
    /**
     * \brief Sets the in degree of the Vertex.
     *
     * @param indegree The in degree to set.
     *
     * \par Complexity
     * O(1)
     */
    void setIndegree(int indegree);

    /**
     * \brief Gets the number of the Vertex.
     *
     * @return The number of the Vertex.
     *
     * \par Complexity
     * O(1)
     */
    int getNum() const;
    /**
     * \brief Sets the number of the Vertex.
     *
     * @param num The number to set.
     *
     * \par Complexity
     * O(1)
     */
    void setNum(int num);

    /**
     * \brief Gets the low of the Vertex.
     *
     * @return The low of the Vertex.
     *
     * \par Complexity
     * O(1)
     */
    int getLow() const;
    /**
     * \brief Sets the low of the Vertex.
     *
     * @param low The low to set.
     *
     * \par Complexity
     * O(1)
     */
    void setLow(int low);


    friend class Graph;
};

/**
 * \class Edge
 * \brief This is a class for representing a graph Edge (connection between two vertices of a graph).
 *
 * This class keeps track of the destination Vertex and the weight (Airline code) of the Edge.
 */
class Edge {
    Vertex * dest;      // destination vertex
    std::string weight;         // edge weight
public:
    /**
     * \brief Creates a new Edge.
     *
     * @param d The destination Vertex of the Edge.
     * @param w The weight (Airline code) of the Edge.
     */
    Edge(Vertex *d, std::string w);
    /**
     * \brief Gets the destination Vertex of the Edge.
     *
     * @return The destination Vertex of the Edge.
     *
     * \par Complexity
     * O(1)
     */
    Vertex *getDest() const;
    /**
     * \brief Sets the destination Vertex of the Edge.
     *
     * @param dest The destination Vertex to set.
     *
     * \par Complexity
     * O(1)
     */
    void setDest(Vertex *dest);
    /**
     * \brief Gets the weight (Airline code) of the Edge.
     *
     * @return The weight (Airline code) of the Edge.
     *
     * \par Complexity
     * O(1)
     */
    std::string getWeight() const;
    /**
     * \brief Sets the weight (Airline code) of the Edge.
     *
     * @param airline The weight (Airline code) to set.
     *
     * \par Complexity
     * O(1)
     */
    void setWeight(std::string airline);
    friend class Graph;
    friend class Vertex;
};

/**
 * \class Graph
 * \brief This is a class for representing a Graph.
 *
 * This class keeps track of the vertices and their respective Airport.
 */
class Graph {
    unordered_map<std::string, Vertex*> vertexMap;

public:
    /**
     * \brief Gets the Vertex of the given Airport.
     *
     * @param in The Airport of the Vertex.
     * @return The Vertex of the given Airport.
     *
     * \par Complexity
     * O(1)
     */
    Vertex* findVertex(const Node &in) const;
    /**
     * \brief Gets the total number of Vertex in the Graph.
     *
     * @return The total number of Vertex in the Graph.
     *
     * \par Complexity
     * O(1)
     */
    size_t getNumVertex() const;
    /**
     * \brief Creates and adds a new Vertex to the Graph.
     *
     * @param in The Airport of the new Vertex.
     * @return False if Vertex already exists, true otherwise.
     *
     * \par Complexity
     * O(1)
     */
    bool addVertex(const Node &in);
    /**
     * \brief Removes the Vertex with the given Airport from the Graph.
     *
     * @param in The Airport of the Vertex to remove.
     * @return False if nothing was removed, true otherwise.
     *
     * \par Complexity
     * O(1)
     */
    bool removeVertex(const Node &in);
    /**
     * \brief Creates and adds a new Edge from the source Vertex to the destination Vertex.
     *
     * @param sourc The Airport of the source Vertex.
     * @param dest The Airport of the destination Vertex.
     * @param w The weight (Airline code) of the Edge to create.
     * @return False if either the source or destination Vertex doesn't exist, true otherwise.
     *
     * \par Complexity
     * O(1)
     */
    bool addEdge(const Node &sourc, const Node &dest, std::string w);
    /**
     * \brief Removes Edge from the source Vertex to the destination Vertex with the corresponding weight.
     *
     * @param sourc The Airport of the source Vertex.
     * @param dest The Airport of the destination Vertex.
     * @param airline The airline of the Edge to remove
     * @return False if the Edge was not found, True on successful removal.
     *
     * \par Complexity
     * O(E) in which E is the number of edges of the vertex
     */
    bool removeEdge(const Node &sourc, const Node &dest, const string& airline);
    /**
     * \brief Gets the VertexSet of the Graph.
     *
     * @return The VertexSet of the Graph.
     *
     * \par Complexity
     * O(1)
     */
    unordered_map<std::string, Vertex *> getVertexSet() const;
    /**
     * \brief Resets all the vertices in the graph to the initial state.
     *
     * \par Complexity
     * O(V)
     */
    void resetVertex() const;
    /**
      * \brief Maximum trip (number of stops) and corresponding pair of source-destination airports.
      *
      * @return The maximum number of stops in one trip and the pair source-destination of that trip.
      *
      * \par Complexity
      * O(V(V+E))
      */
};


#endif //WATERSUPPLYMANAGER_GRAPH_H
