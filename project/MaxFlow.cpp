#include "MaxFlow.h"
#include "datastructures/MutablePriorityQueue.h"
#include <queue>
#include <stack>
using namespace std;


/********************** Max Flow  ****************************/

double residualC(Edge* e, bool out){
    return out ? e->getWeight() - e->getFlow() : e->getFlow();
}

double getCf(Vertex* source, Vertex* target) {
    double minC = INF;
    Vertex *curr = target;
    while (curr != source) {
        bool outgoing = curr->getPath()->getDest() == curr;
        minC = std::min(minC, residualC(curr->getPath(), outgoing));
        curr = outgoing ? curr->getPath()->getOrig() : curr->getPath()->getDest();
    }
    return minC;
}

void augmentPath(Vertex* source, Vertex* target, double cf) {
    Vertex* curr = target;
    while (curr != source){
        bool outgoing = curr->getPath()->getDest() == curr;
        curr->getPath()->setFlow(outgoing ? curr->getPath()->getFlow() + cf : curr->getPath()->getFlow() - cf);
        curr = outgoing ? curr->getPath()->getOrig() : curr->getPath()->getDest();
    }
}

void testAndVisit(queue<Vertex*>& q, Edge* e, Vertex* w, double residual) {
    if (!w->isVisited() && residual > 0 && w->checkActive() && e->checkActive()) {
        w->setVisited(true);
        w->setPath(e);
        q.push(w);
    }
}

bool findAugPath(Graph* g, Vertex* src, Vertex* target){
    for(auto v : g->getVertexSet())
        v.second->setVisited(false); //reset
    std::queue<Vertex*> aux;
    aux.push(src);
    src->setVisited(true);
    while(!aux.empty() && !target->isVisited()){
        Vertex* v = aux.front();
        aux.pop();
        for(Edge* adj : v->getAdj()){
            testAndVisit(aux, adj, adj->getDest(), residualC(adj, true));
        }
        for(Edge* adj : v->getIncoming()){
            testAndVisit(aux, adj, adj->getOrig(), residualC(adj, false));
        }
    }
    return target->isVisited();
}

void MaxFlow::maxFlow(const string& source, const string& sink, Graph* network) {
    Vertex* src = network->findVertex(source);
    Vertex* snk = network->findVertex(sink);
    while(findAugPath(network, src, snk)){
        double cf = getCf(src, snk);
        augmentPath(src, snk, cf);
    }
}

/********************** MaxFlow Reverse  ****************************/

bool reverseFindAugPath(Graph* g, Vertex* src, Vertex* target){
    for(auto v : g->getVertexSet())
        v.second->setVisited(false); //reset
    std::queue<Vertex*> aux;
    aux.push(src);
    src->setVisited(true);
    while(!aux.empty() && !target->isVisited()){
        Vertex* v = aux.front();
        aux.pop();
        for(Edge* adj : v->getAdj()){
            testAndVisit(aux, adj, adj->getDest(), residualC(adj, false));
        }
        for(Edge* adj : v->getIncoming()){
            testAndVisit(aux, adj, adj->getOrig(), residualC(adj, true));
        }
    }
    return target->isVisited();
}
double reverseGetCf(Vertex* source, Vertex* target) {
    double minC = INF;
    Vertex *curr = target;
    while (curr != source) {
        bool outgoing = curr->getPath()->getDest() == curr;
        minC = std::min(minC, residualC(curr->getPath(), !outgoing));
        curr = outgoing ? curr->getPath()->getOrig() : curr->getPath()->getDest();
    }
    return minC;
}

void MaxFlow::reverseMaxFlow(const string& source, const string& sink, Graph* network) {
    Vertex* src = network->findVertex(source);
    Vertex* snk = network->findVertex(sink);
    while(reverseFindAugPath(network, src, snk)){
        double cf = reverseGetCf(src, snk);
        augmentPath(src, snk, -cf);
    }
}



/********************** Delete with paths  ****************************/

void MaxFlow::augmentPathList(Vertex* source, Vertex* target, double cf) {
    Vertex* curr = target;
    vector<pair<bool, Edge*>> path;
    while (curr != source){
        bool outgoing = curr->getPath()->getDest() == curr;
        path.emplace_back(outgoing, curr->getPath());
        curr->getPath()->setFlow(outgoing ? curr->getPath()->getFlow() + cf : curr->getPath()->getFlow() - cf);
        curr = outgoing ? curr->getPath()->getOrig() : curr->getPath()->getDest();
    }
    path.erase(path.end()-1);
    for (auto e: path) {
        e.second->addPath(free.empty() ? paths.size() : free.at(0));
        e.second->getDest()->addPath(free.empty() ? paths.size() : free.at(0));
        e.second->getOrig()->addPath(free.empty() ? paths.size() : free.at(0));
    }
    paths.emplace(free.empty()? paths.size(): free.at(0), pair<double, vector<pair<bool, Edge*>>>{make_pair(cf, path)});
    if (!free.empty()) free.erase(free.begin());
}

void MaxFlow::maxFlowWithList(Graph* network) {
    Vertex* src = network->findVertex("src");
    Vertex* snk = network->findVertex("sink");
    while(findAugPath(network, src, snk)){
        double cf = getCf(src, snk);
        augmentPathList(src, snk, cf);
    }
}


void MaxFlow::resetPaths(const std::unordered_set<int>& pathSet) {
    for (auto k: pathSet) {
        if (paths.count(k)) {
            for (auto e: paths.at(k).second) {
                if (e.second->hasPath(k)) {
                    e.second->setFlow(e.second->getFlow() - (e.first ? paths.at(k).first: -paths.at(k).first));
                    e.second->removePath(k);
                    e.second->getDest()->removePath(k);
                    e.second->getOrig()->removePath(k);
                    if (e.second->getFlow() < 0) resetPaths(e.second->getPaths());
                }
            }
            paths.erase(k);
            free.push_back(k);
        }
    }
}

void MaxFlow::deleteReservoir(const std::string& reservoir, Graph* network) {
    Vertex* v = network->findVertex(reservoir);
    resetPaths(v->getPaths());
    v->desactivate();
    maxFlowWithList(network);
}

void MaxFlow::deleteStation(const std::string& station, Graph* network) {
    Vertex* v = network->findVertex(station);
    resetPaths(v->getPaths());
    v->desactivate();
    maxFlowWithList(network);
}

void MaxFlow::deletePipe(const std::string& source, const std::string& dest, Graph* network) {
    auto edge = network->findEdge(source, dest);
    resetPaths(edge->getPaths());
    edge->desactivate();
    if (edge->getReverse() != nullptr) edge->getReverse()->desactivate();
    maxFlowWithList(network);
}

void MaxFlow::reliabilityPrep(Graph* network) {
    paths.clear();
    for (auto v: network->getVertexSet()) {
        v.second->resetPath();
        for (auto e: v.second->getAdj()) {
            e->resetPath();
            e->setFlow(0);
        }
    }
    maxFlowWithList(network);
}

bool findMinAugmentingPath(Graph* network, const string& source, const string& target, double(*cost)(Edge*)){
    MutablePriorityQueue q;
    for(auto v : network->getVertexSet()){
        v.second->setDist(INF);
        v.second->setPath(nullptr);
        v.second->setVisited(false);
    }
    auto *start = network->findVertex(source);
    start->setDist(0);
    q.insert(start);
    while(!q.empty()){
        Vertex* v = q.extractMin();
        v->setVisited(true);
        if(!v->checkActive()) continue;
        for(auto* e : v->getAdj()){
            if(!e->checkActive() || e->getFlow() == e->getWeight()) continue;
            Vertex* w = e->getDest();
            if(!w->checkActive() || w->isVisited()) continue;
            double currentCost = w->getDist(), nextCost = v->getDist() + cost(e);
            if(currentCost > nextCost){
                w->setPath(e);
                w->setDist(nextCost);
                if(currentCost == INF)
                    q.insert(w);
                else
                    q.decreaseKey(w);
            }
        }
    }
    return network->findVertex(target)->isVisited();
}

void MaxFlow::balancedMaxFlow(Graph* network, const string& source, const string& sink){
    Vertex* src = network->findVertex(source);
    Vertex* snk = network->findVertex(sink);
    network->resetFlow();
    while(findMinAugmentingPath(network, source, sink,
            [](Edge* edge) -> double { return 1/(edge->getWeight() - edge->getFlow());})){
        double cf = getCf(src, snk);
        augmentPath(src, snk, cf);
    }
}
