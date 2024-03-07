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
        if (!code.empty()) network.addVertex(code);
    }
    citiesFile.close();
}

Graph WaterSupply::getNetwork() {
    return network;
}

void WaterSupply::loadReservoir() {
    ifstream citiesFile("../dataSetSmall/Reservoirs_Madeira.csv");
    string line;
    getline(citiesFile, line);
    while (getline(citiesFile, line)) {
        string name, id, code, municipality, maxDelivery;
        istringstream iss(line);
        getline(iss, name, ',');
        getline(iss, municipality, ',');
        getline(iss, id, ',');
        getline(iss, code, ',');
        getline(iss, maxDelivery, ',');
        if (!code.empty()) network.addVertex(code);
    }
    citiesFile.close();
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
        if (!code.empty()) network.addVertex(code);
    }
    stationsFile.close();
}


