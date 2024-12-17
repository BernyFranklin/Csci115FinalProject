#include "UserInterface.h"
#include "Orders.h"
#include <iostream>
#include <cctype>
#include <string>
using namespace std;

void UserInterface::displayMenu() {
     bigLine();
     cout << "Please choose one of the following options:" << endl;
     bigLine();
     cout << "1.\tView Order Listings Ascending" << endl
          << "2.\tView Order Listings Descending" << endl
          << "3.\tAdd Order" << endl
          << "4.\tDelete Order" << endl
          << "5.\tFind Order by Order ID" << endl
          << "6.\tView Route by Order ID" << endl
          << "7.\tSort And View by Priority" << endl
          << "0.\tQuit" << endl;
     lilLine();
}
void UserInterface::bigLine() {
    cout << "================================================" << endl;
}
void UserInterface::lilLine() {
    cout << "------------------------------------------------" << endl;
}
char UserInterface::getInput() {
    bool validityCheck = false;
    char userInput;
    string userString;
    while (!validityCheck) {
        cout << "Please Select an option: ";
        cin >> userString;
        userInput = userString[0];
        validityCheck = validInput(userInput);
    }
    return userInput;
}
bool UserInterface::validInput(char& userInput) {
    string validStringExample = "\nInput must be 0 - 7, please enter another selection.\n";

    if (isdigit(userInput)) {
        if (userInput < '0' || userInput > '7'){
            cout << validStringExample;
            return false;
        }
        return true;
    }
    cout << validStringExample;
    return false;
}
Order UserInterface::addOrder(string& orderId) {
    bool valid = false;
    string userInput;
    int priority;
    string destination;
    while (!valid) {
        cout << "Please Enter a Priority 1 - 5: ";
        cin >> userInput;
        if(isdigit(userInput[0]) && !(userInput[0] < '1' || userInput[0] > '7')) {
            priority = stoi(userInput);
            valid = true;
        }
        else {
            cout << "Invalid priority, please try again" << endl;
        }
    }
    valid = false;
    userInput = "";
    while (!valid) {
        cout << "Please Enter a Destination B - J: ";
        cin >> userInput;
        userInput = toupper(userInput[0]);
        if (userInput.length() == 1 && !(userInput[0] < 'B' || userInput[0] > 'J')) {
            destination = userInput[0];
            valid = true;
        }
        else {
            cout << "Invalid Destination, please try again" << endl;
        }
    }
    Order newOrder = Order(orderId, priority, destination);
    return newOrder;
}
string UserInterface::removeOrder() {
    string userInput;
    cout << "Please enter id of order to delete: ";
    cin >> userInput;
    return userInput;
}
