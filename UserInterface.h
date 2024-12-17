#ifndef USERINTERFACE_H
#define USERINTERFACE_H
#include <iostream>
using namespace std;

class UserInterface {
public:
    static void displayMenu();
    static void bigLine();
    static void lilLine();
    static char getInput();
    static bool validInput(char& userInput);
};
#endif