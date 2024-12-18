#ifndef USERINTERFACE_H
#define USERINTERFACE_H
#include "Orders.h"
#include "ArrayOrderList.h"
#include <iostream>
using namespace std;

class UserInterface {
public:
    static void displayMenu();
    static void bigLine();
    static void lilLine();
    static char getInput();
    static bool validInput(char& userInput);
    static Order addOrder(string& orderId);
    static string getOrderId();
    static string generateOrderId(ArrayOrderList& list);
};
#endif