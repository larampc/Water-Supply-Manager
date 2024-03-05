#ifndef WATERSUPPLYMANAGER_WATERSUPPLY_H
#define WATERSUPPLYMANAGER_WATERSUPPLY_H
#include "City.h"
#include "datastructures/Graph.h"

class WaterSupply {
private:
    Graph network;
public:
    WaterSupply();
    void loadCities();
    void loadReservoir();
    void loadStations();
    Graph getNetwork();
};


#endif //WATERSUPPLYMANAGER_WATERSUPPLY_H
