#ifndef WATERSUPPLYMANAGER_RESERVOIR_H
#define WATERSUPPLYMANAGER_RESERVOIR_H

#include "Station.h"

class Reservoir {
private:
    int id;
    std::string code;
    std::string name;
    std::string municipality;
    int maxDelivery;
public:
    Reservoir(int id, std::string code, std::string name, std::string municipality, int maxDelivery): id(id), code(code), name(name), municipality(municipality), maxDelivery(maxDelivery) {};
    std::string getName() const;
    std::string getMunicipality() const;
    int getDelivery() const;
};


#endif //WATERSUPPLYMANAGER_RESERVOIR_H
