#ifndef WATERSUPPLYMANAGER_WATERSUPPLY_H
#define WATERSUPPLYMANAGER_WATERSUPPLY_H
#include "City.h"
#include "datastructures/Graph.h"
#include "Reservoir.h"
#include "Station.h"
#include "unordered_map"
#include "MaxFlow.h"

/**
 * \class WaterSupply
 * \brief This class stores all the data and performs different functions on it.
 *
 * This class initializes, stores and modifies the Graph, all the City data, all the Reservoir data and all the Station data.
 */
class WaterSupply {
private:
    Graph network;
    std::unordered_map<std::string, City> cities;
    std::unordered_map<std::string, Reservoir> reservoirs;
    std::unordered_map<std::string, Station> stations;

    /**
     * \brief Loads all the City data from the file in the given file path.
     *
     * @param path The file path of the file to load the City data from.
     */
    void loadCities(std::string path);
    /**
     * \brief Loads all the Reservoir data from the file in the given file path.
     *
     * @param path The file path of the file to load the Reservoir data from.
     */
    void loadReservoir(std::string path);
    /**
     * \brief Loads all the Station data from the file in the given file path.
     *
     * @param path The file path of the file to load the Station data from.
     */
    void loadStations(std::string path);
    /**
     * \brief Loads all the Pipe data from the file in the given file path.
     *
     * @param path The file path of the file to load the Pipe data from.
     */
    void loadPipes(std::string path);

public:
    /**
     * \brief Parses the Cities, pipes, reservoirs and stations input files into appropriate data structures.
     *
     * @param citiesPath The path of the cities information input file.
     * @param reservoirsPath The path of the reservoirs information input file.
     * @param pipesPath The path of the pipes information input file.
     * @param stationsPath The path of the stations information input file.
     *
     */
    void load(std::string citiesPath, std::string reservoirsPath, std::string pipesPath, std::string stationsPath);

    /********************** Setters  ****************************/
    /**
     * \brief Creates a superSource vertex connected to each reservoir by an Edge with capacity equal to their max Delivery.
     */
    void addSuperSource();
    /**
     * \brief Creates a superSink vertex connected to each city by an Edge with capacity equal to the city's demand.
     */
    void addSuperSink();
    /**
     * \brief Creates a superSink vertex connected to each city by an Edge with infinite capacity.
     */
    void setInfSuperSink();

    /********************** Getters  ****************************/
    /**
     * \brief Gets the Graph of the network.
     *
     * @return The Graph of the network.
     */
    Graph* getNetwork();
    /**
     * \brief Gets the City with the specified code.
     *
     * @param code The code of the City to get.
     * @return The City with the specified code.
     */
    City getCity(const std::string& code);
    /**
     * \brief Gets the Reservoir with the specified code.
     *
     * @param code The code of the Reservoir to get.
     * @return The Reservoir with the specified code.
     */
    Reservoir getReservoir(const std::string& code);
    /**
     * \brief Gets all the City of the network.
     *
     * @return A mapping of code to City of all City in the network.
     */
    std::unordered_map<std::string, City> getCities();
    /**
     * \brief Gets all the Reservoir of the network.
     *
     * @return A mapping of code to Reservoir of all Reservoir in the network.
     */
    std::unordered_map<std::string, Reservoir> getReservoirs();
    /**
     * \brief Gets all the Station of the network.
     *
     * @return A mapping of codes to Station of all Station in the network.
     */
    std::unordered_map<std::string, Station> getStations();

    /********************** Checkers  ****************************/
    /**
     * \brief Checks if exists a City with the given ID.
     *
     * @param id The ID to check.
     * @return The City code of the City with the given ID or empty if invalid ID.
     */
    std::string existsCityByID(int id);
    /**
     * \brief Checks if exists a City with the given code.
     *
     * @param code The code to check.
     * @return True if exists a City with the given code, false otherwise.
     */
    bool existsCityByCode(const std::string& code);
    /**
     * \brief Checks if exists a City with the given name.
     *
     * @param name The name to check.
     * @return The City code of the City with the given name or empty if invalid name.
     */
    std::string existsCityByName(const std::string& name);
    /**
     * \brief Checks if exists a Reservoir with the given name.
     *
     * @param name The name to check.
     * @return The Reservoir code of the Reservoir with the given name or empty if invalid name.
     */
    std::string existsReservoirByName(const std::string& name);
    /**
     * \brief Checks if exists a Reservoir with the given ID.
     *
     * @param id The ID to check.
     * @return The Reservoir code of the Reservoir with the given ID or empty if invalid ID.
     */
    std::string existsReservoirByID(int id);
    /**
     * \brief Checks if exists a Reservoir with the given code.
     *
     * @param code The code to check.
     * @return True if exists a Reservoir with the given code, false otherwise.
     */
    bool existsReservoirByCode(const std::string& code);
    /**
     * \brief Checks if exists any Reservoir with the given municipality.
     *
     * @param municipality The municipality to check.
     * @return The Reservoir code of all the Reservoir with the given municipality or empty if invalid municipality.
     */
    std::vector<Reservoir> existsMunicipality(const std::string& municipality);

    /********************** Statistics  ****************************/
    /**
     * \brief Gets all City with the highest demand.
     *
     * @return A vector of all City with the highest demand.
     */
    std::vector<City> getCityMaxDemand();
    /**
     * \brief Gets all City with the lowest demand.
     *
     * @return A vector of all City with the lowest demand.
     */
    std::vector<City> getCityMinDemand();
    /**
     * \brief Gets all City with the highest population.
     *
     * @return A vector of all City with the highest population.
     */
    std::vector<City> getCityMaxPop();
    /**
     * \brief Gets all City with the lowest population.
     *
     * @return A vector of all City with the lowest population.
     */
    std::vector<City> getCityMinPop();
    /**
     * \brief Gets all Reservoir with the highest max delivery.
     *
     * @return A vector of all Reservoir with the highest max delivery.
     */
    std::vector<Reservoir> getReservoirMaxDel();
    /**
     * \brief Gets all Reservoir with the lowest max demand.
     *
     * @return A vector of all Reservoir with the lowest max demand.
     */
    std::vector<Reservoir> getReservoirMinDel();
    /**
    * \brief Computes the maximum difference (capacity - flow) of all pipes in the network.
    *
    * @return The maximum difference (capacity - flow) of all pipes in the network.
    */
    double computeMaxDiffCapacityFlow();
    /**
     * \brief Computes the network average of the differences (capacity - flow) of all pipes.
     *
     * @return Computes the network average of the differences (capacity - flow) of all pipes.
     */
    double computeAverageDiffCapacityFlow();
    /**
     * \brief Computes the network variance with respect to the difference (capacity - flow) of each pipe.
     *
     * @param average The global network (capacity - flow) average of all pipes.
     * @return The global network variance with respect to the difference (capacity - flow).
     */
    double computeVarianceDiffCapacityFlow(double average);
    /**
     * \brief Computes the network flow value.
     *
     * @return The network flow value.
     */
    int computeFlow();
    /**
     * \brief Computes a given City's incoming flow value.
     *
     * @param city The City whose incoming flow will be computed.
     * @return The City's incoming flow value.
     */
    int computeCityFlow(const std::string& city);

    /********************** MaxFlow  ****************************/
    /**
     * \brief Sets up and calls the maxflow function of MaxFlow.
     */
    void maxFlow();
    /**
     * \brief Sets up the sink and source Vertex and calls the maxflow function of MaxFlow to perform a maxflow with excess.
     */
    void maxFlowWithExcess();
    /**
     * \brief Sets up the sink and source Vertex and calls the maxflow function of MaxFlow to perform a maxflow with excess to all the given City only.
     *
     * @param target Vector of the City to add excess flow.
     */
    void maxFlowWithExcessToCities(const std::vector<std::string> &target);
    /**
     * \brief Calls the maxflow function of MaxFlow to perform a maxflow with sink of only the City with the given code.
     *
     * @param target The code of the City sink.
     */
    void maxFlowToCity(const std::string& target);

    /********************** MaxFlow Reverse ****************************/
    /**
     * \brief Deletes the given Reservoir and recomputes the max flow using the reverseMaxFlow method.
     *
     * @param reservoir The Reservoir to delete.
     */
    void deleteReservoirMaxReverse(const std::string& reservoir);
    /**
     * \brief Outputs the given string to the file with the given file name.
     *
     * @param fileName The file name of the file to output to.
     * @param text The string to output to the given file.
     */
    static void OutputToFile(const std::string &fileName, const std::string &text);
    /**
     * \brief Checks if exists a Station with the given code.
     *
     * @param code The code to check.
     * @return True if exists a Station with the given code, false otherwise.
     */
    bool existsStationByCode(const std::string& code);
    /**
     * \brief Checks if exists a Pipe with the given source and destination.
     *
     * @param source The source to check.
     * @param dest The destination to check.
     * @return True if exists a Pipe with the given source and destination, false otherwise.
     */
    bool existsPipe(const std::string& source, const std::string& dest);
    /**
     * \brief Checks if exists a Reservoir, City or Station with the given code.
     *
     * @param code The code to check.
     * @return True if exists a Reservoir, City or Station with the given code, false otherwise.
     */
    bool existsCode(const std::string& code);
    /**
     * \brief Activates all deactivated Vertex.
     */
    void activateAll();
    /**
     * \brief Transforms all bidirectional Edge to be one directional without altering the current flow of the Graph.
     *
     * @return The deactivated part of all the bidirectional Edge.
     */
    std::vector<Edge*> transformBidirectionalEdges();
    /**
     * \brief Balances the demand - flow across the Graph.
     */
    void balancingViaMinCost();
    /**
     * \brief Finds the shortest path to the given City Vertex using the given function to calculate the distance.
     *
     * @param city The City vertex to calculate the shortest path to.
     * @param func The function to calculate the distance.
     * @return The shortest path to the given City Vertex using the given function to calculate the distance.
     * \par Complexity
     * O(V+E) in which V is the number of vertex and E the number of edges of the Graph.
     */
    std::vector<Edge *> getShortestPathTo(Vertex* city, double (*func)(Edge*));
    /**
     * \brief Checks if the given path has any flow.
     *
     * @param path The path to check.
     * @return True if the given path has any flow, false otherwise.
     */
    static bool PathHasFlow(std::vector<Edge*> path);
    /**
     * \brief Sets all Edge from City to super sink capacity to the respective City demand.
     */
    void setSuperSinkWithDemand();
    /**
     * \brief Calculates the optimal max flow to the given City list ignoring every other City.
     *
     * @param cityList The City list to calculate the optimal max flow to.
     */
    void optimalCityMaxFlow(const std::vector<std::string> &cityList);
    /**
     * \brief Sets all Edge from City to super sink capacity to 0.
     */
    void setSuperSinkNull();
};


#endif //WATERSUPPLYMANAGER_WATERSUPPLY_H
