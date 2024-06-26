
#include "City.h"

std::string City::getName() const {
    return name;
}

int City::getDemand() const {
    return demand;
}

unsigned City::getPopulation() const {
    return population;
}

int City::getID() const {
    return id;
}

std::string City::getCode() const{
    return code;
}

bool City::operator<(const City& c) const {
    return id < c.id;
}
