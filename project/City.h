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
    City(int id, std::string code, std::string name, std::string demand, std::string population): id(id), code(std::move(code)), name(std::move(name)), demand(std::move(demand)), population(std::move(population)) {};
    [[nodiscard]] std::string getName() const;
    [[nodiscard]] std::string getDemand() const;
    [[nodiscard]] std::string getPopulation() const;
};


#endif //WATERSUPPLYMANAGER_CITY_H
