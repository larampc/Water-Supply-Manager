
#include "Reservoir.h"


std::string Reservoir::getName() const {
    return name;
}

std::string Reservoir::getMunicipality() const {
    return municipality;
}

int Reservoir::getDelivery() const {
    return maxDelivery;
}
