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
        string city, id, code, demand, population;
        istringstream iss(line);
        getline(iss, city, ',');
        getline(iss, id, ',');
        getline(iss, code, ',');
        getline(iss, demand, ',');
        getline(iss, population);
        cities.emplace(code, City(stoi(id), code, city, demand, population));
        if (!code.empty()) network.addVertex(code);
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
        reservoirs.emplace(code, Reservoir(stoi(id), code, name, municipality, stoi(maxDelivery)));
        if (!code.empty()) network.addVertex(code);
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
        stations.emplace(code, Station(stoi(id), code));
        if (!code.empty()) network.addVertex(code);
    }
    stationsFile.close();
}


