#include "Graph.h"

#include <utility>
#include <stack>

/************************* Vertex  **************************/


Vertex::Vertex(std::string in): info(std::move(in)) {}
/*
 * Auxiliary function to add an outgoing edge to a vertex (this),
 * with a given destination vertex (d) and edge weight (w).
 */

Edge * Vertex::addEdge(Vertex *d, double w) {
    auto newEdge = new Edge(this, d, w);
    adj.push_back(newEdge);
    d->incoming.push_back(newEdge);
    return newEdge;
}

/*
 * Auxiliary function to remove an outgoing edge (with a given destination (d))
 * from a vertex (this).
 * Returns true if successful, and false if such edge does not exist.
 */

bool Vertex::removeEdge(const std::string& in) {
    bool removedEdge = false;
    auto it = adj.begin();
    while (it != adj.end()) {
        Edge *edge = *it;
        Vertex *dest = edge->getDest();
        if (dest->getInfo() == in) {
            it = adj.erase(it);
            deleteEdge(edge);
            removedEdge = true; // allows for multiple edges to connect the same pair of vertices (multigraph)
        }
        else {
            it++;
        }
    }
    return removedEdge;
}

/*
 * Auxiliary function to remove an outgoing edge of a vertex.
 */

void Vertex::removeOutgoingEdges() {
    auto it = adj.begin();
    while (it != adj.end()) {
        Edge *edge = *it;
        it = adj.erase(it);
        deleteEdge(edge);
    }
}


bool Vertex::operator<(Vertex & vertex) const {
    return this->dist < vertex.dist;
}

std::string
Vertex::getInfo() const {
    return this->info;
}

std::vector<Edge*> Vertex::getAdj() const {
    return this->adj;
}

bool Vertex::isVisited() const {
    return this->visited;
}

bool Vertex::isProcessing() const {
    return this->processing;
}

unsigned int Vertex::getIndegree() const {
    return this->indegree;
}

double Vertex::getDist() const {
    return this->dist;
}

Edge *Vertex::getPath() const {
    return this->path;
}

std::vector<Edge *> Vertex::getIncoming() const {
    return this->incoming;
}

void Vertex::setInfo(std::string in) {
    this->info = std::move(in);
}

void Vertex::setVisited(bool visited) {
    this->visited = visited;
}

void Vertex::setProcessing(bool processing) {
    this->processing = processing;
}

void Vertex::setIndegree(unsigned int indegree) {
    this->indegree = indegree;
}

void Vertex::setDist(double dist) {
    this->dist = dist;
}

void Vertex::setPath(Edge *path) {
    this->path = path;
}

void Vertex::deleteEdge(Edge *edge) {
    Vertex *dest = edge->getDest();
    // Remove the corresponding edge from the incoming list
    auto it = dest->incoming.begin();
    while (it != dest->incoming.end()) {
        if ((*it)->getOrig()->getInfo() == info) {
            it = dest->incoming.erase(it);
        }
        else {
            it++;
        }
    }
    delete edge;
}

std::unordered_set<int> Vertex::getPaths() {
    return paths;
}

void Vertex::addPath(int p) {
    paths.emplace(p);
}

void Vertex::removePath(int p) {
    paths.erase(p);
}

void Vertex::resetPath() {
    paths.clear();
}

void Vertex::activate() {
    isActive = true;
}

void Vertex::desactivate() {
    isActive = false;
}

bool Vertex::checkActive() {
    return isActive;
}

/********************** Edge  ****************************/


Edge::Edge(Vertex *orig, Vertex *dest, double w): orig(orig), dest(dest), weight(w) {}

Vertex * Edge::getDest() const {
    return this->dest;
}

double Edge::getWeight() const {
    return this->weight;
}

Vertex * Edge::getOrig() const {
    return this->orig;
}

Edge *Edge::getReverse() const {
    return this->reverse;
}

double Edge::getFlow() const {
    return flow;
}

void Edge::setReverse(Edge *reverse) {
    this->reverse = reverse;
}

void Edge::setFlow(double flow) {
    this->flow = flow;
}

void Edge::setWeight(double weight) {
    this->weight = weight;
}

std::unordered_set<int> Edge::getPaths() {
    return paths;
}

void Edge::addPath(int p) {
    paths.emplace(p);

}

void Edge::removePath(int p) {
    paths.erase(p);
}

void Edge::resetPath() {
    paths.clear();
}

bool Edge::hasPath(int p) {
    return paths.count(p);
}

void Edge::desactivate() {
    isActive = false;
}

void Edge::activate() {
    isActive = true;
}

bool Edge::checkActive() const {
    return isActive;
}

bool Edge::checkVisited() const {
    return visited;
}

void Edge::setVisited(bool newVisited) {
    visited = newVisited;
}

/********************** Graph  ****************************/


int Graph::getNumVertex() const {
    return vertexSet.size();
}

std::unordered_map<std::string, Vertex*> Graph::getVertexSet() const {
    return vertexSet;
}

/*
 * Auxiliary function to find a vertex with a given content.
 */
Vertex* Graph::findVertex(const std::string&in) const {
    auto it = vertexSet.find(in);
    return (it != vertexSet.end()) ? it->second : nullptr;
}


/*
 *  Adds a vertex with a given content or info (in) to a graph (this).
 *  Returns true if successful, and false if a vertex with that content already exists.
 */
bool Graph::addVertex(const std::string &in) {
    if(findVertex(in) != nullptr) return false;
    vertexSet.emplace(in, new Vertex(in));
    return true;
}

/*
 *  Removes a vertex with a given content (in) from a graph (this), and
 *  all outgoing and incoming edges.
 *  Returns true if successful, and false if such vertex does not exist.
 */

bool Graph::removeVertex(const std::string& in) {
    auto it = vertexSet.find(in);
    if (it != vertexSet.end()) {
        Vertex* v = it->second;
        v->removeOutgoingEdges();
        for (auto u: vertexSet) {
            (u.second)->removeEdge(v->getInfo());
        }
        vertexSet.erase(it);
        delete v;
        return true;
    }
    return false;
}

/*
 * Adds an edge to a graph (this), given the contents of the source and
 * destination vertices and the edge weight (w).
 * Returns true if successful, and false if the source or destination vertex does not exist.
 */

bool Graph::addEdge(const std::string &sourc, const std::string& dest, double w) const {
    auto v1 = findVertex(sourc);
    auto v2 = findVertex(dest);
    if (v1 == nullptr || v2 == nullptr)
        return false;
    v1->addEdge(v2, w);
    return true;
}

bool Graph::addBidirectionalEdge(const std::string& sourc, const std::string& dest, double w) const {
    auto v1 = findVertex(sourc);
    auto v2 = findVertex(dest);
    if (v1 == nullptr || v2 == nullptr)
        return false;
    auto e1 = v1->addEdge(v2, w);
    auto e2 = v2->addEdge(v1, w);
    e1->setReverse(e2);
    e2->setReverse(e1);
    return true;
}

/****************** isDAG  ********************/
/*
 * Performs a depth-first search in a graph (this), to determine if the graph
 * is acyclic (acyclic directed graph or DAG).
 * During the search, a cycle is found if an edge connects to a vertex
 * that is being processed in the stack of recursive calls (see theoretical classes).
 * Returns true if the graph is acyclic, and false otherwise.
 */

bool Graph::isDAG() const {
    for (auto v : vertexSet) {
        v.second->setVisited(false);
        v.second->setProcessing(false);
    }
    for (auto v : vertexSet) {
        if (! v.second->isVisited()) {
            if ( ! dfsIsDAG(v.second) ) return false;
        }
    }
    return true;
}

/**
 * Auxiliary function that visits a vertex (v) and its adjacent, recursively.
 * Returns false (not acyclic) if an edge to a vertex in the stack is found.
 */

bool Graph::dfsIsDAG(Vertex *v) const {
    v->setVisited(true);
    v->setProcessing(true);
    for (auto e : v->getAdj()) {
        if(!e->checkActive()) continue;
        auto w = e->getDest();
        if (w->isProcessing()) return false;
        if (! w->isVisited()) {
            if (! dfsIsDAG(w)) return false;
        }
    }
    v->setProcessing(false);
    return true;
}

void dfsVisit(Vertex* v, std::stack<std::string>& aux){
    v->setVisited(true);
    v->setProcessing(true);
    for(Edge* adj : v->getAdj()){
        if (adj->checkActive()) {
            if(!adj->getDest()->isVisited()) dfsVisit(adj->getDest(), aux);
        }
    }
    v->setProcessing(false);
    aux.push(v->getInfo());
}

std::vector<std::string> Graph::topSort() const {
    std::vector<std::string> res;
    std::stack<std::string> aux;
    for(auto v : vertexSet){
        v.second->setVisited(false);
        v.second->setProcessing(false);
    }
    for(const auto& v : vertexSet){
        if(!v.second->isVisited()){
            dfsVisit(v.second, aux);
        }
    }
    while (!aux.empty()) {
        res.push_back(aux.top());
        aux.pop();
    }
    return res;
}

void Graph::resetFlow() {
    for(const auto& v: vertexSet){
        for(Edge* e: v.second->getAdj()){
            e->setFlow(0);
        }
    }
}

Edge *Graph::findEdge(const std::string &source, const std::string &dest) const {
    auto v = findVertex(source);
    for(auto adj: v->getAdj()){
        if(adj->getDest()->getInfo() == dest) return adj;
    }
    return nullptr;
}

Graph::~Graph() {
    for (const auto& v: vertexSet) {
        removeVertex(v.first);
    }
}