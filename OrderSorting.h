#ifndef ORDER_SORTING_H
#define ORDER_SORTING_H

#include "ArrayOrderList.h"

class OrderSorting {
public:

    static void generateOrders(int n, ArrayOrderList& list);    // generate N Order objects in an array
    static void selectionSort(ArrayOrderList& list);            // performs selection sort by priority
};

#endif