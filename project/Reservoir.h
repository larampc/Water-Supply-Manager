#ifndef WATERSUPPLYMANAGER_RESERVOIR_H
#define WATERSUPPLYMANAGER_RESERVOIR_H

#include <string>

/**
 * \class Reservoir
 * \brief A custom class to represent a Reservoir.
 *
 * This class stores all information of a Reservoir.
 */
class Reservoir {
private:
    int id;
    std::string code;
    std::string name;
    std::string municipality;
    int maxDelivery; // m³/sec
public:
    /**
     * \brief Reservoir constructor.
     *
     * @param id The Reservoir id.
     * @param code The Reservoir code.
     * @param name The Reservoir name.
     * @param municipality The Reservoir municipality.
     * @param maxDelivery The Reservoir max delivery in m³/sec.
     */
    Reservoir(int id, std::string code, std::string name, std::string municipality, int maxDelivery): id(id), code(std::move(code)), name(std::move(name)), municipality(std::move(municipality)), maxDelivery(maxDelivery) {};
    /**
     * \brief Gets the Reservoir name.
     *
     * @return The Reservoir name.
     */
    [[nodiscard]] std::string getName() const;
    /**
     * \brief Gets the Reservoir municipality.
     *
     * @return The Reservoir municipality.
     */
    [[nodiscard]] std::string getMunicipality() const;
    /**
     * \brief Gets the Reservoir max delivery in m³/sec.
     *
     * @return The Reservoir max delivery in m³/sec.
     */
    [[nodiscard]] int getDelivery() const;
    /**
     * \brief Gets the Reservoir ID.
     *
     * @return The Reservoir ID.
     */
    [[nodiscard]] int getId() const;
    /**
     * \brief Gets the Reservoir code.
     *
     * @return The Reservoir code.
     */
    [[nodiscard]] std::string getCode() const;
    /**
     * \brief Less than operator to compare Reservoir IDs.
     *
     * @param reservoir The Reservoir to compare.
     * @return True if this Reservoir ID id lower than the ID of the given Reservoir.
     */
    bool operator<(const Reservoir& reservoir) const;
};


#endif //WATERSUPPLYMANAGER_RESERVOIR_H
