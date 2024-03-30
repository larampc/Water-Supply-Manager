#ifndef WATERSUPPLYMANAGER_WATERSUPPLY_H
#define WATERSUPPLYMANAGER_WATERSUPPLY_H
#include "City.h"
#include "datastructures/Graph.h"
#include "Reservoir.h"
#include "Station.h"
#include "unordered_map"
#include "MaxFlow.h"

class WaterSupply {
private:
    Graph network;
    std::unordered_map<std::string, City> cities;
    std::unordered_map<std::string, Reservoir> reservoirs;
    std::unordered_map<std::string, Station> stations;
    void loadCities(std::string path);
    void loadReservoir(std::string path);
    void loadStations(std::string path);
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
     *
     */
    void addSuperSource();
    /**
     * \brief Creates a superSink vertex connected to each city by an Edge with capacity equal to the city's demand.
     *
     */
    void addSuperSink();
    /**
     * \brief Creates a superSink vertex connected to each city by an Edge with infinite capacity.
     *
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
     * @return The City with the specified code.
     */
    City getCity(const std::string& code);
    /**
     * \brief Gets the Reservoir with the specified code.
     *
     * @return The Reservoir with the specified code.
     */
    Reservoir getReservoir(const std::string& code);
    /**
     * \brief Gets the cities of the network.
     *
     * @return A mapping of codes to cities.
     */
    std::unordered_map<std::string, City> getCities();
    /**
     * \brief Gets the reservoirs of the network.
     *
     * @return A mapping of codes to reservoirs.
     */
    std::unordered_map<std::string, Reservoir> getReservoirs();
    /**
     * \brief Gets the stations of the network.
     *
     * @return A mapping of codes to stations.
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
     * \brief Gets the cities with the highest demand.
     *
     * @return A vector of cities with the highest demand.
     */
    std::vector<City> getCityMaxDemand();
    /**
     * \brief Gets the cities with the lowest demand.
     *
     * @return A vector of cities with the lowest demand.
     */
    std::vector<City> getCityMinDemand();
    /**
     * \brief Gets the cities with the highest population.
     *
     * @return A vector of cities with the highest population.
     */
    std::vector<City> getCityMaxPop();
    /**
     * \brief Gets the cities with the lowest population.
     *
     * @return A vector of cities with the lowest population.
     */
    std::vector<City> getCityMinPop();
    /**
     * \brief Gets the reservoirs with the highest max delivery.
     *
     * @return A vector of reservoirs with the highest max delivery.
     */
    std::vector<Reservoir> getReservoirMaxDel();
    /**
     * \brief Gets the reservoirs with the lowest max demand.
     *
     * @return A vector of reservoirs with the lowest max demand.
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
     * \brief Computes a given city's incoming flow value.
     *
     * @param city The city whose incoming flow will be computed.
     * @return The city's incoming flow value.
     */
    int computeCityFlow(const std::string& city);
    /********************** MaxFlow  ****************************/
    void maxFlow();
    void maxFlowWithExcess();
    void maxFlowWithExcessToCities(const std::vector<std::string> &target);
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

    std::vector<Edge *> getMaxPathTo(Vertex* city);

    std::vector<Edge *> findMinAugPath(Vertex* city);

    static bool PathHasFlow(std::vector<Edge*> path);


    void setSuperSinkWithDemand();

    void optimalCityMaxFlow(const std::vector<std::string> &cityList);

    void setSuperSinkNull();
};


#endif //WATERSUPPLYMANAGER_WATERSUPPLY_H
