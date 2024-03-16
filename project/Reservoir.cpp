
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

int Reservoir::getId() const {
    return id;
}

std::string Reservoir::getCode() const {
    return code;
}
