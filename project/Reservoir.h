#ifndef WATERSUPPLYMANAGER_RESERVOIR_H
#define WATERSUPPLYMANAGER_RESERVOIR_H

#include "Node.h"

class Reservoir: public Node{
private:
    std::string name;
    std::string municipality;
    int maxDelivery;
public:
    Reservoir(int id, std::string code, std::string name, std::string municipality, int maxDelivery): Node(id, code), name(name), municipality(municipality), maxDelivery(maxDelivery) {};
    std::string getName() const;
    std::string getMunicipality() const;
    int getDelivery() const;
};


#endif //WATERSUPPLYMANAGER_RESERVOIR_H
