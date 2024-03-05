#ifndef WATERSUPPLYMANAGER_CITY_H
#define WATERSUPPLYMANAGER_CITY_H

#include "Node.h"

class City: public Node{
private:
    std::string name;
    std::string demand;
    std::string population;
public:
    City(int id, std::string code, std::string name, std::string demand, std::string population): Node(id, code), name(name), demand(demand), population(population) {};
    std::string getName() const;
    std::string getDemand() const;
    std::string getPopulation() const;
};


#endif //WATERSUPPLYMANAGER_CITY_H
