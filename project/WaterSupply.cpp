#include "WaterSupply.h"
#include <fstream>
#include <sstream>
#include <string>
using namespace std;

WaterSupply::WaterSupply() {
    loadCities();
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
        network.addVertex(City(stoi(id), code, city, demand, population));
    }
    citiesFile.close();
}

Graph WaterSupply::getNetwork() {
    return network;
}


