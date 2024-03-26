#ifndef WATERSUPPLYMANAGER_MENU_H
#define WATERSUPPLYMANAGER_MENU_H

/**
 * \mainpage Welcome to the Water Supply Management Program
 *
 * \section description_sec Project description
 *
 * This program was made for DA course unit of Bachelor in Informatics and Computing Engineering at FEUP.
 * This program is an analysis tool that can support the Management Team of a water supply network in Portugal to make informed decisions about how to best allocate its resources.
 *
 * \section utility_sec What can this project do?
 *

 * Change settings such enabling colour mode.
 */

#include "WaterSupply.h"

/**
 * \class Menu
 * \brief This class handles and runs the different commands.
 *
 * This class has the --- and different functions to analyze and get information from the data.
 * It is also responsible for handling inputs and outputs.
 */
class Menu {
private:
    WaterSupply waterSupply;
public:
    void init();
    /**
     * \brief Outputs the main menu and handles the respective inputs.
     */
    void run();
    /**
     * \brief Reads an option from 1 to n from user input.
     */
    static char readOption(int n);
    /**
     * \brief Asks user for a valid city code.
     *
     * @return The given city code.
     */
    std::string readCityCode();
    /**
     * \brief Asks user for a valid city id.
     *
     * @return The given city id.
     */
    std::string readCityId();
    /**
     * \brief Asks user for a valid city name.
     *
     * @return The given city name.
     */
    std::string readCityName();
    /**
     * \brief Asks user for a valid reservoir code.
     *
     * @return The given reservoir code.
     */
    std::string readReservoirCode();
    /**
     * \brief Asks user for a valid reservoir id.
     *
     * @return The given reservoir id.
     */
    std::string readReservoirID();
    /**
     * \brief Asks user for a valid reservoir name.
     *
     * @return The given reservoir name.
     */
    std::string readReservoirName();
    /**
     * \brief Asks user for a valid reservoir municipality.
     *
     * @return The given reservoir municipality.
     */
    std::vector<Reservoir> readReservoirMunicipality();
    /**
     * \brief Asks user for a valid Station code.
     *
     * @return The given Station code.
     */
    std::string readStationCode();
    /**
     * \brief Asks user for a valid pipe source and destination.
     *
     * @return A pair with the given pipe source and destination.
     */
    std::pair<std::string, std::string> readPipeCodes();
    /**
     * \brief Outputs the information of a city: code, name, demand and population.
     */

    void printCity(City city);
    /**
    * \brief Outputs the information of a city: code, name, municipality and delivery.
    */
    void printReservoir(const Reservoir& reservoir);
    /**
     * \brief Outputs the settings menu and handles the respective inputs.
     */
    void settings();
    /**
     * \brief Outputs the network information menu and handles the respective inputs.
     */
    void getNetworkInfo();
    /**
     * \brief Outputs the options for getting city information and handles the respective inputs.
     */
    void getCityInfo();
    /**
     * \brief Outputs the options for getting reservoir information and handles the respective inputs.
     */
    void getReservoirInfo();
    /**
     * \brief Outputs the options for getting city statistics and handles the respective inputs.
     */
    void getCityStatistics();
    /**
     * \brief Outputs the options for getting reservoir statistics and handles the respective inputs.
     */
    void getReservoirStatistics();
    /**
     * \brief Outputs the max flow options and handles the respective inputs.
     */
    void getMaxFlowOp();
    /**
     * \brief Outputs the reliability testing options and handles the respective inputs.
     */
    void reliabilityTesting(std::vector<std::string>& resStat, std::vector<std::pair<std::string, std::string>>& pipes);
    /**
     * \brief Handles auxiliary options for reliability testing.
     */
    void auxReliability();
    void pressEnterToContinue();
};


#endif //WATERSUPPLYMANAGER_MENU_H
