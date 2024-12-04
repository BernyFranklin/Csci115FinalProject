#ifndef CSCI115FINALPROJECT_ORDERS_H
#define CSCI115FINALPROJECT_ORDERS_H
#include <string>
using namespace std;

class Order {
private:
    string id;
    int priority;
    string destination;

public:
    Order(const string& orderId, int orderPriority, const string& orderDestination);
    Order();

    // setters
    string getId() const;
    int getPriority() const;
    string getDestination() const;

    // getters
    void setId(const string& orderId);
    void setPriority(int orderPriority);
    void setDestination(const string& orderDestination);

    // displayers
    void displayOrder() const;
};

#endif //CSCI115FINALPROJECT_ORDERS_H
