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
    MaxFlow tester;
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
    void setSuperSource();
    /**
     * \brief Creates a superSink vertex connected to each city by an Edge with capacity equal to the city's demand.
     *
     */
    void setSuperSink();
    /**
     * \brief Creates a superSink vertex connected to each city by an Edge with infinite capacity.
     *
     */
    void setInfSuperSink();
    /**
     * \brief Creates a superSource vertex connected to all reservoirs but the one provided, by an Edge with capacity equal to their max Delivery.
     *
     */
    void setSuperWithout(const std::string& reservoir);
    /********************** Getters  ****************************/
    /**
     * \brief Gets the Graph of the network.
     *
     * @return
     */
    Graph* getNetwork();
    City getCity(const std::string& code);
    Reservoir getReservoir(const std::string& code);
    Station getStation(const std::string& code);
    std::unordered_map<std::string, City> getCities();
    std::unordered_map<std::string, Reservoir> getReservoirs();
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
    std::vector<City> getCityMaxDemand();
    std::vector<City> getCityMinDemand();
    std::vector<City> getCityMaxPop();
    std::vector<City> getCityMinPop();
    std::vector<Reservoir> getReservoirMaxDel();
    std::vector<Reservoir> getReservoirMinDel();
    double computeVarianceDiffCapacityFlow(double average);
    std::vector<std::vector<std::string>> computeCitiesStatistics();
    int computeMaxFlow();
    int computeCityFlow(const std::string& city);
    /********************** MaxFlow  ****************************/
    void optimalResMaxFlow();
    void optimalExcessMaxFlow();
    void optimalExcessCityMaxFlow(std::string target);
    void cityMaxFlow(std::string target);
    /********************** MaxFlow Reverse ****************************/
    void reliabilityPrep();
    void reliabilityTearDown();
    void activate(std::string p);
    void optimalDelete(std::string reservoir);
    void deleteReservoir(std::string reservoir);
    void deleteStation(std::string station);
    void deletePipe(std::string source, std::string dest);


    static void OutputToFile(const std::string &fileName, const std::string &text);

    void deleteReservoirMaxReverse(std::string reservoir);

    void activatePipe(std::string source, std::string dest);

    bool existsStationByCode(const std::string& code);

    bool existsPipe(const std::string& source, const std::string& code);
    bool existsCode(std::string code);
    std::vector<std::string> topsort();

    void activateAll();
    void prepBalance();

    void exportToFile(bool flow);

    void transformBidirectionalEdges();

    void balancingViaMinCost();

    std::vector<Edge *> getMaxPathTo(Vertex* city);

    std::vector<Edge*> findMinAugPath(Vertex* source, Vertex* target);

    std::vector<Edge *> findMinAugPath(Vertex* city);

    static bool PathHasFlow(std::vector<Edge*> path);

    double computeMaxDiffCapacityFlow();

    double computeAverageDiffCapacityFlow();
};


#endif //WATERSUPPLYMANAGER_WATERSUPPLY_H
