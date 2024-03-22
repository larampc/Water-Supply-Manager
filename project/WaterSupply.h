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
    void loadCities();
    void loadReservoir();
    void loadStations();
    void loadPipes();
    bool dataSet;

public:
    void load();
    /********************** Setters  ****************************/
    void setDataSmall();
    void setDataDefault();
    void setSuperSource();
    void setSuperSink();
    void setInfSuperSink();
    void setSuperWithout(std::string reservoir);
    /********************** Getters  ****************************/
    Graph getNetwork();
    City getCity(std::string code);
    Reservoir getReservoir(std::string code);
    Station getStation(std::string code);
    std::unordered_map<std::string, City> getCities();
    std::unordered_map<std::string, Reservoir> getReservoirs();
    std::unordered_map<std::string, Station> getStations();
    /********************** Checkers  ****************************/
    std::string existsCityByID(int id);
    bool existsCityByCode(std::string code);
    std::string existsCityByName(std::string name);
    std::string existsReservoirByName(std::string name);
    std::string existsReservoirByID(int id);
    bool existsReservoirByCode(std::string code);
    std::vector<Reservoir> existsMunicipality(std::string municipality);
    /********************** Statistics  ****************************/
    std::vector<City> getCityMaxDemand();
    std::vector<City> getCityMinDemand();
    std::vector<City> getCityMaxPop();
    std::vector<City> getCityMinPop();
    std::vector<Reservoir> getReservoirMaxDel();
    std::vector<Reservoir> getReservoirMinDel();
    void computeAverageAndVarianceOfPipes();
    void computeCitiesStatistics();
    int computeMaxFlow();
    int computeCityFlow(std::string city);
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

    bool frblanraciursnacoo();

    void maxFlow();

    void activatePipe(std::string source, std::string dest);

    bool existsStationByCode(std::string code);

    bool existsPipe(std::string source, std::string code);
    bool existsCode(std::string code);

};


#endif //WATERSUPPLYMANAGER_WATERSUPPLY_H
