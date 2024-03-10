#ifndef WATERSUPPLYMANAGER_CITY_H
#define WATERSUPPLYMANAGER_CITY_H

#include <string>

class City {
private:
    int id;
    std::string code;
    std::string name;
    std::string demand;
    unsigned population;
public:
    City(int id, std::string code, std::string name, std::string demand, int population): id(id), code(std::move(code)), name(std::move(name)), demand(std::move(demand)), population(population) {};
    [[nodiscard]] std::string getName() const;
    [[nodiscard]] std::string getDemand() const;
    [[nodiscard]] unsigned getPopulation() const;
};


#endif //WATERSUPPLYMANAGER_CITY_H
