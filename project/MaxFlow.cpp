#include "MaxFlow.h"
#include <queue>
#include <stack>
using namespace std;


/********************** Max Flow  ****************************/

double residualC(Edge* e, bool out){
    return out ? e->getWeight() - e->getFlow() : e->getFlow();
}

double MaxFlow::getCf(Vertex* source, Vertex* target) {
    double minC = INF;
    Vertex *curr = target;
    while (curr != source) {
        bool outgoing = curr->getPath()->getDest() == curr;
        minC = std::min(minC, residualC(curr->getPath(), outgoing));
        curr = outgoing ? curr->getPath()->getOrig() : curr->getPath()->getDest();
    }
    return minC;
}

void MaxFlow::augmentPath(Vertex* source, Vertex* target, double cf) {
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

bool MaxFlow::findAugPath(Graph* g, Vertex* src, Vertex* target){
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

void MaxFlow::maxFlow(string source, string sink, Graph& network) {
    Vertex* src = network.findVertex(source);
    Vertex* snk = network.findVertex(sink);
    while(findAugPath(&network, src, snk)){
        double cf = getCf(src, snk);
        augmentPath(src, snk, cf);
    }
}

/********************** MaxFlow Reverse  ****************************/

void reverseAugmentPath(Vertex* source, Vertex* target, double cf) {
    Vertex* curr = target;
    while (curr != source){
        bool outgoing = curr->getPath()->getDest() == curr;
        curr->getPath()->setFlow(outgoing ? curr->getPath()->getFlow() - cf : curr->getPath()->getFlow() + cf);
        curr = outgoing ? curr->getPath()->getOrig() : curr->getPath()->getDest();
    }
}

double reverseResidualC(Edge* e, bool out){
    return out ? e->getFlow() : e->getWeight() - e->getFlow();
}
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
            testAndVisit(aux, adj, adj->getDest(), reverseResidualC(adj, true));
        }
        for(Edge* adj : v->getIncoming()){
            testAndVisit(aux, adj, adj->getOrig(), reverseResidualC(adj, false));
        }
    }
    return target->isVisited();
}
double reverseGetCf(Vertex* source, Vertex* target) {
    double minC = INF;
    Vertex *curr = target;
    while (curr != source) {
        bool outgoing = curr->getPath()->getDest() == curr;
        minC = std::min(minC, reverseResidualC(curr->getPath(), outgoing));
        curr = outgoing ? curr->getPath()->getOrig() : curr->getPath()->getDest();
    }
    return minC;
}

void MaxFlow::reverseMaxFlow(string source, string sink, Graph& network) {
    Vertex* src = network.findVertex(source);
    Vertex* snk = network.findVertex(sink);
    while(reverseFindAugPath(&network, src, snk)){
        double cf = reverseGetCf(src, snk);
        reverseAugmentPath(src, snk, cf);
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

void MaxFlow::maxFlowWithList(Graph& network) {
    Vertex* src = network.findVertex("src");
    Vertex* snk = network.findVertex("sink");
    for(auto v: network.getVertexSet()) {
        for (Edge *e: v.second->getAdj()) {
            e->setFlow(0);
            e->resetPath();
        }
    }
    while(findAugPath(&network, src, snk)){
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

void MaxFlow::deleteReservoir(const std::string& reservoir, Graph& network) {
    Vertex* v = network.findVertex(reservoir);
    resetPaths(v->getPaths());
    v->desactivate();
    maxFlowWithList(network);
}

void MaxFlow::deleteStation(const std::string& station, Graph& network) {
    Vertex* v = network.findVertex(station);
    resetPaths(v->getPaths());
    v->desactivate();
    maxFlowWithList(network);
}

void MaxFlow::deletePipe(const std::string& source, const std::string& dest, Graph& network) {
    auto edge = network.findEdge(source, dest);
    resetPaths(edge->getPaths());
    edge->desactivate();
    maxFlowWithList(network);
}

void MaxFlow::reliabilityPrep(Graph& network) {
    paths.clear();
    maxFlowWithList(network);
}

void MaxFlow::reliabilityTearDown(Graph& network) {
    network.removeVertex("src");
    network.removeVertex("sink");
}

//void MaxFlow::balanceAdj(Vertex* v, Graph& network){
//    auto adjs = v->getAdj();
//    vector<Edge*> activeAdj;
//    double totalCap = 0, totalFlow = 0, adjSize = 0;
//    for(auto adj : adjs){
//        if (adj->checkActive()) {
//            totalCap += adj->getWeight();
//            totalFlow += adj->getFlow();
//            adjSize++;
//            activeAdj.push_back(adj);
//        }
//    }
//    double freeSpaceTarget = (totalCap - totalFlow)/adjSize;
//    sort(activeAdj.begin(), activeAdj.end(), [](Edge* e1, Edge* e2){
//        return e1->getWeight() - e1->getFlow() < e2->getWeight() - e2->getFlow();
//    });
//
//    for (auto k: (*(activeAdj.end()-1))->getPaths()) {
//        auto path = paths.at(k);
//        for (auto e: path.second) {
//            e.second->setFlow(e.second->getFlow()-path.first);
//        }
//
//    }
//    auto sink = network.findVertex("sink");
//    int current = 0;
//    while ( activeAdj.size() > 1) {
//        auto currentAdj = adjs[current];
//        if(findAugPath(&network,currentAdj->getDest(),network.findVertex("sink"))){
//            double cF = getCf(currentAdj->getDest(),sink);
//            double targetFlow = currentAdj->getWeight() - freeSpaceTarget;
//            double delta = targetFlow - currentAdj->getFlow();
//            if (cF > delta){
//
//            }
//        }
//    }
//}
//
//void MaxFlow::balance(Graph& network){
//    for(auto v: network.getVertexSet()){
//        v.second->setVisited(false);
//        v.second->setPath(nullptr);
//    }
//
//    //assuming max flow is done
//    transformBidirectionalEdges(network);
//    if(!network.isDAG()) {
//        cout << "NETWORK IS NOT DAG\n";
//
//    }
//    //visit node in BFS order
//    stack<Vertex*> q;
//    q.push(network.findVertex("src"));
//    while(!q.empty()){
//        auto v = q.top();
//        v->setVisited(true);
//        q.pop();
//        for(auto adj: v->getAdj()){
//            if(!v->isVisited() && adj->checkActive()) q.push(adj->getDest());
//        }
//        balanceAdj(v, network);
//    }
//}
//
//void MaxFlow::transformBidirectionalEdges(Graph& network){
//    for(const auto& v: network.getVertexSet()){
//        for(auto e : v.second->getAdj()){
//            auto reverse = e->getReverse();
//            if(reverse){
//                auto resultingFlow = abs(reverse->getFlow() - e->getFlow());
//                reverse->setFlow(reverse->getFlow() - resultingFlow);
//                e->setFlow(e->getFlow() - resultingFlow);
//                e->getFlow() == 0 ? e->desactivate() : reverse->desactivate();
//            }
//        }
//    }
//}