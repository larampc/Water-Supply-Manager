#include "WaterSupply.h"
#include "Reservoir.h"
#include <fstream>
#include <sstream>
#include <string>
using namespace std;

WaterSupply::WaterSupply() {
    loadCities();
    loadReservoir();
    loadStations();
}

void WaterSupply::loadCities() {
    ifstream citiesFile("../dataSetSmall/Cities_Madeira.csv");
    string line;
    getline(citiesFile, line);
    while (getline(citiesFile, line)) {
        string name, id, code, demand, population;
        istringstream iss(line);
        getline(iss, name, ',');
        getline(iss, id, ',');
        getline(iss, code, ',');
        getline(iss, demand, ',');
        getline(iss, population);
        if (!code.empty()) {
            network.addVertex(code);
            cities.emplace(code, City(stoi(id), code, name, demand, population));
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
        network.addEdge(a, b, stoi(capacity));
        if (!stoi(direction)) {

        }
    }
    pipesFile.close();

}

