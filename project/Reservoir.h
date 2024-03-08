#ifndef WATERSUPPLYMANAGER_RESERVOIR_H
#define WATERSUPPLYMANAGER_RESERVOIR_H

#include "Station.h"

class Reservoir {
private:
    int id;
    std::string code;
    std::string name;
    std::string municipality;
    int maxDelivery; // m³/sec
public:
    Reservoir(int id, std::string code, std::string name, std::string municipality, int maxDelivery): id(id), code(std::move(code)), name(std::move(name)), municipality(std::move(municipality)), maxDelivery(maxDelivery) {};
    [[nodiscard]] std::string getName() const;
    [[nodiscard]] std::string getMunicipality() const;
    [[nodiscard]] int getDelivery() const;
};


#endif //WATERSUPPLYMANAGER_RESERVOIR_H
