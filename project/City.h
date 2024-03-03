#ifndef WATERSUPPLYMANAGER_CITY_H
#define WATERSUPPLYMANAGER_CITY_H

#include "Node.h"

class City: public Node{
private:
    std::string name;
    int demand;
    int population;
public:
    City(int id, std::string code, std::string name, int demand, int population): Node(id, code), name(name), demand(demand), population(population) {};
    std::string getName() const;
    int getDemand() const;
    int getPopulation() const;
};


#endif //WATERSUPPLYMANAGER_CITY_H
