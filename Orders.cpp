#include "Orders.h"
#include <iostream>

using namespace std;

// paramater based constructor
Order::Order(const string& orderId, int orderPriority, const string& orderDestination)
    : id(orderId), priority(orderPriority), destination(orderDestination) {}

    // default constructor
    Order::Order() : id(""), priority(0), destination("") {}

    // getters
    string Order::getId() const {return id;}
    int Order::getPriority() const {return priority;}
    string Order::getDestination() const {return destination;}

    // setters
    void Order::setId(const std::string &orderId) {id = orderId;}
    void Order::setPriority(int orderPriority) {priority = orderPriority;}
    void Order::setDestination(const std::string &orderDestination) {destination = orderDestination;}

    // displayer
    void Order::displayOrder() const {
    cout << "Order ID:\t\t" << id << endl
         << "Priority:\t\t" << priority << endl
         << "Destination:\tLocation " << destination << endl
         << "-----------------------------------------------" << endl;
}