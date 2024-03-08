
#ifndef WATERSUPPLYMANAGER_STATION_H
#define WATERSUPPLYMANAGER_STATION_H

#include <string>

class Station {
private:
    int id;
    std::string code;
public:
    Station(int id, std::string code): id(id), code(std::move(code)) {};
    [[nodiscard]] int getId() const;
    [[nodiscard]] std::string getCode() const;
};


#endif //WATERSUPPLYMANAGER_STATION_H
