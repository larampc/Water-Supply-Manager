#include "Graph.h"
#include <string>
#include <utility>

Vertex::Vertex(string in): info(std::move(in)) {}

Edge::Edge(Vertex *d, string w): dest(d), weight(std::move(w)) {}

size_t Graph::getNumVertex() const {
    return vertexMap.size();
}

unordered_map<string, Vertex*> Graph::getVertexSet() const {
    return vertexMap;
}

std::string Vertex::getInfo() const {
    return info;
}

void Vertex::setInfo(std::string in) {
    Vertex::info = std::move(in);
}

bool Vertex::isProcessing() const {
    return processing;
}

void Vertex::setProcessing(bool p) {
    Vertex::processing = p;
}

Vertex *Edge::getDest() const {
    return dest;
}

void Edge::setDest(Vertex *d) {
    Edge::dest = d;
}

std::string Edge::getWeight() const {
    return weight;
}

void Edge::setWeight(std::string airline) {
    Edge::weight = std::move(airline);
}

/*
 * Auxiliary function to find a vertex with a given content.
 */
Vertex* Graph::findVertex(const string &in) const {
    auto it = vertexMap.find(in);
    if (it == vertexMap.end()) return nullptr;
    return vertexMap.at(in);
}

bool Vertex::isVisited() const {
    return visited;
}

int Vertex::getIndegree() const {
    return indegree;
}

void Vertex::setIndegree(int indegree) {
    Vertex::indegree = indegree;
}

int Vertex::getNum() const {
    return num;
}

void Vertex::setNum(int num) {
    Vertex::num = num;
}

int Vertex::getLow() const {
    return low;
}

void Vertex::setLow(int low) {
    Vertex::low = low;
}

void Vertex::setVisited(bool v) {
    Vertex::visited = v;
}

const vector<Edge> &Vertex::getAdj() const {
    return adj;
}

void Vertex::setAdj(const vector<Edge> &adj) {
    Vertex::adj = adj;
}


/*
 *  Adds a vertex with a given content or info (in) to a graph (this).
 *  Returns true if successful, and false if a vertex with that content already exists.
 */
bool Graph::addVertex(const std::string &in) {
    if (findVertex(in) != nullptr)
        return false;
    vertexMap.insert(make_pair(in, new Vertex(in)));
    return true;
}


/*
 * Adds an edge to a graph (this), given the contents of the source and
 * destination vertices and the edge weight (w).
 * Returns true if successful, and false if the source or destination vertex does not exist.
 */
bool Graph::addEdge(const string &sourc, const string &dest, std::string w) {
    auto v1 = findVertex(sourc);
    auto v2 = findVertex(dest);
    if (v1 == nullptr || v2 == nullptr)
        return false;
    v1->addEdge(v2,w);
    return true;
}

/*
 * Auxiliary function to add an outgoing edge to a vertex (this),
 * with a given destination vertex (d) and edge weight (w).
 */
void Vertex::addEdge(Vertex *d, std::string w) {
    adj.emplace_back(d, w);
    d->setIndegree(d->getIndegree() + 1);
}


/*
 * Removes an edge from a graph (this).
 * The edge is identified by the source (sourc) and destination (dest) contents.
 * Returns true if successful, and false if such edge does not exist.
 */
bool Graph::removeEdge(const string &sourc, const string &dest, const string& airline) {
    auto v1 = findVertex(sourc);
    auto v2 = findVertex(dest);
    if (v1 == nullptr || v2 == nullptr)
        return false;
    return v1->removeEdgeTo(v2, airline);
}

/*
 * Auxiliary function to remove an outgoing edge (with a given destination (d))
 * from a vertex (this).
 * Returns true if successful, and false if such edge does not exist.
 */
bool Vertex::removeEdgeTo(Vertex *d, const string& airline) {
    for (auto it = adj.begin(); it != adj.end(); it++)
        if (it->dest  == d && it->weight == airline) {
            adj.erase(it);
            d->setIndegree(d->getIndegree() - 1);
            return true;
        }

    return false;
}

/*
 *  Removes a vertex with a given content (in) from a graph (this), and
 *  all outgoing and incoming edges.
 *  Returns true if successful, and false if such vertex does not exist.
 */
bool Graph::removeVertex(const string &in) {
    return vertexMap.erase(in);
}