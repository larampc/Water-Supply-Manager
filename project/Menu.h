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
    /**
     * \brief Outputs the main menu and handles the respective inputs.
     */
    void run();
    /**
     * \brief Reads an option from 1 to n from user input.
     */
    static char readOption(int n);
    /**
     * \brief Outputs the settings menu and handles the respective inputs.
     */
    std::string readCityCode();
    std::string readCityId();
    std::string readCityName();
    std::string readReservoirCode();
    std::string readReservoirID();
    std::string readReservoirName();
    std::vector<Reservoir> readReservoirMunicipality();
    void printCity(City city);

    void settings();
    void getNetworkInfo();
    void getCityInfo();
    void getReservoirInfo();
    void printReservoir(const Reservoir& reservoir);
    void getCityStatistics();
    void getReservoirStatistics();
};


#endif //WATERSUPPLYMANAGER_MENU_H
