#include "Menu.h"
#include <iostream>
#include <sstream>
#include <iomanip>
#include <locale>
#include <codecvt>
#include <fstream>
#include "ColorPrint.h"

using namespace std;

std::string convertDouble(double d) {
    ostringstream os;
    os << std::fixed << std::setprecision(2) << d;
    return os.str();
}

char Menu::readOption(int n){
    string option;
    getline(cin, option);
    while(option.size() > to_string(n).size() || option < "1" || option > to_string(n)){
        if (!option.empty()) ColorPrint("red", "Invalid Input, please try again\n");
        getline(cin, option);
    }
    return option[0];
}

string Menu::readCityCode(){
    string code;
    ColorPrint("cyan", "City code: \n");
    getline(cin, code);
    transform(code.begin(), code.end(), code.begin(), ::toupper);
    while(!waterSupply.existsCityByCode(code)) {
        ColorPrint("red","Invalid city code, please try again\n");
        getline(cin, code);
        transform(code.begin(), code.end(), code.begin(), ::toupper);
    }
    return code;
}

string Menu::readReservoirCode(){
    string code;
    ColorPrint("cyan", "Reservoir code: \n");
    getline(cin, code);
    transform(code.begin(), code.end(), code.begin(), ::toupper);
    while(!waterSupply.existsReservoirByCode(code)) {
        ColorPrint("red","Invalid reservoir code, please try again\n");
        getline(cin, code);
        transform(code.begin(), code.end(), code.begin(), ::toupper);
    }
    return code;
}


string Menu::readCityId(){
    string id;
    ColorPrint("cyan", "City ID: \n");
    getline(cin, id);
    string code = waterSupply.existsCityByID(stoi(id));
    while(code.empty()) {
        ColorPrint("red","Invalid city ID, please try again\n");
        getline(cin, id);
        code = waterSupply.existsCityByID(stoi(id));
    }
    return code;
}

string Menu::readReservoirID(){
    string id;
    ColorPrint("cyan", "Reservoir ID: \n");
    getline(cin, id);
    string code = waterSupply.existsReservoirByID(stoi(id));
    while(code.empty()) {
        ColorPrint("red","Invalid reservoir ID, please try again\n");
        getline(cin, id);
        code = waterSupply.existsReservoirByID(stoi(id));
    }
    return code;
}


string Menu::readCityName(){
    string name;
    ColorPrint("cyan", "City Name: \n");
    getline(cin, name);
    transform(name.begin(), name.end(), name.begin(), ::toupper);
    string code = waterSupply.existsCityByName(name);
    while(code.empty()) {
        ColorPrint("red","Invalid city name, please try again\n");
        getline(cin, name);
        transform(name.begin(), name.end(), name.begin(), ::toupper);
        code = waterSupply.existsCityByName(name);
    }
    return code;
}

string Menu::readReservoirName(){
    string name;
    ColorPrint("cyan", "Reservoir Name: \n");
    getline(cin, name);
    transform(name.begin(), name.end(), name.begin(), ::toupper);
    string code = waterSupply.existsReservoirByName(name);
    while(code.empty()) {
        ColorPrint("red","Invalid reservoir name, please try again\n");
        getline(cin, name);
        transform(name.begin(), name.end(), name.begin(), ::toupper);
        code = waterSupply.existsReservoirByName(name);
    }
    return code;
}
vector<Reservoir> Menu::readReservoirMunicipality(){
    string municipality;
    ColorPrint("cyan", "Municipality: \n");
    getline(cin, municipality);
    transform(municipality.begin(), municipality.end(), municipality.begin(), ::toupper);
    vector<Reservoir> res = waterSupply.existsMunicipality(municipality);
    while(res.empty()) {
        ColorPrint("red","Invalid municipality, please try again\n");
        getline(cin, municipality);
        transform(municipality.begin(), municipality.end(), municipality.begin(), ::toupper);
        res = waterSupply.existsMunicipality(municipality);
    }
    return res;
}


void Menu::run() {
    waterSupply.verification();
    while (true) {
        ColorPrint("blue", "\n-----------------------------------\n");
        ColorPrint("blue", "Water Supply Management System\n");
        ColorPrint("blue", "-----------------------------------\n");
        ColorPrint("blue", "Select option:\n");
        ColorPrint("cyan", "1. ");
        ColorPrint("white", "Network Information \n");
        ColorPrint("cyan", "2. ");
        ColorPrint("white", "Get max flow \n");
        ColorPrint("cyan", "3. ");
        ColorPrint("white", "Settings \n");
        ColorPrint("cyan", "4. ");
        ColorPrint("red", "Quit Manager \n");
        cin.sync();
        switch (readOption(4)) {
            case '1':
                getNetworkInfo();
                break;
            case '2':
                getMaxFlowOp();
                break;
            case '3':
                settings();
                break;
            case '4':
                exit(0);
        }
    }
}

void Menu::settings() {
    string option;
    ColorPrint("blue", "Select option:\n");
    ColorPrint("cyan", "1. ");
    ColorPrint("yellow", ColorPrint::colorMode ? "Disable" : "Enable");
    ColorPrint("white", " Color Mode\n");
    ColorPrint("cyan", "2. ");
    ColorPrint("red", "Cancel\n");
    if (readOption(2) == '1') {
        ColorPrint::swapColorMode();
        ColorPrint("cyan", ColorPrint::colorMode ? "Color mode enabled\n" : "Color mode disabled\n");
    }
}

void Menu::getNetworkInfo() {
    ColorPrint("blue", "Select option:\n");
    ColorPrint("cyan", "1. ");
    ColorPrint("white", "Get City info \n");
    ColorPrint("cyan", "2. ");
    ColorPrint("white", "Get Reservoir info \n");
    ColorPrint("cyan", "3. ");
    ColorPrint("white", "Get Stations \n");
    ColorPrint("cyan", "4. ");
    ColorPrint("red", "Cancel \n");
    cin.sync();
    switch (readOption(4)) {
        case '1':
            getCityInfo();
            break;
        case '2':
            getReservoirInfo();
            break;
        case '3':
            ColorPrint("blue", "Code\n");
            for (const auto& s: waterSupply.getStations()) {
                ColorPrint("white", s.first + "\n");
            }
    }
}

void Menu::getCityInfo() {
    ColorPrint("blue", "Select option:\n");
    ColorPrint("cyan", "1. ");
    ColorPrint("white", "Search by code\n");
    ColorPrint("cyan", "2. ");
    ColorPrint("white", "Search by name\n");
    ColorPrint("cyan", "3. ");
    ColorPrint("white", "Search by ID\n");
    ColorPrint("cyan", "4. ");
    ColorPrint("white", "List all cities \n");
    ColorPrint("cyan", "5. ");
    ColorPrint("white", "Statistics \n");
    ColorPrint("cyan", "6. ");
    ColorPrint("red", "Cancel \n");
    cin.sync();
    string code;
    switch (readOption(6)) {
        case '1':
            code = readCityCode();
            ColorPrint("blue", "Code | City | Demand | Population\n");
            printCity(waterSupply.getCity(code));
            break;
        case '2':
            code = readCityName();
            ColorPrint("blue", "Code | City | Demand | Population\n");
            printCity(waterSupply.getCity(code));
            break;
        case '3':
            code = readCityId();
            ColorPrint("blue", "Code | City | Demand | Population\n");
            printCity(waterSupply.getCity(code));
            break;
        case '4':
            ColorPrint("blue", "Code | City | Demand | Population\n");
            for (const auto& c: waterSupply.getCities()) {
                printCity(c.second);
            }
            break;
        case '5':
            getCityStatistics();
            break;
    }
}

void Menu::printCity(City city) {
    ColorPrint("white", city.getCode() + " | " + city.getName() + " | " + to_string(city.getDemand()) + " | " + to_string(city.getPopulation()) + "\n");
}

void Menu::getReservoirInfo() {
    ColorPrint("blue", "Select option:\n");
    ColorPrint("cyan", "1. ");
    ColorPrint("white", "Search by code\n");
    ColorPrint("cyan", "2. ");
    ColorPrint("white", "Search by name\n");
    ColorPrint("cyan", "3. ");
    ColorPrint("white", "Search by ID\n");
    ColorPrint("cyan", "4. ");
    ColorPrint("white", "Search by Municipality\n");
    ColorPrint("cyan", "5. ");
    ColorPrint("white", "List all reservoirs \n");
    ColorPrint("cyan", "6. ");
    ColorPrint("white", "Statistics \n");
    ColorPrint("cyan", "7. ");
    ColorPrint("red", "Cancel \n");
    cin.sync();
    string code;
    vector<Reservoir> mun;
    switch (readOption(7)) {
        case '1':
            code = readReservoirCode();
            ColorPrint("blue", "Code | Reservoir | Municipality | Max Delivery \n");
            printReservoir(waterSupply.getReservoir(code));
            break;
        case '2':
            code = readReservoirName();
            ColorPrint("blue", "Code | Reservoir | Municipality | Max Delivery \n");
            printReservoir(waterSupply.getReservoir(code));
            break;
        case '3':
            code = readReservoirID();
            ColorPrint("blue", "Code | Reservoir | Municipality | Max Delivery \n");
            printReservoir(waterSupply.getReservoir(code));
            break;
        case '4':
            mun = readReservoirMunicipality();
            ColorPrint("blue", "Code | Reservoir | Municipality | Max Delivery \n");
            for (const auto& r: mun) {
                printReservoir(r);
            }
            break;
        case '5':
            ColorPrint("blue", "Code | Reservoir | Municipality | Max Delivery \n");
            for (const auto& r: waterSupply.getReservoirs()) {
                printReservoir(r.second);
            }
            break;
        case '6':
            getReservoirStatistics();
            break;
    }
}

void Menu::printReservoir(const Reservoir& reservoir) {
    ColorPrint("white", reservoir.getCode() + " |  " + reservoir.getName() + " | " + reservoir.getMunicipality() + " | " + to_string(reservoir.getDelivery()) + "\n");
}

void Menu::getCityStatistics() {
    ColorPrint("blue", "Select option:\n");
    ColorPrint("cyan", "1. ");
    ColorPrint("white", "Max demand\n");
    ColorPrint("cyan", "2. ");
    ColorPrint("white", "Min demand\n");
    ColorPrint("cyan", "3. ");
    ColorPrint("white", "Max population\n");
    ColorPrint("cyan", "4. ");
    ColorPrint("white", "Min population\n");
    ColorPrint("cyan", "5. ");
    ColorPrint("red", "Cancel \n");
    cin.sync();
    vector<City> values;
    switch (readOption(5)) {
        case '1':
            values = waterSupply.getCityMaxDemand();
            for (const auto& v: values) {
                printCity(v);
            }
            break;
        case '2':
            values = waterSupply.getCityMinDemand();
            for (const auto& v: values) {
                printCity(v);
            }
            break;
        case '3':
            values = waterSupply.getCityMaxPop();
            for (const auto& v: values) {
                printCity(v);
            }
            break;
        case '4':
            values = waterSupply.getCityMinPop();
            for (const auto& v: values) {
                printCity(v);
            }
            break;
    }
}

void Menu::getReservoirStatistics() {
    ColorPrint("blue", "Select option:\n");
    ColorPrint("cyan", "1. ");
    ColorPrint("white", "Biggest max delivery\n");
    ColorPrint("cyan", "2. ");
    ColorPrint("white", "Lowest max delivery\n");
    ColorPrint("cyan", "3. ");
    ColorPrint("red", "Cancel \n");
    cin.sync();
    vector<Reservoir> values;
    switch (readOption(3)) {
        case '1':
            values = waterSupply.getReservoirMaxDel();
            for (auto r: values) {
                printReservoir(r);
            }
            break;
        case '2':
            values = waterSupply.getReservoirMinDel();
            for (auto r: values) {
                printReservoir(r);
            }
            break;
    }
}

void Menu::init() {
    ColorPrint("blue", "Which data set do you wish to use?\n");
    ColorPrint("cyan", "1. ");
    ColorPrint("white", "Continental Portugal\n");
    ColorPrint("cyan", "2. ");
    ColorPrint("white", "Madeira\n");
    cin.sync();
    switch (readOption(2)) {
        case '1':
            waterSupply.setDataDefault();
            break;
        case '2':
            waterSupply.setDataSmall();
            break;
    }
    waterSupply.load();
}

void Menu::getMaxFlowOp() {
    ColorPrint("blue", "Select option:\n");
    ColorPrint("cyan", "1. ");
    ColorPrint("white", "Get optimal max flow\n");
    ColorPrint("cyan", "2. ");
    ColorPrint("white", "Get optimal max flow with excess\n");
    ColorPrint("cyan", "3. ");
    ColorPrint("white", "Get max flow to specific city\n");
    ColorPrint("cyan", "4. ");
    ColorPrint("white", "Get max flow to each city\n");
    ColorPrint("cyan", "5. ");
    ColorPrint("white", "Get optimal max flow with excess to a specific city\n");
    ColorPrint("cyan", "6. ");
    ColorPrint("red", "Cancel \n");
    cin.sync();
    string code;
    ostringstream oss;
    switch (readOption(5)) {
        case '1':
            waterSupply.optimalResMaxFlow();
            waterSupply.computeCitiesStatistics();
            ColorPrint("cyan", "Total: ");
            ColorPrint("white", to_string(waterSupply.computeMaxFlow()));
            break;
        case '2':
            waterSupply.optimalExcessMaxFlow();
            waterSupply.computeCitiesStatistics();
            ColorPrint("cyan", "Total: ");
            ColorPrint("white", to_string(waterSupply.computeMaxFlow()));
            break;
        case '3':
            code = readCityCode();
            waterSupply.cityMaxFlow(code);
            ColorPrint("cyan", "Total: ");
            ColorPrint("white", to_string(waterSupply.getCityFlow(code)));
            break;
        case '4':
            oss << "City - Flow\n";
            for(const auto& c : waterSupply.getCities()){
                waterSupply.cityMaxFlow(c.first);
                oss << left << setw(4) << c.first << " - " + to_string(waterSupply.getCityFlow(c.first)) + "\n";
            }
            waterSupply.OutputToFile("../output/CitiesMaxFlow", oss.str());
            cout << oss.str();
            break;
        case '5':
            code = readCityCode();
            waterSupply.optimalExcessCityMaxFlow(code);
            waterSupply.computeCitiesStatistics();
            ColorPrint("cyan", "Total to " + waterSupply.getCity(code).getName() + ": ");
            ColorPrint("white", to_string(waterSupply.getCityFlow(code)) + "\n");
            ColorPrint("cyan", "Total: ");
            ColorPrint("white", to_string(waterSupply.computeMaxFlow()));
            break;
    }
}


