#ifndef CSCI115FINALPROJECT_ORDERS_H
#define CSCI115FINALPROJECT_ORDERS_H
#include <string>
using namespace std;

class Order {
private:
    // attributes
    string id;
    int priority;
    string destination;

public:
    Order(const string& orderId, int orderPriority, const string& orderDestination);
    Order();

    // setters
    void setId(const string& orderId);
    void setPriority(int orderPriority);
    void setDestination(const string& orderDestination);


    // getters
    string getId() const;
    int getPriority() const;
    string getDestination() const;

    // displayers
    void displayOrder() const;
};

#endif
