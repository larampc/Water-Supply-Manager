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
#include <iomanip>

using namespace std;

unsigned readPopulation(string pop){
    string res;
    pop = pop.substr(1,pop.length() - 2);
    for(char c: pop){
        if(c != ',') res.push_back(c);
    }
    return stoi(res);
}

/********************** Load  ****************************/

void WaterSupply::load() {
    loadCities();
    loadReservoir();
    loadStations();
    loadPipes();
}

void WaterSupply::loadCities() {
    string path = dataSet? "../dataSet/Cities.csv": "../dataSetSmall/Cities_Madeira.csv";
#ifdef _WIN32
    setlocale (LC_ALL, "");
    wifstream  file(path);
    file.imbue(std::locale(std::locale(), new std::codecvt_utf8<wchar_t,0x10ffff, std::consume_header>));
    wstring  s;
#else
    ifstream  file(path);
    string  s;
#endif
    getline(file, s);
    while (getline(file, s)) {
        string name, id, code, demand;
        string population;
        istringstream iss(string(s.begin(), s.end()));
        getline(iss, name, ',');
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

void WaterSupply::loadReservoir() {
    string path = dataSet? "../dataSet/Reservoir.csv": "../dataSetSmall/Reservoirs_Madeira.csv";
#ifdef _WIN32
    setlocale (LC_ALL, "");
    wifstream  reservoirsFile(path);
    reservoirsFile.imbue(std::locale(std::locale(), new std::codecvt_utf8<wchar_t,0x10ffff, std::consume_header>));
    wstring line;
#else
    ifstream  reservoirsFile(path);
    string  line;
#endif
    getline(reservoirsFile, line);
    while (getline(reservoirsFile, line)) {
        string name, id, code, municipality, maxDelivery;
        istringstream iss(string(line.begin(), line.end()));
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
    ifstream  stationsFile(path);
    string line;
    getline(stationsFile, line);
    while (getline(stationsFile, line)) {
        string id, code;
        istringstream iss(string(line.begin(), line.end()));
        getline(iss, id, ',');
        getline(iss, code, ',');
        if (!code.empty()) {
            network.addVertex(code);
            stations.emplace(code, Station(stoi(id), code));
        }
    }
    stationsFile.close();
}

void WaterSupply::loadPipes() {
    string path = dataSet? "../dataSet/Pipes.csv": "../dataSetSmall/Pipes_Madeira.csv";
    ifstream  pipesFile(path);
    string line;
    getline(pipesFile, line);
    while (getline(pipesFile, line)) {
        string a, b, capacity, direction;
        istringstream iss(string(line.begin(), line.end()));
        getline(iss, a, ',');
        getline(iss, b, ',');
        getline(iss, capacity, ',');
        getline(iss, direction);
        if (stoi(direction)) network.addEdge(a, b, stoi(capacity));
        else network.addBidirectionalEdge(a,b,stoi(capacity));
    }
    pipesFile.close();
}

/********************** Getters  ****************************/

Graph WaterSupply::getNetwork() {
    return network;
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

std::unordered_map<std::string, City> WaterSupply::getCities() {
    return cities;
}

std::unordered_map<std::string, Reservoir> WaterSupply::getReservoirs() {
    return reservoirs;
}

std::unordered_map<std::string, Station> WaterSupply::getStations() {
    return stations;
}

/********************** Setters  ****************************/

void WaterSupply::setDataSmall() {
    dataSet = false;
}

void WaterSupply::setDataDefault() {
    dataSet = true;
}

void WaterSupply::setSuperSource() {
    network.addVertex("src");
    for(auto v: reservoirs) {
        network.addEdge("src", v.first, v.second.getDelivery());
    }
}

void WaterSupply::setSuperSink() {
    network.addVertex("sink");
    for(auto v: cities) {
        network.addEdge( v.first, "sink", v.second.getDemand());
    }
}


void WaterSupply::setInfSuperSink() {
    network.addVertex("sink");
    for(auto v: cities) {
        network.addEdge( v.first, "sink", INF);
    }
}

void WaterSupply::setSuperWithout(std::string reservoir) {
    network.addVertex("src");
    for(auto v: reservoirs) {
        if (v.first == reservoir) network.addEdge("src", v.first, 0);
        else network.addEdge("src", v.first, v.second.getDelivery());
    }
}

/********************** Checkers  ****************************/

string WaterSupply::existsCityByID(int id) {
    for (const auto& c: cities) {
        if (c.second.getID() == id) return c.first;
    }
    return "";
}

bool WaterSupply::existsCityByCode(std::string code) {
    return cities.count(code);
}

bool compareString(string s1, string s2) {
    int count = 0;
    for (int i = 0; i < s1.size(); i++) {
        if (s1[i] != s2[i]) count++;
    }
    return (count <= 2);
}

string WaterSupply::existsCityByName(std::string name) {
    for (const auto& c: cities) {
        string nameC = c.second.getName();
        transform(nameC.begin(), nameC.end(), nameC.begin(), ::toupper);
        if (compareString(nameC, name)) return c.first;
    }
    return "";
}

string WaterSupply::existsReservoirByName(std::string name) {
    for (const auto& r: reservoirs) {
        string nameR = r.second.getName();
        transform(nameR.begin(), nameR.end(), nameR.begin(), ::toupper);
        if (compareString(nameR, name)) return r.first;
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
        if (compareString(municipality, mun)) res.push_back(r.second);
    }
    return res;
}

/********************** Statistics  ****************************/

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
    ostringstream oss;
    oss << "City - Flow\n\n";
    for(auto v: cities) {
        double flow = 0;
        for(Edge* e: network.findVertex(v.first)->getIncoming()) {
            flow += e->getFlow();
        }
        oss << left << setw(4) << v.second.getCode() << " - " << setw(6) << v.second.getDemand();
        if ((v.second.getDemand()) < flow) oss << " (Overflow by " << flow - (v.second.getDemand()) << ")";
        else if ((v.second.getDemand()) > flow) oss << " (Underflow by " << (v.second.getDemand()) - flow << ")";
        oss << "\n";
    }
    cout << oss.str() << "\n";
    OutputToFile("../output/MaxFlow", oss.str());
}

int WaterSupply::computeCityFlow(std::string city) {
    Vertex* end = network.findVertex(city);
    int count = 0;
    for (Edge* e: end->getIncoming()) {
        count += e->getFlow();
    }
    return count;
}

int WaterSupply::computeMaxFlow() {
    int total = 0;
    for (auto v: cities) {
        Vertex* end = network.findVertex(v.first);
        int count = 0;
        for (Edge* e: end->getIncoming()) {
            count += e->getFlow();
        }
        total += count;
    }
    return total;
}

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
    if (! w->isVisited() && residual > 0) {
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

void WaterSupply::maxFlow(string source, string sink) {
    Vertex* src = network.findVertex(source);
    Vertex* snk = network.findVertex(sink);
    while(findAugPath(&network, src, snk)){
        double cf = getCf(src, snk);
        augmentPath(src, snk, cf);
    }
}

/********************** MaxFlow Options  ****************************/

void WaterSupply::optimalResMaxFlow() {
    setSuperSource();
    setSuperSink();
    for(auto v: network.getVertexSet()){
        for(Edge* e: v.second->getAdj()){
            e->setFlow(0);
        }
    }
    maxFlow("src", "sink");
    network.removeVertex("src");
    network.removeVertex("sink");
}

void WaterSupply::optimalExcessMaxFlow() {
    setSuperSource();
    setSuperSink();
    for(auto v: network.getVertexSet()){
        for(Edge* e: v.second->getAdj()){
            e->setFlow(0);
        }
    }
    maxFlow("src", "sink");
    network.removeVertex("sink");
    setInfSuperSink();
    maxFlow("src", "sink");
    network.removeVertex("src");
    network.removeVertex("sink");
}

void WaterSupply::optimalExcessCityMaxFlow(std::string target) {
    setSuperSource();
    setSuperSink();
    Vertex* targ = network.findVertex(target);
    for (auto e: targ->getAdj()) {                          //only one edge but verify if it's sink
        if (e->getDest()->getInfo() == "sink") e->setWeight(INF);
    }
    for(auto v: network.getVertexSet()){
        for(Edge* e: v.second->getAdj()){
            e->setFlow(0);
        }
    }
    maxFlow("src", "sink");
    network.removeVertex("src");
    network.removeVertex("sink");
}

void WaterSupply::cityMaxFlow(std::string target) {
    setSuperSource();
    for(auto v: network.getVertexSet()){
        for(Edge* e: v.second->getAdj()){
            e->setFlow(0);
        }
    }
    maxFlow("src", target);
    network.removeVertex("src");
}

void WaterSupply::optimalDelete(std::string reservoir) {
    setSuperWithout(reservoir);
    setSuperSink();
    for(auto v: network.getVertexSet()){
        for(Edge* e: v.second->getAdj()){
            e->setFlow(0);
        }
    }
    maxFlow("src", "sink");
    network.removeVertex("src");
    network.removeVertex("sink");
}

void WaterSupply::OutputToFile(const string& fileName, const string& text){
    ofstream out(fileName);
    out << text;
    out.close();
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

void WaterSupply::reverseMaxFlow(string source, string sink) {
    Vertex* src = network.findVertex(source);
    Vertex* snk = network.findVertex(sink);
    while(reverseFindAugPath(&network, src, snk)){
        double cf = reverseGetCf(src, snk);
        reverseAugmentPath(src, snk, cf);
    }
}

void WaterSupply::deleteReservoirMaxReverse(std::string reservoir) {
    setSuperSource();
    setSuperSink();
    for(auto v: network.getVertexSet()){
        for(Edge* e: v.second->getAdj()){
            e->setFlow(0);
        }
    }
    maxFlow("src", "sink");
    reverseMaxFlow(reservoir, "sink");
    for(auto v: network.findVertex("src")->getAdj()) {
        if (v->getDest()->getInfo() == reservoir) v->setWeight(0);
    }
    maxFlow("src", "sink");
    network.removeVertex("src");
    network.removeVertex("sink");
}

/********************** Delete with paths  ****************************/

void WaterSupply::augmentPathList(Vertex* source, Vertex* target, double cf) {
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
        e.second->addPath(free.empty()? paths.size(): free.at(0));
        e.second->getDest()->addPath(free.empty()? paths.size(): free.at(0));
        e.second->getOrig()->addPath(free.empty()? paths.size(): free.at(0));
    }
    paths.emplace(free.empty()? paths.size(): free.at(0), pair<double, vector<pair<bool, Edge*>>>{make_pair(cf, path)});
    if (!free.empty()) free.erase(free.begin());
}

void WaterSupply::maxFlowWithList() {
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


void WaterSupply::resetPaths(std::unordered_set<int> pat) {
    for (auto k: pat) {
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

void WaterSupply::deleteReservoir(std::string reservoir) {
    Vertex* v = network.findVertex(reservoir);
    resetPaths(v->getPaths());
    for(auto v: network.findVertex("src")->getAdj()) {
        if (v->getDest()->getInfo() == reservoir) v->setWeight(0);
    }
    maxFlowWithList();
}

void WaterSupply::verification() {
    int count = 0;
    paths.clear();
    setSuperSource();
    setSuperSink();
    maxFlowWithList();
    for (auto c: reservoirs) {
        cout << c.first << " ";
        deleteReservoir(c.first);
        int g = computeMaxFlow();
        cout << " Given: " << g << endl;
    }
    cout << count;
    network.removeVertex("src");
    network.removeVertex("sink");
}