#ifndef WATERSUPPLYMANAGER_CITY_H
#define WATERSUPPLYMANAGER_CITY_H

#include "Station.h"

class City {
private:
    int id;
    std::string code;
    std::string name;
    std::string demand;
    std::string population;
public:
    City(int id, std::string code, std::string name, std::string demand, std::string population): id(id), code(code), name(name), demand(demand), population(population) {};
    std::string getName() const;
    std::string getDemand() const;
    std::string getPopulation() const;
};


#endif //WATERSUPPLYMANAGER_CITY_H
