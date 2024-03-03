#include "Menu.h"
#include <iostream>
#include "ColorPrint.h"

using namespace std;

char Menu::readOption(int n){
    string option;
    getline(cin, option);
    while(option.size() > to_string(n).size() || option < "1" || option > to_string(n)){
        if (!option.empty()) ColorPrint("red", "Invalid Input, please try again\n");
        getline(cin, option);
    }
    return option[0];
}

void Menu::run() {
    ColorPrint("blue", "\n-----------------------------------\n");
    ColorPrint("blue", "Water Supply Management System\n");
    ColorPrint("blue", "-----------------------------------\n");
    ColorPrint("blue", "Select option:\n");
    ColorPrint("cyan", "1. ");
    ColorPrint("white", "Network Information \n");
    ColorPrint("cyan", "2. ");
    ColorPrint("white", "Plan trip \n");
    ColorPrint("cyan", "3. ");
    ColorPrint("white", "Settings \n");
    ColorPrint("cyan", "4. ");
    ColorPrint("red", "Quit Manager \n");
    cin.sync();
    switch (readOption(4)) {
        case '3':
            settings();
            break;
        case '4':
            exit(0);
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
    run();
}