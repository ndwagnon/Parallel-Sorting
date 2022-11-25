// Local includes
#include "serial_insertion_sort.h"

// Standard library includes
#include <iostream>
#include <stdlib.h>

// Standard Constuctor
SerialInsertionSort::SerialInsertionSort() {
    // Initialize all of the booleans to false
    isFilled = false;
    isSorted = false;
    isTimed = false;
}

// Size-Specified Constructor
SerialInsertionSort::SerialInsertionSort(int size) {
    // Initialize all of the booleans to false
    isFilled = false;
    isSorted = false;
    isTimed = false;

    // Fill the data
    FillData(size);
}

// Size and Data Specified Constructor
SerialInsertionSort::SerialInsertionSort(int size, std::string filename) {
    // Initialize all of the booleans to false
    isFilled = false;
    isSorted = false;
    isTimed = false;

    // Fill the data
    FillData(size, filename);
}

// NOP Destructor
SerialInsertionSort::~SerialInsertionSort() {}

// Main function. Do the sorting
void SerialInsertionSort::Sort() {

}

// Verifies that the underlying data is sorted
// Also updates the isSorted member
bool SerialInsertionSort::VerifySort() {
    // Iterate through the vector and make sure that
    // ascending order is true
    for (int i = 0; i < size_; i++) {
        if (data[i] > data[i+1]) {
            std::cout << "Data is not in sorted order for Serial Insertion Sort" << std::endl;
            isSorted = false;
        }
    }

    // If here, then the sort was successful
    std::cout << "Data is in sorted order for Serial Insertion Sort" << std::endl;
    isSorted = true;

    return isSorted;
}

// Prints the data
void SerialInsertionSort::Print() {
    std::cout << "Begin Data for Serial Insertion Sort" << std::endl;
    // Loop through and print the data
    for (int i = 0; i < size_; i++) {
        std::cout << data[i] << std::endl;
    }
    std::cout << "End Data for Serial Insertion Sort" << std::endl;
}

// Report timing
void SerialInsertionSort::ReportTiming() {

}

// Report efficiency
void SerialInsertionSort::ReportEfficiency() {

}

// Report Speedup
void SerialInsertionSort::ReportSpeedup() {

}

// Fill the data. If the filename is specified, ingest the data from a file
void SerialInsertionSort::FillData(int size, std::string filename = "") {
    // Clear the data
    ClearData();

    if (filename != "") {
        isDataRandom = false;
    } else {
        // Set the seed to the current time
        srand(time(0));
        for (int i = 0; i < size; i++) {
            data.push_back(rand());
        }
        isDataRandom = true;
    }

    isFilled = true;
}

// Clear the data
void SerialInsertionSort::ClearData() {
    data.clear();
    size_ = 0;
    isFilled = false;
}

// Getters
bool SerialInsertionSort::IsSorted() { return isSorted; }
bool SerialInsertionSort::IsTimed() { return isTimed; }
bool SerialInsertionSort::IsFilled() { return isFilled; }
bool SerialInsertionSort::IsDataRandom() { return isDataRandom; }
int SerialInsertionSort::Size() { return size_; }

// Helper Computation Methods
double SerialInsertionSort::ComputeEfficiency() {

}

double SerialInsertionSort::ComputeSpeedup() {

}