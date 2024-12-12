#ifndef ORDER_SORTING_H
#define ORDER_SORTING_H

#include "ArrayOrderList.h"

class OrderSorting {
public:

    static void generateOrders(int n, ArrayOrderList& list);            // generate N Order objects in an array
    static void selectionSort(ArrayOrderList& list);                    // performs selection sort by priority
    static void bubbleSort(ArrayOrderList& list);                       // performs bubble sort by priority
    static void swap(ArrayOrderList& list, int index1, int index2);     // swaps two orders
};

#endif