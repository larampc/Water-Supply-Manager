#include "Menu.h"
#include <iostream>
#include <sstream>
#include <iomanip>
#include <map>
#include "ColorPrint.h"

using namespace std;

std::string convertDouble(double d, int precision = 2) {
    ostringstream os;
    os << std::fixed << std::setprecision(precision) << d;
    return os.str();
}

void Menu::changeDisplayMode() {
    string option;
    ColorPrint("blue", "Select option:\n");
    ColorPrint("cyan", "1. ");
    ColorPrint("yellow", displayOnDemand ? "Hide" : "Show");
    ColorPrint("white", " on demand\n");
    ColorPrint("cyan", "2. ");
    ColorPrint("yellow", displayOverflow ? "Hide" : "Show");
    ColorPrint("white", " overflow\n");
    ColorPrint("cyan", "3. ");
    ColorPrint("yellow", displayUnderflow ? "Hide" : "Show");
    ColorPrint("white", " underflow\n");
    ColorPrint("cyan", "4. ");
    ColorPrint("yellow", displayDemand ? "Hide" : "Show");
    ColorPrint("white", " demand of cities\n");
    ColorPrint("cyan", "5. ");
    ColorPrint("red", "Cancel\n");
    cin.sync();
    switch (readOption(5)) {
        case '1':
            swapDisplayOnDemand();
            ColorPrint("cyan", displayOnDemand ? "Displaying on demand\n" : "Hiding on demand\n");
            pressEnterToContinue();
            break;
        case '2':
            swapDisplayOverflow();
            ColorPrint("cyan", displayOverflow ? "Displaying overflow\n" : "Hiding overflow\n");
            pressEnterToContinue();
            break;
        case '3':
            swapDisplayUnderflow();
            ColorPrint("cyan", displayUnderflow ? "Displaying underflow\n" : "Hiding underflow\n");
            pressEnterToContinue();
            break;
        case '4':
            swapDisplayDemand();
            ColorPrint("cyan", displayDemand ? "Displaying demand of cities\n" : "Hiding demand of cities\n");
            pressEnterToContinue();
            break;
        case '5':
            settings();
            break;
    }
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
    ColorPrint("cyan", "City code (");
    ColorPrint("yellow", "empty to Cancel");
    ColorPrint("cyan", "): \n");
    getline(cin, code);
    if (code.empty()) return code;
    transform(code.begin(), code.end(), code.begin(), ::toupper);
    while(!waterSupply.existsCityByCode(code)) {
        ColorPrint("red","Invalid city code, please try again\n");
        getline(cin, code);
        if (code.empty()) break;
        transform(code.begin(), code.end(), code.begin(), ::toupper);
    }
    return code;
}

vector<string> Menu::readCitiesCodes(){
    vector<string> codes;
    ColorPrint("cyan", "City codes (");
    ColorPrint("yellow", "empty to finish");
    ColorPrint("cyan", "): \n");
    while (true) {
        string code;
        getline(cin, code);
        if (code.empty()) return codes;
        transform(code.begin(), code.end(), code.begin(), ::toupper);
        while(!waterSupply.existsCityByCode(code)) {
            ColorPrint("red","Invalid city code, please try again\n");
            getline(cin, code);
            if (code.empty()) break;
            transform(code.begin(), code.end(), code.begin(), ::toupper);
        }
        if (code.empty()) break;
        codes.push_back(code);
    }
    return codes;
}

void Menu::printPipeDestinations(const string& code){
    auto pipe = waterSupply.getNetwork()->findVertex(code);
    for(auto dest : pipe->getAdj()){
        if (dest->getDest()->getInfo() != "sink") {
            ColorPrint("yellow", " " + dest->getDest()->getInfo());
            if(dest != *(pipe->getAdj().end()-1)) ColorPrint("blue",",");
        }
    }
}

pair<string, string> Menu::readPipeCodes(){
    string code, code2;
    do {
        ColorPrint("cyan", "Pipe source code (");
        ColorPrint("yellow", "empty to Cancel");
        ColorPrint("cyan", "): \n");
        getline(cin, code);
        if (code.empty()) return make_pair(code, code2);
        transform(code.begin(), code.end(), code.begin(), ::toupper);
        while(!waterSupply.existsCode(code)) {
            ColorPrint("red","Invalid code, please try again\n");
            getline(cin, code);
            if (code.empty()) return make_pair(code, code2);
            transform(code.begin(), code.end(), code.begin(), ::toupper);
        }
        ColorPrint("cyan", "Pipe destination code (");
        ColorPrint("yellow", "empty to Cancel");
        ColorPrint("cyan", "): \n");
        ColorPrint("blue","[");
        printPipeDestinations(code);
        ColorPrint("blue"," ]\n");
        getline(cin, code2);
        if (code2.empty()) return make_pair(code, code2);
        transform(code2.begin(), code2.end(), code2.begin(), ::toupper);
        while(!waterSupply.existsCode(code2)) {
            ColorPrint("red","Invalid code, please try again\n");
            getline(cin, code2);
            if (code2.empty()) return make_pair(code, code2);
            transform(code2.begin(), code2.end(), code2.begin(), ::toupper);
        }
        if (!waterSupply.existsPipe(code, code2)) ColorPrint("red","Invalid pipe, please try again\n");
    }
    while (!waterSupply.existsPipe(code, code2));
    return make_pair(code, code2);
}

string Menu::readStationCode(){
    string code;
    ColorPrint("cyan", "Station code (");
    ColorPrint("yellow", "empty to Cancel");
    ColorPrint("cyan", "): \n");
    getline(cin, code);
    if (code.empty()) return code;
    transform(code.begin(), code.end(), code.begin(), ::toupper);
    while(!waterSupply.existsStationByCode(code)) {
        ColorPrint("red","Invalid station code, please try again\n");
        getline(cin, code);
        if (code.empty()) return code;
        transform(code.begin(), code.end(), code.begin(), ::toupper);
    }
    return code;
}

string Menu::readReservoirCode(){
    string code;
    ColorPrint("cyan", "Reservoir code (");
    ColorPrint("yellow", "empty to Cancel");
    ColorPrint("cyan", "): \n");
    getline(cin, code);
    if (code.empty()) return code;
    transform(code.begin(), code.end(), code.begin(), ::toupper);
    while(!waterSupply.existsReservoirByCode(code)) {
        ColorPrint("red","Invalid reservoir code, please try again\n");
        getline(cin, code);
        if (code.empty()) return code;
        transform(code.begin(), code.end(), code.begin(), ::toupper);
    }
    return code;
}


string Menu::readCityId(){
    string id;
    ColorPrint("cyan", "City ID (");
    ColorPrint("yellow", "empty to Cancel");
    ColorPrint("cyan", "): \n");
    getline(cin, id);
    if (id.empty()) return id;
    string code;
    while( (std::any_of(id.begin(), id.end(), [](char c) {return !isdigit(c);})) || id.empty() || (code = waterSupply.existsCityByID(stoi(id))).empty()) {
        ColorPrint("red","Invalid city ID, please try again\n");
        getline(cin, id);
        if (id.empty()) return id;
    }
    return code;
}

string Menu::readReservoirID(){
    string id;
    ColorPrint("cyan", "Reservoir ID (");
    ColorPrint("yellow", "empty to Cancel");
    ColorPrint("cyan", "): \n");
    getline(cin, id);
    if (id.empty()) return id;
    string code;
    while( (std::any_of(id.begin(), id.end(), [](char c) {return !isdigit(c);})) || id.empty() || (code = waterSupply.existsReservoirByID(stoi(id))).empty()) {
        ColorPrint("red","Invalid reservoir ID, please try again\n");
        getline(cin, id);
        if (id.empty()) return id;
    }
    return code;
}


string Menu::readCityName(){
    string name;
    ColorPrint("cyan", "City Name (");
    ColorPrint("yellow", "empty to Cancel");
    ColorPrint("cyan", "): \n");
    getline(cin, name);
    if (name.empty()) return name;
    transform(name.begin(), name.end(), name.begin(), ::toupper);
    string code = waterSupply.existsCityByName(name);
    while(code.empty()) {
        ColorPrint("red","Invalid city name, please try again\n");
        getline(cin, name);
        if (name.empty()) return name;
        transform(name.begin(), name.end(), name.begin(), ::toupper);
        code = waterSupply.existsCityByName(name);
    }
    return code;
}

string Menu::readReservoirName(){
    string name;
    ColorPrint("cyan", "Reservoir Name (");
    ColorPrint("yellow", "empty to Cancel");
    ColorPrint("cyan", "): \n");
    getline(cin, name);
    if (name.empty()) return name;
    transform(name.begin(), name.end(), name.begin(), ::toupper);
    string code = waterSupply.existsReservoirByName(name);
    while(code.empty()) {
        ColorPrint("red","Invalid reservoir name, please try again\n");
        getline(cin, name);
        if (name.empty()) return name;
        transform(name.begin(), name.end(), name.begin(), ::toupper);
        code = waterSupply.existsReservoirByName(name);
    }
    return code;
}
vector<Reservoir> Menu::readReservoirMunicipality(){
    string municipality;
    ColorPrint("cyan", "Municipality (");
    ColorPrint("yellow", "empty to Cancel");
    ColorPrint("cyan", "): \n");
    getline(cin, municipality);
    if (municipality.empty()) return {};
    transform(municipality.begin(), municipality.end(), municipality.begin(), ::toupper);
    vector<Reservoir> res = waterSupply.existsMunicipality(municipality);
    while(res.empty()) {
        ColorPrint("red","Invalid municipality, please try again\n");
        getline(cin, municipality);
        if (municipality.empty()) return {};
        transform(municipality.begin(), municipality.end(), municipality.begin(), ::toupper);
        res = waterSupply.existsMunicipality(municipality);
    }
    return res;
}


void Menu::run() {
    while (true) {
        ColorPrint("blue", "\n-----------------------------------\n");
        ColorPrint("blue", "Water Supply Management System\n");
        ColorPrint("blue", "-----------------------------------\n");
        ColorPrint("blue", "Select option:\n");
        ColorPrint("cyan", "1. ");
        ColorPrint("white", "Network Information \n");
        ColorPrint("cyan", "2. ");
        ColorPrint("white", "Max flow options\n");
        ColorPrint("cyan", "3. ");
        ColorPrint("white", "Network reliability\n");
        ColorPrint("cyan", "4. ");
        ColorPrint("white", "Balance Network load\n");
        ColorPrint("cyan", "5. ");
        ColorPrint("white", "Settings \n");
        ColorPrint("cyan", "6. ");
        ColorPrint("red", "Quit Manager \n");
        cin.sync();
        switch (readOption(6)) {
            case '1':
                getNetworkInfo();
                break;
            case '2':
                getMaxFlowOp();
                break;
            case '3':
                reliabilityMenu();
                break;
            case '4':
                waterSupply.balancingViaMinCost();
                printNetworkStatistics();
                pressEnterToContinue();
                break;
            case '5':
                settings();
                break;
            case '6':
                ColorPrint("blue", "Bye Bye :(\n");
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
    ColorPrint("white", "Change display mode\n");
    ColorPrint("cyan", "3. ");
    ColorPrint("red", "Cancel\n");
    switch (readOption(3)) {
        case '1':
            ColorPrint::swapColorMode();
            ColorPrint("cyan", ColorPrint::colorMode ? "Color mode enabled\n" : "Color mode disabled\n");
            break;
        case '2':
            changeDisplayMode();
            break;
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
    ColorPrint("white", "Get Network statistics \n");
    ColorPrint("cyan", "5. ");
    ColorPrint("red", "Cancel \n");
    cin.sync();
    switch (readOption(5)) {
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
            pressEnterToContinue();
            break;
        case '4':
            printNetworkStatistics();
            pressEnterToContinue();
            break;
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
            break;
        case '2':
            code = readCityName();
            break;
        case '3':
            code = readCityId();
            break;
        case '4':
            ColorPrint("blue", "Code | City | Demand | Population\n");
            for(int i = 1; i <= waterSupply.getCities().size(); i++) {
                printCity(waterSupply.getCity("C_" + to_string(i)));
            }
            pressEnterToContinue();
            return;
        case '5':
            getCityStatistics();
            return;
        case '6':
            getNetworkInfo();
            return;
    }
    if (!code.empty()) {
        ColorPrint("blue", "Code | City | Demand | Population\n");
        printCity(waterSupply.getCity(code));
        pressEnterToContinue();
    } else getCityInfo();
}

void Menu::printCity(const City& city) {
    ostringstream oss;
    oss << setw(4) << left << city.getCode()
    << " | " << city.getName() + " | "
    << city.getDemand() << " | " << city.getPopulation() << "\n";
    ColorPrint("white", oss.str());
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
    switch (readOption(7)) {
        case '1':
            code = readReservoirCode();
            break;
        case '2':
            code = readReservoirName();
            break;
        case '3':
            code = readReservoirID();
            break;
        case '4':
        {
            vector<Reservoir> mun;
            mun = readReservoirMunicipality();
            std::sort(mun.begin(), mun.end());
            if (!mun.empty()) {
                ColorPrint("blue", "Code | Reservoir | Municipality | Max Delivery \n");
                for (const auto &r: mun) {
                    printReservoir(r);
                }
                pressEnterToContinue();
            } else getReservoirInfo();
        }
            return;
        case '5':
            ColorPrint("blue", "Code | Reservoir | Municipality | Max Delivery \n");
            for (int i = 1; i <= waterSupply.getReservoirs().size(); i++) {
                printReservoir(waterSupply.getReservoir("R_" + to_string(i)));
            }
            pressEnterToContinue();
            return;
        case '6':
            getReservoirStatistics();
            return;
        case '7':
            getNetworkInfo();
            return;
    }
    if (!code.empty()) {
        ColorPrint("blue", "Code | Reservoir | Municipality | Max Delivery \n");
        printReservoir(waterSupply.getReservoir(code));
        pressEnterToContinue();
    } else getReservoirInfo();
}

void Menu::printReservoir(const Reservoir& reservoir) {
    ostringstream oss;
    oss << setw(4) << left << reservoir.getCode()
        << " | " << reservoir.getName() + " | "
        << reservoir.getMunicipality() << " | " << to_string(reservoir.getDelivery()) << "\n";
    ColorPrint("white", oss.str());
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
            break;
        case '2':
            values = waterSupply.getCityMinDemand();
            break;
        case '3':
            values = waterSupply.getCityMaxPop();
            break;
        case '4':
            values = waterSupply.getCityMinPop();
            break;
        case '5':
            getCityInfo();
            return;
    }
    std::sort(values.begin(), values.end());
    ColorPrint("blue", "Code | City | Demand | Population\n");
    for (const auto& v: values) {
        printCity(v);
    }
    pressEnterToContinue();
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
            break;
        case '2':
            values = waterSupply.getReservoirMinDel();
            break;
        case '3':
            getReservoirInfo();
            return;
    }
    std::sort(values.begin(), values.end());
    ColorPrint("blue", "Code | Reservoir | Municipality | Max Delivery \n");
    for (const auto& r: values) {
        printReservoir(r);
    }
    pressEnterToContinue();
}

void Menu::init() {
    ColorPrint("blue", "Which data set do you wish to use?\n");
    ColorPrint("cyan", "1. ");
    ColorPrint("white", "Continental Portugal\n");
    ColorPrint("cyan", "2. ");
    ColorPrint("white", "Madeira\n");
    ColorPrint("cyan", "3. ");
    ColorPrint("white", "Other\n");
    cin.sync();
    switch (readOption(3)) {
        case '1':
            waterSupply.load("dataSet/Cities.csv", "dataSet/Reservoir.csv", "dataSet/Pipes.csv", "dataSet/Stations.csv");
            break;
        case '2':
            waterSupply.load("dataSetSmall/Cities_Madeira.csv", "dataSetSmall/Reservoirs_Madeira.csv", "dataSetSmall/Pipes_Madeira.csv", "dataSetSmall/Stations_Madeira.csv");
            break;
        case '3':
            ColorPrint("cyan", "Cities file path: \n");
            ColorPrint("white", "Format - City,Id,Code,Demand,Population\n");
            string cities, pipes, reservoirs, stations;
            getline(cin, cities);
            ColorPrint("cyan", "Pipes file path: \n");
            ColorPrint("white", "Format - Service_Point_A,Service_Point_B,Capacity,Direction\n");
            getline(cin, pipes);
            ColorPrint("cyan", "Reservoirs file path: \n");
            ColorPrint("white", "Format - Reservoir,Municipality,Id,Code,Maximum Delivery (m3/sec)\n");
            getline(cin, reservoirs);
            ColorPrint("cyan", "Stations file path: \n");
            ColorPrint("white", "Format - Id,Code\n");
            getline(cin, stations);
            waterSupply.load(cities, reservoirs, pipes, stations);
    }
}

void Menu::getMaxFlowOp() {
    ColorPrint("blue", "Select option:\n");
    ColorPrint("cyan", "1. ");
    ColorPrint("white", "Get max flow\n");
    ColorPrint("cyan", "2. ");
    ColorPrint("white", "Get max flow prioritizing specific cities\n");
    ColorPrint("cyan", "3. ");
    ColorPrint("white", "Max flow with excess options\n");
    ColorPrint("cyan", "4. ");
    ColorPrint("white", "Balanced Max flow\n");
    ColorPrint("cyan", "5. ");
    ColorPrint("red", "Cancel \n");
    cin.sync();
    switch (readOption(5)) {
        case '1':
            waterSupply.maxFlow();
            printCitiesFlow();
            pressEnterToContinue();
            break;
        case '2':
            MaxFlowWithPrioritizedCities();
            break;
        case '3':
            getMaxFlowExcessOp();
            break;
        case '4':
            MaxFlow::balancedMaxFlow(waterSupply.getNetwork(), "src", "sink");
            printNetworkStatistics();
            pressEnterToContinue();
            break;
    }
}

void Menu::MaxFlowWithPrioritizedCities(){
    ColorPrint("blue", "Select option:\n");
    ColorPrint("cyan", "1. ");
    ColorPrint("white", "Custom city priority list\n");
    ColorPrint("cyan", "2. ");
    ColorPrint("white", "Population-based priority\n");
    ColorPrint("cyan", "3. ");
    ColorPrint("red", "Cancel \n");
    cin.sync();
    switch (readOption(3)) {
        case '1':
        {
            vector<string> cities = readCitiesCodes();
            if (!cities.empty()) {
                waterSupply.optimalCityMaxFlow(cities);
                printCitiesFlow();
                pressEnterToContinue();
            } else MaxFlowWithPrioritizedCities();
        }
        break;
        case '2':
        {
            vector<string> citiesByPopulation;
            auto cities = waterSupply.getCities();
            citiesByPopulation.reserve(cities.size());
            for(const auto& c : cities) citiesByPopulation.push_back(c.first);

            ColorPrint("blue", "Select option:\n");
            ColorPrint("cyan", "1. ");
            ColorPrint("white", "Ascending order (Benefits those with lowest population)\n");
            ColorPrint("cyan", "2. ");
            ColorPrint("white", "Descending order\n");
            ColorPrint("cyan", "3. ");
            ColorPrint("red", "Cancel\n");
            char option = readOption(3);
            if (option != '3') {
                bool ascending = option == '1';
                ascending ? std::sort(citiesByPopulation.begin(), citiesByPopulation.end(),
                                      [cities](const string &s1, const string &s2) {
                                          return cities.at(s1).getPopulation() < cities.at(s2).getPopulation();
                                      })
                          : std::sort(citiesByPopulation.rbegin(), citiesByPopulation.rend(),
                                      [cities](const string &s1, const string &s2) {
                                          return cities.at(s1).getPopulation() < cities.at(s2).getPopulation();
                                      });

                waterSupply.optimalCityMaxFlow(citiesByPopulation);
                printCitiesFlow();
                pressEnterToContinue();
            } else MaxFlowWithPrioritizedCities();
        }
            break;
        case '3':
            getMaxFlowOp();
            break;
    }
}

void Menu::getMaxFlowExcessOp() {
    ColorPrint("blue", "Select option:\n");
    ColorPrint("cyan", "1. ");
    ColorPrint("white", "Get max flow\n");
    ColorPrint("cyan", "2. ");
    ColorPrint("white", "Get max possible flow to specific city\n");
    ColorPrint("cyan", "3. ");
    ColorPrint("white", "Get max flow with possible overflowing to specific cities\n");
    ColorPrint("cyan", "4. ");
    ColorPrint("red", "Cancel \n");
    cin.sync();
    string code;
    ostringstream oss;
    switch (readOption(4)) {
        case '1':
            waterSupply.maxFlowWithExcess();
            printCitiesFlow();
            pressEnterToContinue();
            break;
        case '2':
            code = readCityCode();
            if (!code.empty()) {
                waterSupply.maxFlowToCity(code);
                ColorPrint("cyan", "Total: ");
                ColorPrint("white", to_string(waterSupply.computeCityFlow(code)));
                pressEnterToContinue();
            } else getMaxFlowExcessOp();
            break;
        case '3': {
            vector<string> codes = readCitiesCodes();
            if (!codes.empty()) {
                waterSupply.maxFlowWithExcessToCities(codes);
                printCitiesFlow();
                pressEnterToContinue();
            } else getMaxFlowExcessOp();
        }
            break;
        case '4':
            getMaxFlowOp();
            break;
    }
}

void Menu::checkDeactivatedReservoirs(){
    ColorPrint("blue", "Deactivated Reservoirs:\n");
    bool empty = true;
    for(int i = 1; i <= waterSupply.getReservoirs().size(); i++) {
        auto code = "R_" + to_string(i);
        if(!waterSupply.getNetwork()->findVertex(code)->checkActive()){
            ColorPrint("white", code + "\n");
            empty = false;
        }
    }
    if(empty){
        ColorPrint("blue", "There are no deactivated reservoirs\n");
        pressEnterToContinue();
        checkDeactivatedComponents();
        return;
    }
    ColorPrint("blue", "Specify the reservoir you wish to activate \n");
    string code = readReservoirCode();
    if (!code.empty()) {
        waterSupply.getNetwork()->findVertex(code)->activate();
        checkDeactivatedReservoirs();
    }
    else checkDeactivatedComponents();
}

void Menu::checkDeactivatedStations(){
    ColorPrint("blue", "Deactivated Stations:\n");
    bool empty = true;
    for(int i = 1; i <= waterSupply.getStations().size(); i++) {
        auto code = "PS_" + to_string(i);
        if(!waterSupply.getNetwork()->findVertex(code)->checkActive()){
            ColorPrint("white", code + "\n");
            empty = false;
        }
    }
    if(empty){
        ColorPrint("blue", "There are no deactivated stations\n");
        pressEnterToContinue();
        checkDeactivatedComponents();
        return;
    }
    ColorPrint("blue", "Specify the station you wish to activate \n");
    string code = readStationCode();
    if (!code.empty()) {
        waterSupply.getNetwork()->findVertex(code)->activate();
        checkDeactivatedStations();
    }
    else checkDeactivatedComponents();
}


void Menu::checkDeactivatedPipes(){
    ColorPrint("blue", "Deactivated Pipes:\n");
    vector<pair<string,string>> pipes;
    for(const auto& v : waterSupply.getNetwork()->getVertexSet()){
        for(auto adj : v.second->getAdj()){
            if(!adj->checkActive()) pipes.emplace_back(adj->getOrig()->getInfo(), adj->getDest()->getInfo());
        }
    }
    std::sort(pipes.begin(), pipes.end());
    for(const auto& pipe : pipes){
        ColorPrint("white", pipe.first + " -> " + pipe.second + "\n");
    }
    if(pipes.empty()){
        ColorPrint("blue", "There are no deactivated pipes\n");
        pressEnterToContinue();
        checkDeactivatedComponents();
        return;
    }
    ColorPrint("blue", "Specify the pipe you wish to activate \n");
    pair<string,string> code = readPipeCodes();
    if (!code.first.empty()) {
        waterSupply.getNetwork()->findEdge(code.first, code.second)->activate();
        checkDeactivatedPipes();
    }
    else checkDeactivatedComponents();
}

void Menu::checkDeactivatedComponents(){
    ColorPrint("blue", "Select option:\n");
    ColorPrint("cyan", "1. ");
    ColorPrint("white", "Check reservoirs\n");
    ColorPrint("cyan", "2. ");
    ColorPrint("white", "Check stations\n");
    ColorPrint("cyan", "3. ");
    ColorPrint("white", "Check pipes\n");
    ColorPrint("cyan", "4. ");
    ColorPrint("white", "Activate all components\n");
    ColorPrint("cyan", "5. ");
    ColorPrint("red", "Cancel \n");
    cin.sync();
    switch(readOption(5)) {
        case '1':
            checkDeactivatedReservoirs();
            break;
        case '2':
            checkDeactivatedStations();
            break;
        case '3':
            checkDeactivatedPipes();
            break;
        case '4':
            waterSupply.activateAll();
            ColorPrint("blue", "Activated all components \n");
            pressEnterToContinue();
            break;
        case '5':
            reliabilityMenu();
            break;
    }
}


void Menu::reliabilityMenu() {
    ColorPrint("blue", "Select option:\n");
    ColorPrint("cyan", "1. ");
    ColorPrint("white", "Deactivate components\n");
    ColorPrint("cyan", "2. ");
    ColorPrint("white", "List deactivate components\n");
    ColorPrint("cyan", "3. ");
    ColorPrint("white", "Check deactivated components\n");
    ColorPrint("cyan", "4. ");
    ColorPrint("red", "Cancel \n");
    cin.sync();
    switch (readOption(4)) {
        case '1':
            auxReliability();
            break;
        case '2':
            listReliabilityTesting();
            break;
        case '3':
            checkDeactivatedComponents();
            break;
    }
}

void Menu::auxReliability() {
    vector<std::string> ResStat;
    vector<pair<string, string>> pipes;
    maxFlow.reliabilityPrep(waterSupply.getNetwork());
    reliabilityTesting(ResStat, pipes);
    if (ResStat.empty() && pipes.empty()) return;
    ColorPrint("blue", "Do you wish to make your changes permanent?\n");
    ColorPrint("cyan", "1. ");
    ColorPrint("white", "Yes\n");
    ColorPrint("cyan", "2. ");
    ColorPrint("white", "No\n");
    cin.sync();
    if (readOption(2) == '2') {
        for (const auto& s: ResStat) {
            waterSupply.getNetwork()->findVertex(s)->activate();
        }
        for (const auto& s: pipes) {
            waterSupply.getNetwork()->findEdge(s.first,s.second)->activate();
        }
        waterSupply.maxFlow();
    }
}

void Menu::reliabilityTesting(vector<std::string>& resStat, vector<pair<string, string>>& pipes) {
    ColorPrint("blue", "Select option:\n");
    ColorPrint("cyan", "1. ");
    ColorPrint("white", "Remove a reservoir\n");
    ColorPrint("cyan", "2. ");
    ColorPrint("white", "Remove a station\n");
    ColorPrint("cyan", "3. ");
    ColorPrint("white", "Remove a pipe \n");
    ColorPrint("cyan", "4. ");
    ColorPrint("red", "Cancel \n");
    cin.sync();
    string res;
    pair<string, string> pipe;
    bool end = true;
    vector<double> citiesPrevFlow;
    switch(readOption(4)) {
        case '1':
            res = readReservoirCode();
            if (!res.empty()) {
                for(int i = 1; i <= waterSupply.getCities().size(); i++) {
                    auto city = waterSupply.getCity("C_" + to_string(i));
                    citiesPrevFlow.push_back(waterSupply.computeCityFlow(city.getCode()));
                }
                maxFlow.deleteReservoir(res, waterSupply.getNetwork());
                resStat.push_back(res);
            }
            else end = false;
            break;
        case '2':
            res = readStationCode();
            if (!res.empty()) {
                for(int i = 1; i <= waterSupply.getCities().size(); i++) {
                    auto city = waterSupply.getCity("C_" + to_string(i));
                    citiesPrevFlow.push_back(waterSupply.computeCityFlow(city.getCode()));
                }
                maxFlow.deleteStation(res, waterSupply.getNetwork());
                resStat.push_back(res);
            }
            else end = false;
            break;
        case '3':
            pipe =  readPipeCodes();
            if (!pipe.first.empty() && !pipe.second.empty()) {
                for(int i = 1; i <= waterSupply.getCities().size(); i++) {
                    auto city = waterSupply.getCity("C_" + to_string(i));
                    citiesPrevFlow.push_back(waterSupply.computeCityFlow(city.getCode()));
                }
                pipes.push_back(pipe);
                maxFlow.deletePipe(pipe.first, pipe.second, waterSupply.getNetwork());
            }
            else end = false;
            break;
        case '4':
            if (resStat.empty() && pipes.empty()) reliabilityMenu();
            return;
    }
    if (end) {
        printCitiesFlow(citiesPrevFlow);
        pressEnterToContinue();
        ColorPrint("blue", "Do you want to perform another action?\n");
        ColorPrint("cyan", "1. ");
        ColorPrint("white", "Yes\n");
        ColorPrint("cyan", "2. ");
        ColorPrint("white", "No\n");
        cin.sync();
        if (readOption(2) == '1') reliabilityTesting(resStat, pipes);
    } else reliabilityTesting(resStat, pipes);
}

void Menu::listReliabilityTesting() {
    ColorPrint("blue", "Select option:\n");
    ColorPrint("cyan", "1. ");
    ColorPrint("white", "List remove reservoirs\n");
    ColorPrint("cyan", "2. ");
    ColorPrint("white", "List remove stations\n");
    ColorPrint("cyan", "3. ");
    ColorPrint("white", "List remove pipes\n");
    ColorPrint("cyan", "4. ");
    ColorPrint("red", "Cancel\n");
    cin.sync();
    pair<string, string> pipe;
    vector<pair<string, vector<tuple<string, double, double, double>>>> res;
    pair<string, vector<tuple<string, double, double, double>>> result;
    vector<double> citiesPrevFlow;

    waterSupply.maxFlow();
    for(int i = 1; i <= waterSupply.getCities().size(); i++) {
        auto city = waterSupply.getCity("C_" + to_string(i));
        citiesPrevFlow.push_back(waterSupply.computeCityFlow(city.getCode()));
    }
    switch(readOption(4)) {
        case '1':
            for (int i = 1; i <= waterSupply.getReservoirs().size(); i++) {
                string name = "R_" + to_string(i);
                if(waterSupply.getNetwork()->findVertex(name)->checkActive()) {
                    result.second.clear();
                    maxFlow.deleteReservoir(name, waterSupply.getNetwork());
                    result.first = name;
                    for(int j = 1; j <= waterSupply.getCities().size(); j++) {
                        auto city = waterSupply.getCity("C_" + to_string(j));
                        double flow = waterSupply.computeCityFlow(city.getCode());
                        if (flow != citiesPrevFlow[j-1]) result.second.emplace_back("C_" + to_string(j), flow, city.getDemand(), flow - citiesPrevFlow[j-1]);
                    }
                    res.push_back(result);
                    waterSupply.getNetwork()->findVertex(name)->activate();
                }
            }
            printlistReliability(res, 1);
            waterSupply.maxFlow();
            pressEnterToContinue();
            break;
        case '2':
            for (int i = 1; i <= waterSupply.getStations().size(); i++) {
                string name = "PS_" + to_string(i);
                if(waterSupply.getNetwork()->findVertex(name)->checkActive()) {
                    result.second.clear();
                    maxFlow.deleteStation(name, waterSupply.getNetwork());
                    result.first = name;
                    for(int j = 1; j <= waterSupply.getCities().size(); j++) {
                        auto city = waterSupply.getCity("C_" + to_string(j));
                        double flow = waterSupply.computeCityFlow(city.getCode());
                        if (flow != citiesPrevFlow[j-1]) result.second.emplace_back("C_" + to_string(j), flow, city.getDemand(), flow - citiesPrevFlow[j-1]);
                    }
                    res.push_back(result);
                    waterSupply.getNetwork()->findVertex(name)->activate();
                }
            }
            printlistReliability(res, 2);
            waterSupply.maxFlow();
            pressEnterToContinue();
            break;
        case '3':
            for (const auto& v : waterSupply.getNetwork()->getVertexSet()) {
                for (auto e: v.second->getAdj()) {
                    e->setVisited(false);
                }
            }
            for (const auto& v : waterSupply.getNetwork()->getVertexSet()) {
                if (v.first != "sink" && v.first != "src") {
                    for (auto e: v.second->getAdj()) {
                        if (e->getDest()->getInfo() != "sink" && e->getDest()->getInfo() != "src") {
                            if(e->checkActive() && !e->checkVisited()) {
                                result.second.clear();
                                maxFlow.deletePipe(e->getOrig()->getInfo(), e->getDest()->getInfo(), waterSupply.getNetwork());
                                result.first = (e->getOrig()->getInfo() + " - " + e->getDest()->getInfo());
                                for(int i = 1; i <= waterSupply.getCities().size(); i++) {
                                    auto city = waterSupply.getCity("C_" + to_string(i));
                                    double flow = waterSupply.computeCityFlow(city.getCode());
                                    if (flow != citiesPrevFlow[i-1]) result.second.emplace_back("C_" + to_string(i), flow, city.getDemand(), flow - citiesPrevFlow[i-1]);
                                }
                                res.push_back(result);
                                e->activate();
                                e->setVisited(true);
                                if (e->getReverse() != nullptr) {
                                    e->getReverse()->activate();
                                    e->getReverse()->setVisited(true);
                                }
                            }
                        }
                    }
                }
            }
            printlistReliability(res, 3);
            waterSupply.maxFlow();
            pressEnterToContinue();
            break;
        case '4':
            reliabilityMenu();
            break;
    }
}

void Menu::printlistReliability(const vector<pair<string, vector<tuple<string, double, double, double>>>>& result, int mode) {
    ostringstream file;
    if (mode == 1) {
        ColorPrint("cyan", "\nReservoir: Altered City [Flow Difference](Flow / Demand) | ...\n");
    }
    else if (mode == 2) {
        ColorPrint("cyan", "\nStation: Altered City [Flow Difference](Flow / Demand) | ...\n");
    }
    else {
        ColorPrint("cyan", "\nPipe origin - Pipe destination: Altered City [Flow Difference](Flow / Demand) | ...\n");
    }

    for (auto line: result) {
        ostringstream tmp;
        if (mode <= 2) {
            tmp << left << setw(7) << line.first + ": ";
        }
        else {
            tmp << left << setw(15) << line.first + ": ";
        }
        ColorPrint("blue", tmp.str());
        if (!line.second.empty()) {
            for (int c = 0; c < line.second.size(); c++) {
                if (c != 0 && c%4 == 0) {
                    if (mode <= 2) {
                        ColorPrint("white", "\n       ");
                    }
                    else {
                        ColorPrint("white", "\n               ");
                    }
                }
                tuple<string, double, double, double> city = line.second[c];
                tmp.clear();
                tmp.str("");
                tmp << left << setw(4) << get<0>(city);
                if (c != 0 && (c%4 != 0)) ColorPrint("white", " | " + tmp.str());
                else ColorPrint("white", tmp.str());
                string color;
                string signal;
                (get<3>(city) > 0)? (color = "green") : (color = "red");
                (get<3>(city) > 0)? (signal = " [+") : (signal = " [");
                ColorPrint(color, signal + convertDouble(get<3>(city), 0) + "]");
                ColorPrint("cyan", "(" + convertDouble(get<1>(city), 0) + "/" + convertDouble(get<2>(city), 0) + ")");
            }
            ColorPrint("white", "\n\n");
        } else {
            ColorPrint("pink", "(No changes of flow to any City)\n\n");
        }
    }
    waterSupply.computeFlow();
}

void Menu::printCitiesFlow(vector<double> citiesPrevFlow) {
    ostringstream file;
    if (displayDemand) {
        ColorPrint("cyan", "\nCity - Flow / Demand\n");
        file << "City - Flow / Demand\n\n";
    }
    else {
        ColorPrint("cyan", "\nCity - Flow\n");
        file << "City - Flow\n\n";
    }
    for(int i = 1; i <= waterSupply.getCities().size(); i++) {
        auto city = waterSupply.getCity("C_" + to_string(i));
        double flow = waterSupply.computeCityFlow(city.getCode());
        ostringstream line;
        ostringstream flowDemand;
        if ((city.getDemand() < flow && displayOverflow) || (city.getDemand() > flow && displayUnderflow) || (city.getDemand() == flow && displayOnDemand)) {
            if (displayDemand) {
                flowDemand << flow << " / " << city.getDemand();
                line << left << setw(4) << city.getCode() << " - " << setw(13) << flowDemand.str();
            } else line << left << setw(4) << city.getCode() << " - " << setw(6) << flow;
            ColorPrint("white", line.str());
            file << line.str();
            line.str("");
            line.clear();
            if ((city.getDemand()) < flow) {
                line << " (Overflow by " << flow - (city.getDemand()) << ")";
                ColorPrint("green", line.str());
                file << line.str();
            }
            else if ((city.getDemand()) > flow) {
                line << " (Underflow by " << (city.getDemand()) - flow << ")";
                ColorPrint("yellow", line.str());
                file << line.str();
            }
            line.str("");
            line.clear();
            if (!citiesPrevFlow.empty()) {
                if(citiesPrevFlow[i-1] != flow) {
                    line << " (Previous flow : " << citiesPrevFlow[i-1] << ")";
                    ColorPrint("pink", line.str());
                    file << line.str();
                }
            }
            ColorPrint("white", "\n");
            file << "\n";
        }
    }
    ColorPrint("cyan", "Total: " );
    int flow = waterSupply.computeFlow();
    ColorPrint("white", to_string(flow) + "\n");
    file << "Total: " << flow;
    WaterSupply::OutputToFile("../output/MaxFlow", file.str());
}

void Menu::pressEnterToContinue() {
    ColorPrint("cyan", "\nPress ");
    ColorPrint("yellow", "ENTER");
    ColorPrint("cyan", " to continue\n");
    cin.sync();
    cin.ignore();
}

void Menu::printNetworkStatistics() {
    printCitiesFlow();
    double average = waterSupply.computeAverageDiffCapacityFlow();
    double maxDiff = waterSupply.computeMaxDiffCapacityFlow();
    double variance = waterSupply.computeVarianceDiffCapacityFlow(average);

    ColorPrint("cyan","\nAverage (Capacity - Flow): ");
    ColorPrint("white", convertDouble(average) + "\n");
    ColorPrint("cyan","Max (Capacity - Flow): ");
    ColorPrint("white", convertDouble(maxDiff) + "\n");
    ColorPrint("cyan","Variance (Capacity - Flow): ");
    ColorPrint("white", convertDouble(variance) + "\n");
}

void Menu::swapDisplayOnDemand() {
    displayOnDemand = !displayOnDemand;
}

void Menu::swapDisplayUnderflow() {
    displayUnderflow = !displayUnderflow;
}

void Menu::swapDisplayOverflow() {
    displayOverflow = !displayOverflow;
}

void Menu::swapDisplayDemand() {
    displayDemand = !displayDemand;
}


