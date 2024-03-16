#include "WaterSupply.h"
#include "Reservoir.h"
#include <fstream>
#include <sstream>
#include <string>
using namespace std;

unsigned readPopulation(string pop){
    string res;
    pop = pop.substr(1,pop.length() - 2);
    for(char c: pop){
        if(c != ',') res.push_back(c);
    }
    return stoi(res);
}

WaterSupply::WaterSupply() {
    loadCities();
    loadReservoir();
    loadStations();
    loadPipes();
}

void WaterSupply::loadCities() {
    ifstream citiesFile("../dataSetSmall/Cities_Madeira.csv");
    string line;
    getline(citiesFile, line);
    while (getline(citiesFile, line)) {
        string name, id, code, demand;
        string population;
        istringstream iss(line);
        getline(iss, name, ',');
        getline(iss, id, ',');
        getline(iss, code, ',');
        getline(iss, demand, ',');
        getline(iss,population);
        if (!code.empty()) {
            network.addVertex(code);
            cities.emplace(code, City(stoi(id), code, name, demand, readPopulation(population)));
        }
    }
    citiesFile.close();
}

Graph WaterSupply::getNetwork() {
    return network;
}

void WaterSupply::loadReservoir() {
    ifstream reservoirsFile("../dataSetSmall/Reservoirs_Madeira.csv");
    string line;
    getline(reservoirsFile, line);
    while (getline(reservoirsFile, line)) {
        string name, id, code, municipality, maxDelivery;
        istringstream iss(line);
        getline(iss, name, ',');
        getline(iss, municipality, ',');
        getline(iss, id, ',');
        getline(iss, code, ',');
        getline(iss, maxDelivery, ',');
        if (!code.empty()) {
            network.addVertex(code);
            reservoirs.emplace(code, Reservoir(stoi(id), code, name, municipality, stoi(maxDelivery)));
        }
    }
    reservoirsFile.close();
}

void WaterSupply::loadStations() {
    ifstream stationsFile("../dataSetSmall/Stations_Madeira.csv");
    string line;
    getline(stationsFile, line);
    while (getline(stationsFile, line)) {
        string id, code;
        istringstream iss(line);
        getline(iss, id, ',');
        getline(iss, code, ',');
        if (!code.empty()) {
            network.addVertex(code);
            stations.emplace(code, Station(stoi(id), code));
        }
    }
    stationsFile.close();
}

City WaterSupply::getCity(std::string code) {
    if (cities.find(code)!=cities.end()) return cities.at(code);
}

Reservoir WaterSupply::getReservoir(std::string code) {
    if (reservoirs.find(code)!=reservoirs.end()) return reservoirs.at(code);
}

Station WaterSupply::getStation(std::string code) {
    if (stations.find(code)!=stations.end()) return stations.at(code);
}

void WaterSupply::loadPipes() {
    ifstream pipesFile("../dataSetSmall/Pipes_Madeira.csv");
    string line;
    getline(pipesFile, line);
    while (getline(pipesFile, line)) {
        string a, b, capacity, direction;
        istringstream iss(line);
        getline(iss, a, ',');
        getline(iss, b, ',');
        getline(iss, capacity, ',');
        getline(iss, direction);
        if (stoi(direction)) network.addEdge(a, b, stoi(capacity));
        else network.addBidirectionalEdge(a,b,stoi(capacity));
    }
    pipesFile.close();
}

//bool bfs_aux(Graph *g, std::string source, std::string dest) {
//    Vertex* s = g->findVertex(source);
//    s->setPath(nullptr);
//    if (s == nullptr) {
//        return false;
//    }
//    // Set that no vertex has been visited yet
//    for (auto v : g->getVertexSet()) {
//        v.second->setVisited(false);
//    }
//    bool flag = false;
//    // Perform the actual BFS using a queue
//    std::queue<Vertex *> q;
//    q.push(s);
//    s->setVisited(true);
//    while (!q.empty()) {
//        auto v = q.front();
//        q.pop();
//        for (Edge* e : v->getAdj()) {
//            if (e->getFlow() < e->getWeight()) {
//                Vertex* w = e->getDest();
//                if (!w->isVisited()) {
//                    w->setPath(e);
//                    q.push(w);
//                    w->setVisited(true);
//                }
//                if (w->getInfo() == dest) {
//                    flag = true;
//                    break;
//                }
//            }
//        }
//        if (flag) break;
//        for (Edge* e : v->getIncoming()) {
//            if (e->getFlow() > 0) {
//                Vertex* w = e->getOrig();
//                if (!w->isVisited()) {
//                    w->setPath(e);
//                    q.push(w);
//                    w->setVisited(true);
//                }
//                if (w->getInfo() == dest) {
//                    flag = true;
//                    break;
//                }
//            }
//        }
//        if (flag) break;
//    }
//    return flag;
//}
//
//void edmondsKarp(Graph *g, std::string source, std::string target) {
//    Vertex* start = g->findVertex(source);
//    for (auto v: g->getVertexSet()) {
//        if (v.first.substr(0,1) == "R") v.second->setVisited(1);
//        for (Edge* e: v.second->getAdj()) {
//            e->setFlow(0);
//        }
//    }
//    while (bfs_aux(g, source, target)) {
//        Vertex* st = g->findVertex(target);
//        int min = INT_MAX;
//        while (st != start) {
//            if (st->getPath()->getWeight() < min) min = st->getPath()->getWeight();
//            if (st == st->getPath()->getOrig()) st = st->getPath()->getDest();
//            else st = st->getPath()->getOrig();
//        }
//        Vertex* st2 = g->findVertex(target);
//        while (st2 != start) {
//            int prev = st2->getPath()->getFlow();
//            if (st2->getPath()->getOrig() == st2) {
//                st2->getPath()->setFlow(prev-min);
//                st2 = st2->getPath()->getDest();
//            }
//            else {
//                st2->getPath()->setFlow(prev+min);
//                st2 = st2->getPath()->getOrig();
//            }
//        }
//    }
//}
//
//void WaterSupply::maxFlow(std::string target) {
//    edmondsKarp(&network, "R_1", target);
//    Vertex* start = network.findVertex("R_1");
//    Vertex* end = network.findVertex(target);
//    while (start != end) {
//        cout << end->getPath()->getOrig()->getInfo() << endl;
//        end = end->getPath()->getOrig();
//    }
//}

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

bool findAugPath(Graph* g, Vertex* src, Vertex* target){
    for(auto v : g->getVertexSet()) v.second->setVisited(false); //reset
    std::queue<Vertex*> aux; aux.push(src);
    src->setVisited(true);
    while(!aux.empty()){
        Vertex* v = aux.front();
        aux.pop();
        for(Edge* adj : v->getAdj()){
            auto w = adj->getDest();
            if(!w->isVisited() && residualC(adj, true) > 0) {
                w->setPath(adj);
                aux.push(w);
                w->setVisited(true);
                if(w == target){
                    return true;
                }
            }
        }
    }
    return false;
}

void getSuperSource(Graph* g) {
    g->addVertex("src");
    for(auto v: g->getVertexSet()){
        if (v.first.substr(0,1) == "R") {
            g->addEdge("src", v.first, INF);
        }
    }
}

void getSuperSink(Graph* g) {
    g->addVertex("sink");
    for(auto v: g->getVertexSet()){
        if (v.first.substr(0,1) == "C") {
            g->addEdge(v.first, "sink", INF);
        }
    }
}

void WaterSupply::maxFlow() {
    getSuperSource(&network);
    getSuperSink(&network);
    for(auto v: network.getVertexSet()){
        for(Edge* e: v.second->getAdj()){
            e->setFlow(0);
        }
    }
    Vertex* src = network.findVertex("src");
    Vertex* sink = network.findVertex("sink");
    while(findAugPath(&network, src, sink)){
        double cf = getCf(src, sink);
        augmentPath(src, sink, cf);
    }
    int total = 0;
    for (auto v: cities) {
        Vertex* end = network.findVertex(v.first);
        int count = 0;
        for (Edge* e: end->getIncoming()) {
            count += e->getFlow();
        }
        cout << end->getInfo() << " " << count << endl;
        total += count;
    }
    cout << "Total" << total;
    network.removeVertex("src");
    network.removeVertex("sink");
}

