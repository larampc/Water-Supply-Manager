#ifndef WATERSUPPLYMANAGER_CITY_H
#define WATERSUPPLYMANAGER_CITY_H

#include <string>

/**
 * \class City
 * \brief A custom class to represent a city.
 *
 * This class stores all information of a city.
 */
class City {
private:
    int id;
    std::string code;
    std::string name;
    int demand;
    unsigned population;
public:
    City(int id, std::string code, std::string name, double demand, int population): id(id), code(std::move(code)), name(std::move(name)), demand(demand), population(population) {};
    [[nodiscard]] std::string getName() const;
    [[nodiscard]] int getDemand() const;
    [[nodiscard]] unsigned getPopulation() const;
    [[nodiscard]] int getID() const;
    std::string getCode() const;
    bool operator<(const City& c) const;
};


#endif //WATERSUPPLYMANAGER_CITY_H
