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
    bool displayOnDemand = true, displayUnderflow = true, displayOverflow = true;
public:
    void swapDisplayOnDemand();
    void swapDisplayUnderflow();
    void swapDisplayOverflow();
    /**
     * \brief Outputs the dataset menu and handles the respective inputs.
     */
    void init();
    /**
     * \brief Outputs the main menu and handles the respective inputs.
     */
    void run();
    /**
     * \brief Reads an option from 1 to the given number from user input.
     *
     * @param n The given number.
     * @return The option from user input.
     */
    static char readOption(int n);
    /**
     * \brief Asks user for a valid City code.
     *
     * @return The given City code.
     */
    std::string readCityCode();
    /**
     * \brief Asks user for a valid City id.
     *
     * @return The given City id.
     */
    std::string readCityId();
    /**
     * \brief Asks user for a valid City name.
     *
     * @return The given City name.
     */
    std::string readCityName();
    /**
     * \brief Asks user for a valid Reservoir code.
     *
     * @return The given Reservoir code.
     */
    std::string readReservoirCode();
    /**
     * \brief Asks user for a valid Reservoir id.
     *
     * @return The given Reservoir id.
     */
    std::string readReservoirID();
    /**
     * \brief Asks user for a valid Reservoir name.
     *
     * @return The given Reservoir name.
     */
    std::string readReservoirName();
    /**
     * \brief Asks user for a valid Reservoir municipality.
     *
     * @return The given Reservoir municipality.
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
     * \brief Outputs the information of the given City: code, name, demand and population.
     *
     * @param city The City to output the information.
     */
    void printCity(City city);
    /**
     * \brief Outputs the information of the given Reservoir: code, name, municipality and delivery.
     *
     * @param reservoir The Reservoir to output the information.
     */
    static void printReservoir(const Reservoir& reservoir);
    /**
     * \brief Outputs the settings menu and handles the respective inputs.
     */
    void settings();
    /**
     * \brief Outputs the network information menu and handles the respective inputs.
     */
    void getNetworkInfo();
    /**
     * \brief Outputs the options for getting City information and handles the respective inputs.
     */
    void getCityInfo();
    /**
     * \brief Outputs the options for getting Reservoir information and handles the respective inputs.
     */
    void getReservoirInfo();
    /**
     * \brief Outputs the options for getting City statistics and handles the respective inputs.
     */
    void getCityStatistics();
    /**
     * \brief Outputs the options for getting Reservoir statistics and handles the respective inputs.
     */
    void getReservoirStatistics();
    /**
     * \brief Outputs the max flow options and handles the respective inputs.
     */
    void getMaxFlowOp();
    /**
     * \brief Outputs the reliability testing options and handles the respective inputs.
     *
     * @param resStat Vector of all deleted Reservoir and Station.
     * @param pipes Vector of all deleted pipes.
     */
    void reliabilityTesting(std::vector<std::string>& resStat, std::vector<std::pair<std::string, std::string>>& pipes);
    /**
     * \brief Handles auxiliary options for reliability testing.
     */
    void auxReliability();
    /**
     * \brief Pauses the output until user presses ENTER.
     */
    void pressEnterToContinue();

    void printPipeDestinations(const std::string& code);

    void getMaxFlowExcessOp();

    void printCitiesStatistics();

    void printNetworkStatistics();

    std::vector<std::string> readCityCodes();

    void changeDisplayMode();
};


#endif //WATERSUPPLYMANAGER_MENU_H
