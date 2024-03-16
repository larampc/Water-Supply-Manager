#include "WaterSupply.h"
#include "Reservoir.h"
#include <fstream>
#include <sstream>
#include <string>
#include <float.h>
#include <climits>

#include <locale>
#include <codecvt>
#include <iostream>
using namespace std;

unsigned readPopulation(string pop){
    string res;
    pop = pop.substr(1,pop.length() - 2);
    for(char c: pop){
        if(c != ',') res.push_back(c);
    }
    return stoi(res);
}

void WaterSupply::load() {
    loadCities();
    loadReservoir();
    loadStations();
    loadPipes();
}

void WaterSupply::loadCities() {
    string path = dataSet? "../dataSet/Cities.csv": "../dataSetSmall/Cities_Madeira.csv";
    setlocale (LC_CTYPE, "C");
    wifstream  file(path);
    file.imbue(std::locale(std::locale(), new std::codecvt_utf8<wchar_t,0x10ffff, std::consume_header>));
    wstring  s;
    getline(file, s);
    while (getline(file, s)) {
        string name, id, code, demand;
        string population;
        istringstream iss(string(s.begin(), s.end()));
        iss.imbue(std::locale(std::locale(), new std::codecvt_utf8<wchar_t,0x10ffff, std::consume_header>));
        getline(iss, name, ',');
        cout << name;
        getline(iss, id, ',');
        getline(iss, code, ',');
        getline(iss, demand, ',');
        getline(iss,population);
        if (!code.empty()) {
            network.addVertex(code);
            cities.emplace(code, City(stoi(id), code, name, stod(demand), readPopulation(population)));
        }
    }
    file.close();
}

Graph WaterSupply::getNetwork() {
    return network;
}

void WaterSupply::loadReservoir() {
    string path = dataSet? "../dataSet/Reservoir.csv": "../dataSetSmall/Reservoirs_Madeira.csv";
    ifstream reservoirsFile(path);
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
    string path = dataSet ? "../dataSet/Stations.csv": "../dataSetSmall/Stations_Madeira.csv";
    ifstream stationsFile(path);
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
    string path = dataSet? "../dataSet/Pipes.csv": "../dataSetSmall/Pipes_Madeira.csv";
    ifstream pipesFile(path);
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

void WaterSupply::getSuperSource() {
    network.addVertex("src");
    for(auto v: reservoirs) {
        network.addEdge("src", v.first, v.second.getDelivery());
    }
}

void WaterSupply::getSuperSink() {
    network.addVertex("sink");
    for(auto v: cities) {
        network.addEdge( v.first, "sink", v.second.getDemand());
    }
}

void WaterSupply::maxFlow() {
    getSuperSource();
    getSuperSink();
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
        total += count;
    }
    cout << "Total " << total << endl;
    network.removeVertex("src");
    network.removeVertex("sink");
}

void WaterSupply::computeAverageAndVarianceOfPipes() {
    int n_edges = 0;
    double sum = 0;
    double max = 0;
    for(auto v: network.getVertexSet()){
        for(Edge* e: v.second->getAdj()){
            sum += (e->getWeight() - e->getFlow());
            if (max < (e->getWeight() - e->getFlow())) max = (e->getWeight() - e->getFlow());
            n_edges++;
        }
    }
    double average = sum / ((double)n_edges);

    cout << "Average (Capacity - Flow): " << average << endl;
    cout << "Max (Capacity - Flow): " << max << endl;

    double square_diff = 0;
    for(auto v: network.getVertexSet()){
        for(Edge* e: v.second->getAdj()){
            square_diff += ((e->getWeight() - e->getFlow()) - average) * ((e->getWeight() - e->getFlow()) - average);
            n_edges++;
        }
    }
    double variance = square_diff / n_edges;

    cout << "Variance (Capacity - Flow): " << variance << endl;
}

void WaterSupply::computeCitiesStatistics() {
    for(auto v: cities) {
        double flow = 0;
        for(Edge* e: network.findVertex(v.first)->getIncoming()) {
            flow += e->getFlow();
        }
        cout << "City " << v.second.getName();
        if ((v.second.getDemand()) < flow) cout << " Over demand by " << flow - (v.second.getDemand()) << "." << endl;
        else if ((v.second.getDemand()) > flow) cout << " Under demand by " << (v.second.getDemand()) - flow << "." << endl;
        else cout << " Exactly on demand. " << v.second.getDemand() << endl;
    }
}

std::unordered_map<std::string, City> WaterSupply::getCities() {
    return cities;
}

std::unordered_map<std::string, Reservoir> WaterSupply::getReservoirs() {
    return reservoirs;
}

std::unordered_map<std::string, Station> WaterSupply::getStations() {
    return stations;
}

string WaterSupply::existsCityByID(int id) {
    for (const auto& c: cities) {
        if (c.second.getID() == id) return c.first;
    }
    return "";
}

bool WaterSupply::existsCityByCode(std::string code) {
    return cities.count(code);
}

string WaterSupply::existsCityByName(std::string name) {
    for (const auto& c: cities) {
        string nameC = c.second.getName();
        transform(nameC.begin(), nameC.end(), nameC.begin(), ::toupper);
        if (nameC == name) return c.first;
    }
    return "";
}

string WaterSupply::existsReservoirByName(std::string name) {
    for (const auto& r: reservoirs) {
        string nameR = r.second.getName();
        transform(nameR.begin(), nameR.end(), nameR.begin(), ::toupper);
        if (nameR == name) return r.first;
    }
    return "";
}

std::string WaterSupply::existsReservoirByID(int id) {
    for (const auto& r: reservoirs) {
        if (r.second.getId() == id) return r.first;
    }
    return "";
}

bool WaterSupply::existsReservoirByCode(std::string code) {
    return reservoirs.count(code);
}

vector<Reservoir> WaterSupply::existsMunicipality(std::string municipality) {
    vector<Reservoir> res;
    for (const auto& r: reservoirs) {
        string mun = r.second.getMunicipality();
        transform(mun.begin(), mun.end(), mun.begin(), ::toupper);
        if (mun == municipality) res.push_back(r.second);
    }
    return res;
}

vector<City> WaterSupply::getCityMaxDemand() {
    int maxDemand = 0;
    vector<City> max;
    for (const auto& c: cities) {
        if (c.second.getDemand() > maxDemand) {
            max.clear();
            max.push_back(c.second);
            maxDemand = c.second.getDemand();
        }
        else if (c.second.getDemand() == maxDemand) {
            max.push_back(c.second);
        }
    }
    return max;
}

vector<City> WaterSupply::getCityMinDemand() {
    int minDemand = DBL_MAX;
    vector<City> max;
    for (const auto &c: cities) {
        if (c.second.getDemand() < minDemand) {
            max.clear();
            max.push_back(c.second);
            minDemand = c.second.getDemand();
        }
        else if (c.second.getDemand() == minDemand) {
            max.push_back(c.second);
        }
    }
    return max;
}

vector<City> WaterSupply::getCityMaxPop() {
    int maxPop = 0;
    vector<City> max;
    for (const auto& c: cities) {
        if (c.second.getPopulation() > maxPop) {
            max.clear();
            max.push_back(c.second);
            maxPop = c.second.getPopulation();
        }
        else if (c.second.getPopulation() == maxPop) {
            max.push_back(c.second);
        }
    }
    return max;
}

vector<City> WaterSupply::getCityMinPop() {
    int minPop = UINT_MAX;
    vector<City> max;
    for (const auto& c: cities) {
        if (c.second.getPopulation() < minPop) {
            max.clear();
            max.push_back(c.second);
            minPop = c.second.getPopulation();
        }
        else if (c.second.getPopulation() == minPop) {
            max.push_back(c.second);
        }
    }
    return max;
}

std::vector<Reservoir> WaterSupply::getReservoirMaxDel() {
    int maxDel = 0;
    vector<Reservoir> max;
    for (const auto& c: reservoirs) {
        if (c.second.getDelivery() > maxDel) {
            max.clear();
            max.push_back(c.second);
            maxDel = c.second.getDelivery();
        }
        else if (c.second.getDelivery() == maxDel) {
            max.push_back(c.second);
        }
    }
    return max;
}

std::vector<Reservoir> WaterSupply::getReservoirMinDel() {
    int maxDel = UINT_MAX;
    vector<Reservoir> max;
    for (const auto& c: reservoirs) {
        if (c.second.getDelivery() < maxDel) {
            max.clear();
            max.push_back(c.second);
            maxDel = c.second.getDelivery();
        }
        else if (c.second.getDelivery() == maxDel) {
            max.push_back(c.second);
        }
    }
    return max;
}

void WaterSupply::setDataSmall() {
    dataSet = false;
}

void WaterSupply::setDataDefault() {
    dataSet = true;
}

