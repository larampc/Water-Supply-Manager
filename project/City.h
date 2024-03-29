#ifndef WATERSUPPLYMANAGER_CITY_H
#define WATERSUPPLYMANAGER_CITY_H

#include <string>

/**
 * \class City
 * \brief A custom class to represent a City.
 *
 * This class stores all information of a City.
 */
class City {
private:
    int id;
    std::string code;
    std::string name;
    double demand;
    unsigned population;
public:
    /**
     * \brief City constructor.
     *
     * @param id The City id.
     * @param code The City code.
     * @param name The City name.
     * @param demand The City demand.
     * @param population The City population.
     */
    City(int id, std::string code, std::string name, double demand, unsigned population): id(id), code(std::move(code)), name(std::move(name)), demand(demand), population(population) {};
    /**
     * \brief Gets the City name.
     *
     * @return The City name.
     */
    [[nodiscard]] std::string getName() const;
    /**
     * \brief Gets the City demand.
     *
     * @return The City demand.
     */
    [[nodiscard]] int getDemand() const;
    /**
     * \brief Gets the City population.
     *
     * @return The City population.
     */
    [[nodiscard]] unsigned getPopulation() const;
    /**
     * \brief Gets the City ID.
     *
     * @return The City ID.
     */
    [[nodiscard]] int getID() const;
    /**
     * \brief Gets the City code.
     *
     * @return The City code.
     */
    [[nodiscard]] std::string getCode() const;
    /**
     * \brief Less than operator to compare City IDs.
     *
     * @param c The City to compare.
     * @return True if this City ID id lower than the ID of the given City.
     */
    bool operator<(const City& c) const;
};


#endif //WATERSUPPLYMANAGER_CITY_H
