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
 * Choose to import from the original dataset (big or small) or a custom dataset from file paths.

 * Get information such as:
 * - List of all City in the dataset and there respective information;
 * - Get the information of a specific City from a given code or name or ID;
 * - Get the information of the City that has max or min demand;
 * - Get the information of the City that has max or min population;
 * - List of all Reservoir in the dataset and there respective information;
 * - Get the information of a specific Reservoir from a given code or name or ID or Municipality;
 * - Get the information of the Reservoir that has max or min delivery;
 * - List of all Station in the dataset and there respective information;
 * - Get the statistics of the network such as Average (Capacity - Flow), Max (Capacity - Flow), Variance (Capacity - Flow), current flow to all City and current max flow.

 * Make requests such as:
 * - Compute the standard max flow of the network;
 * - Compute the max flow of the network but prioritizing specific City given by the user or in order of population;
 * - Compute the max flow of the network with overflow;
 * - Compute the max flow of the network with overflow that is able to reach a specific City;
 * - Compute the max flow of the network with overflow for only a given list of City;
 * - Erase specific Reservoir, Station or pipes from the Graph;
 * - Balance the flow of the network in order to reduce the Variance (Capacity - Flow).

 * Change settings such as:
 * - Enabling colour mode;
 * - Changing the display mode of the network statistics.
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
    MaxFlow maxFlow;
    bool displayOnDemand = true, displayUnderflow = true, displayOverflow = true, displayDemand = true;
public:
    void swapDisplayOnDemand();
    void swapDisplayUnderflow();
    void swapDisplayOverflow();
    void swapDisplayDemand();
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
    static void printCity(const City& city);
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
    static void pressEnterToContinue();

    void printPipeDestinations(const std::string& code);

    void getMaxFlowExcessOp();

    void printCitiesFlow(std::vector<double> citiesPrevFlow = {});

    void printNetworkStatistics();

    std::vector<std::string> readCitiesCodes();

    void MaxFlowWithPrioritizedCities();

    void changeDisplayMode();

    void reliabiltyMenu();

    void checkDeactivatedComponents();

    void checkDeactivatedReservoirs();
    void checkDeactivatedStations();
    void checkDeactivatedPipes();


};


#endif //WATERSUPPLYMANAGER_MENU_H
