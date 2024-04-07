
#ifndef WATERSUPPLYMANAGER_STATION_H
#define WATERSUPPLYMANAGER_STATION_H

#include <string>

/**
 * \class Station
 * \brief A custom class to represent a Station.
 *
 * This class stores all information of a Station.
 */
class Station {
private:
    int id;
    std::string code;
public:
    /**
     * \brief Station constructor.
     *
     * @param id The Station id.
     * @param code The Station code.
     */
    Station(int id, std::string code): id(id), code(std::move(code)) {};
    /**
     * \brief Gets the Station ID.
     *
     * @return The Station ID.
     */
    [[nodiscard]] int getId() const;
    /**
     * \brief Gets the Station code.
     *
     * @return The Station code.
     */
    [[nodiscard]] std::string getCode() const;
};


#endif //WATERSUPPLYMANAGER_STATION_H
