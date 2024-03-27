#include "Menu.h"
#include <iostream>
#include <sstream>
#include <iomanip>
#include <map>
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

void Menu::printPipeDestinations(const string& code){
    auto pipe = waterSupply.getNetwork().findVertex(code);
    for(auto dest : pipe->getAdj()){
        ColorPrint("yellow", " " + dest->getDest()->getInfo());
        if(dest != *(pipe->getAdj().end()-1)) ColorPrint("blue",",");
    }
}

pair<string, string> Menu::readPipeCodes(){
    string code, code2;
    do {
    ColorPrint("cyan", "Pipe source code: \n");
    getline(cin, code);
    transform(code.begin(), code.end(), code.begin(), ::toupper);
    while(!waterSupply.existsCode(code)) {
        ColorPrint("red","Invalid code, please try again\n");
        getline(cin, code);
        transform(code.begin(), code.end(), code.begin(), ::toupper);
    }
    ColorPrint("cyan", "Pipe destination code: ");
    ColorPrint("blue","[");
    printPipeDestinations(code);
    ColorPrint("blue"," ]\n");
    getline(cin, code2);
    transform(code2.begin(), code2.end(), code2.begin(), ::toupper);
    while(!waterSupply.existsCode(code2)) {
        ColorPrint("red","Invalid code, please try again\n");
        getline(cin, code2);
        transform(code2.begin(), code2.end(), code2.begin(), ::toupper);
    }
    if (!waterSupply.existsPipe(code, code2)) ColorPrint("red","Invalid pipe, please try again\n");;
    }
    while (!waterSupply.existsPipe(code, code2));
    return make_pair(code, code2);
}

string Menu::readStationCode(){
    string code;
    ColorPrint("cyan", "Station code: \n");
    getline(cin, code);
    transform(code.begin(), code.end(), code.begin(), ::toupper);
    while(!waterSupply.existsStationByCode(code)) {
        ColorPrint("red","Invalid station code, please try again\n");
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
        ColorPrint("white", "Network reliability\n");
        ColorPrint("cyan", "4. ");
        ColorPrint("white", "Settings \n");
        ColorPrint("cyan", "5. ");
        ColorPrint("red", "Quit Manager \n");
        cin.sync();
        switch (readOption(5)) {
            case '1':
                getNetworkInfo();
                break;
            case '2':
                getMaxFlowOp();
                break;
            case '3':
                auxReliability();
                break;
            case '4':
                settings();
                break;
            case '5':
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
    vector<City> orderedCities;
    switch (readOption(6)) {
        case '1':
            code = readCityCode();
            ColorPrint("blue", "Code | City | Demand | Population\n");
            printCity(waterSupply.getCity(code));
            pressEnterToContinue();
            break;
        case '2':
            code = readCityName();
            ColorPrint("blue", "Code | City | Demand | Population\n");
            printCity(waterSupply.getCity(code));
            pressEnterToContinue();
            break;
        case '3':
            code = readCityId();
            ColorPrint("blue", "Code | City | Demand | Population\n");
            printCity(waterSupply.getCity(code));
            pressEnterToContinue();
            break;
        case '4':
            orderedCities.reserve(waterSupply.getCities().size());
            for(const auto& city : waterSupply.getCities()){
                orderedCities.push_back(city.second);
            }
            std::sort(orderedCities.begin(), orderedCities.end());
            ColorPrint("blue", "Code | City | Demand | Population\n");
            for (const auto& c:orderedCities) {
                printCity(c);
            }
            pressEnterToContinue();
            break;
        case '5':
            getCityStatistics();
            break;
        case '6':
            getNetworkInfo();
            break;
    }
}

void Menu::printCity(City city) {
    ostringstream oss;
    oss << setw(4) << left << city.getCode() << " | " << city.getName() + " | " << city.getDemand() << " | " << city.getPopulation() << "\n";
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
    vector<Reservoir> mun;
    switch (readOption(7)) {
        case '1':
            code = readReservoirCode();
            ColorPrint("blue", "Code | Reservoir | Municipality | Max Delivery \n");
            printReservoir(waterSupply.getReservoir(code));
            pressEnterToContinue();
            break;
        case '2':
            code = readReservoirName();
            ColorPrint("blue", "Code | Reservoir | Municipality | Max Delivery \n");
            printReservoir(waterSupply.getReservoir(code));
            pressEnterToContinue();
            break;
        case '3':
            code = readReservoirID();
            ColorPrint("blue", "Code | Reservoir | Municipality | Max Delivery \n");
            printReservoir(waterSupply.getReservoir(code));
            pressEnterToContinue();
            break;
        case '4':
            mun = readReservoirMunicipality();
            ColorPrint("blue", "Code | Reservoir | Municipality | Max Delivery \n");
            for (const auto& r: mun) {
                printReservoir(r);
            }
            pressEnterToContinue();
            break;
        case '5':
            ColorPrint("blue", "Code | Reservoir | Municipality | Max Delivery \n");
            for (const auto& r: waterSupply.getReservoirs()) {
                printReservoir(r.second);
            }
            pressEnterToContinue();
            break;
        case '6':
            getReservoirStatistics();
            break;
        case '7':
            getNetworkInfo();
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
            ColorPrint("blue", "Code | Reservoir | Municipality | Max Delivery \n");
            for (auto r: values) {
                printReservoir(r);
            }
            pressEnterToContinue();
            break;
        case '2':
            values = waterSupply.getReservoirMinDel();
            ColorPrint("blue", "Code | Reservoir | Municipality | Max Delivery \n");
            for (auto r: values) {
                printReservoir(r);
            }
            pressEnterToContinue();
            break;
        case '3':
            getReservoirInfo();
            break;
    }
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
    ColorPrint("white", "Get optimal max flow\n");
    ColorPrint("cyan", "2. ");
    ColorPrint("white", "Get cities with underflow in optimal case\n");
    ColorPrint("cyan", "3. ");
    ColorPrint("white", "Get max flow with excess\n");
    ColorPrint("cyan", "4. ");
    ColorPrint("red", "Cancel \n");
    cin.sync();
    double total = 0;
    string code;
    ostringstream oss;
    vector<City> orderedCities;
    switch (readOption(6)) {
        case '1':
            waterSupply.optimalResMaxFlow();
            waterSupply.computeCitiesStatistics();
            ColorPrint("cyan", "Total: ");
            ColorPrint("white", to_string(waterSupply.computeMaxFlow()));
            pressEnterToContinue();
            break;
        case '2':
            waterSupply.optimalResMaxFlow();
            orderedCities.reserve(waterSupply.getCities().size());
            for(const auto& city : waterSupply.getCities()) orderedCities.push_back(city.second);
            std::sort(orderedCities.begin(), orderedCities.end());
            for(const auto& v: orderedCities) {
                double flow = waterSupply.getNetwork().findVertex(v.getCode())->getIncomingFlow();
                total += v.getDemand() - flow;
                if ((v.getDemand()) > flow) {
                    ColorPrint("cyan", v.getCode() + " " + v.getName());
                    ColorPrint("white", " - underflow by " + to_string((int)(v.getDemand() - flow)) + "\n");
                }
            }
            ColorPrint("cyan", "Total underflow: ");
            ColorPrint("white", to_string((int)total));
            break;
        case '3':
            getMaxFlowExcessOp();
            break;
    }
}

void Menu::getMaxFlowExcessOp() {
    ColorPrint("cyan", "1. ");
    ColorPrint("white", "Get optimal max flow with excess\n");
    ColorPrint("cyan", "2. ");
    ColorPrint("white", "Get max flow to specific city\n");
    ColorPrint("cyan", "3. ");
    ColorPrint("white", "Get max flow to each city\n");
    ColorPrint("cyan", "4. ");
    ColorPrint("white", "Get optimal max flow with excess to a specific city\n");
    ColorPrint("cyan", "5. ");
    ColorPrint("red", "Cancel \n");
    cin.sync();
    string code;
    ostringstream oss;
    vector<City> orderedCities;
    switch (readOption(5)) {
        case '1':
            waterSupply.optimalExcessMaxFlow();
            waterSupply.computeCitiesStatistics();
            ColorPrint("cyan", "Total: ");
            ColorPrint("white", to_string(waterSupply.computeMaxFlow()));
            pressEnterToContinue();
            break;
        case '2':
            code = readCityCode();
            waterSupply.cityMaxFlow(code);
            ColorPrint("cyan", "Total: ");
            ColorPrint("white", to_string(waterSupply.computeCityFlow(code)));
            pressEnterToContinue();
            break;
        case '3':
            oss << "City - Flow\n";
            orderedCities.reserve(waterSupply.getCities().size());
            for(const auto& city : waterSupply.getCities()) orderedCities.push_back(city.second);
            std::sort(orderedCities.begin(), orderedCities.end());
            for(const auto& c : orderedCities){
                waterSupply.cityMaxFlow(c.getCode());
                oss << left << setw(4) << c.getCode() << " - " + to_string(waterSupply.computeCityFlow(c.getCode())) + "\n";
            }
            WaterSupply::OutputToFile("../output/CitiesMaxFlow", oss.str());
            cout << oss.str();
            pressEnterToContinue();
            break;
        case '4':
            code = readCityCode();
            waterSupply.optimalExcessCityMaxFlow(code);
            waterSupply.computeCitiesStatistics();
            ColorPrint("cyan", "Total to " + waterSupply.getCity(code).getName() + ": ");
            ColorPrint("white", to_string(waterSupply.computeCityFlow(code)) + "\n");
            ColorPrint("cyan", "Total: ");
            ColorPrint("white", to_string(waterSupply.computeMaxFlow()));
            pressEnterToContinue();
            break;
    }
}

void Menu::auxReliability() {
    vector<std::string> ResStat;
    vector<pair<string, string>> pipes;
    waterSupply.reliabilityPrep();
    reliabilityTesting(ResStat, pipes);
    waterSupply.reliabilityTearDown();
    ColorPrint("blue", "Do you wish to make your changes permanent?\n");
    ColorPrint("cyan", "1. ");
    ColorPrint("white", "Yes\n");
    ColorPrint("cyan", "2. ");
    ColorPrint("white", "No\n");
    cin.sync();
    if (readOption(2) == '2') {
        for (const auto& s: ResStat) {
            waterSupply.activate(s);
        }
        for (const auto& s: pipes) {
            waterSupply.activatePipe(s.first, s.second);
        }
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
    switch(readOption(4)) {
        case '1':
            res = readReservoirCode();
            waterSupply.deleteReservoir(res);
            resStat.push_back(res);
            break;
        case '2':
            res = readStationCode();
            waterSupply.deleteStation(res);
            resStat.push_back(res);
            break;
        case '3':
            pair<string, string> pipe =  readPipeCodes();
            pipes.push_back(pipe);
            waterSupply.deletePipe(pipe.first, pipe.second);
            break;
    }
    waterSupply.computeCitiesStatistics();
    ColorPrint("cyan", "Total: ");
    ColorPrint("white", to_string(waterSupply.computeMaxFlow()) + "\n");
    pressEnterToContinue();
    ColorPrint("blue", "Do you want to perform another action?\n");
    ColorPrint("cyan", "1. ");
    ColorPrint("white", "Yes\n");
    ColorPrint("cyan", "2. ");
    ColorPrint("white", "No\n");
    cin.sync();
    if (readOption(2) == '1') reliabilityTesting(resStat, pipes);
}

void Menu::pressEnterToContinue() {
    ColorPrint("cyan", "\nPress ");
    ColorPrint("yellow", "ENTER");
    ColorPrint("cyan", " to continue\n");
    cin.sync();
    cin.ignore();
}


