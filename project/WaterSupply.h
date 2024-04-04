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
    std::string existsCityByID(int id);
    bool existsCityByCode(const std::string& code);
    std::string existsCityByName(const std::string& name);
    std::string existsReservoirByName(const std::string& name);
    std::string existsReservoirByID(int id);
    bool existsReservoirByCode(const std::string& code);
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
    void deleteReservoirMaxReverse(const std::string& reservoir);

    static void OutputToFile(const std::string &fileName, const std::string &text);

    bool existsStationByCode(const std::string& code);

    bool existsPipe(const std::string& source, const std::string& dest);
    bool existsCode(const std::string& code);

    void activateAll();

    void exportToFile(bool flow);

    std::vector<Edge*> transformBidirectionalEdges();

    void balancingViaMinCost();

    std::vector<Edge *> getShortestPathTo(Vertex* city, double (*func)(Edge*));

    static bool PathHasFlow(std::vector<Edge*> path);


    void setSuperSinkWithDemand();

    void optimalCityMaxFlow(const std::vector<std::string> &cityList);

    void setSuperSinkNull();
};


#endif //WATERSUPPLYMANAGER_WATERSUPPLY_H
