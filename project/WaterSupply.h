#ifndef WATERSUPPLYMANAGER_WATERSUPPLY_H
#define WATERSUPPLYMANAGER_WATERSUPPLY_H
#include "City.h"
#include "datastructures/Graph.h"

class WaterSupply {
private:
    Graph network;
    unordered_map<std::string, City> cities;
    unordered_map<std::string, City> reservoirs;
    unordered_map<std::string, City> stations;
    void loadCities();
    void loadReservoir();
    void loadStations();
public:
    WaterSupply();
    Graph getNetwork();
};


#endif //WATERSUPPLYMANAGER_WATERSUPPLY_H
