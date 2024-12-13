#ifndef ORDER_SORTING_H
#define ORDER_SORTING_H

#include "ArrayOrderList.h"
#include <functional>

using namespace std;

class OrderSorting {
public:
    // helpers
    static void generateOrders(int n, ArrayOrderList& list);            // generate N Order objects in an array
    static void swap(ArrayOrderList& list, int index1, int index2);     // swaps two orders
    // times the execution of our sorting algorithms
    static void timedSort(const function<void(ArrayOrderList&)>& sortingFunction, ArrayOrderList& list);
    // sorters
    static void selectionSort(ArrayOrderList& list);                    // performs selection sort by priority
    static void bubbleSort(ArrayOrderList& list);                       // performs bubble sort by priority
    static void mergeSort(ArrayOrderList& list);                        // performs merge sort by priority
    static void quickSort(ArrayOrderList& list);                        // performs quick sort by priority

};

#endif