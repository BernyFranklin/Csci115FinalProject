#include "OrderSorting.h"
#include <cstdlib>      // for rand
#include <ctime>        // for seeding rand
#include <sstream>      // for generating orderId in hex
#include <iomanip>      // for formatting
#include <iostream>     // for output
#include <chrono>       // for tracking time
#include <fstream>      // for accessing files

using namespace std;

string sortedString = "\nOrders sorted by priority in ascending order";

// generates N Order objects and stores them in an ArrayOrderList
void OrderSorting::generateOrders(int n, ArrayOrderList& list) {
    srand(time(nullptr));       // seed the random number generator

    char destination = 'A';     // start with 'A' for the destination

    // create N orders
    for (int i = 1; i <= n; i++) {
        //generate orderId in hex
        stringstream ss;
        ss << "ORD" << hex << uppercase << setw(4) << setfill('0') << i;
        // set to string
        string orderId = ss.str();

        // generate a random priority
        int priority = (rand() % 5) + 1;

        // create the Order object and add it to the list
        list.addOrder(Order(orderId, priority, string(1, destination)));

        // increment destination, cycling through A-Z
        destination = (destination == 'J') ? 'B' : destination + 1;
    }
}

// we do a lot of swaps, figured i'd make the code cleaner
void OrderSorting::swap(ArrayOrderList& list, int index1, int index2) {
    Order temp = list.getOrder(index1);
    list.setOrder(index1, list.getOrder(index2));
    list.setOrder(index2, temp);
}

// used to time our sorting functions
void OrderSorting::timedSort(const function<void(ArrayOrderList &)> &sortingFunction, ArrayOrderList &list) {
    //start timing
    auto start = chrono::high_resolution_clock::now();

    // execute sorting function
    sortingFunction(list);

    // STOP THE CLOCK
    auto end = chrono::high_resolution_clock::now();

    // calculate the duration
    auto duration = chrono::duration_cast<chrono::microseconds>(end - start).count();

    // display
    cout << "Sorting completed in " << duration << " microseconds." << endl;
}

// used for visualizing our sorting
void logIntermediateState(ArrayOrderList& list, const string& filename) {
    ofstream file(filename, ios::app);          // open file in append mode
    // file error
    if (!file.is_open()) {
        cerr << "\n\nError opening file for logging." << endl;
        return;
    }
    for (int i = 0; i < list.getSize(); i++) {
        file << list.getOrder(i).getPriority();
        if (i != list.getSize() - 1) file << ",";
    }
    file << "\n";
    file.close();
}

// performs selection sort of ArrayOrderList and sorts by priority
void OrderSorting::selectionSort(ArrayOrderList &list) {
    int n = list.getSize();     // gets number of elements in array

    for (int i = 0; i < n - 1; i++) {
        int minIndex = i;

        // find index of the smallest element in the unsorted part
        for (int j = i + 1; j < n; j++) {
            if (list.getOrder(j).getPriority() < list.getOrder(minIndex).getPriority())
                minIndex = j;
        }

        // swap the current element with the smallest element found
        if (minIndex != i) {
            swap(list, i , minIndex);                       // second swap
        }
    }

    // alert user
    cout << sortedString << "Selection Sort." << endl;
}

// performs bubble sort of ArrayOrderList and sorts by priority
void OrderSorting::bubbleSort(ArrayOrderList &list) {
    int n = list.getSize();

    for (int i = 0; i < n; i++) {
        bool swapped = false;       // used to terminate early
        //perform single pass of the bubble sort
        for (int j = 0; j < n - i - 1; j++) {
            if (list.getOrder(j).getPriority() > list.getOrder(j + 1).getPriority()) {
                //swap elements
                swap(list, j, j + 1);
                swapped = true;
            }
        }
        // if no swaps were made, the list is sorted
        if (!swapped) break;
    }

    // alert user
    cout << sortedString << "Bubble Sort." << endl;
}

// performs merge sort of ArrayOrderList and sorts by priority
// uses 2 helper functions and the main mergeSort function
void merge(ArrayOrderList& list, int left, int mid, int right) {
    int n1 = mid - left + 1;            // size of left array
    int n2 = right - mid;               // size of right array

    // temp vectors to hold sub arrays
    vector<Order> leftArray(n1);
    vector<Order> rightArray(n2);

    // copy data to temp vectors
    for (int i = 0; i < n1; i++) leftArray[i] = list.getOrder(left+i);
    for (int i = 0; i < n2; i++) rightArray[i] = list.getOrder(mid + 1 + i);

    // merge the temp arrays back into the list
    int i = 0, j = 0, k = left;
    while (i < n1 && j < n2) {
        if (leftArray[i].getPriority() <= rightArray[j].getPriority()) {
            list.setOrder(k++, leftArray[i++]);
        }
        else {
            list.setOrder(k++, rightArray[j++]);
        }
    }
    // copy remaining values from both temp arrays
    while (i < n1) list.setOrder(k++, leftArray[i++]);
    while (j < n2) list.setOrder(k++, rightArray[j++]);

}
void mergeSortHelper(ArrayOrderList& list, int left, int right) {
    if (left < right) {
        int mid = left + (right - left) / 2;

        // recursively sort the first and second halves
        mergeSortHelper(list, left, mid);
        mergeSortHelper(list, mid + 1, right);

        // merge sorted halves
        merge(list, left, mid, right);
    }
}
void OrderSorting::mergeSort(ArrayOrderList &list) {
    mergeSortHelper(list, 0, list.getSize() - 1);
    cout << sortedString << endl;
}

// performs quick sort of ArrayOrderList and sorts by priority
// uses 2 helper functions and the main quickSort function
int partition(ArrayOrderList& list, int low, int high) {
    Order pivot = list.getOrder(high);          // using last element as pivot
    int i = low - 1;                                  // index of smaller element

    for (int j = low; j < high; j++) {
        if (list.getOrder(j).getPriority() <= pivot.getPriority()) {
            i++;
            OrderSorting::swap(list, i, j);
        }
    }

    // swap the pivot element with the element at i + 1;
    OrderSorting::swap(list, i + 1, high);
    return i + 1;
}
void quickSortHelper(ArrayOrderList& list, int low, int high) {
    if (low < high) {
        //partition index
        int pi = partition(list, low, high);        // partition the array

        // recursively sort elements before and after the parititon
        quickSortHelper(list, low, pi - 1);
        quickSortHelper(list, pi + 1, high);
    }
}
void OrderSorting::quickSort(ArrayOrderList& list) {
    quickSortHelper(list, 0, list.getSize() - 1);
    cout << sortedString << endl;
}



