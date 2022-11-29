// Local includes
#include "serial_insertion_sort.h"

// Standard library includes
#include <iostream>
#include <random>

// Min and maxes
#define RAND_MINIMUM 0
#define RAND_MAXIMUM 999

// Standard Constuctor
SerialInsertionSort::SerialInsertionSort() {
    // Initialize all of the booleans to false
    isFilled = false;
    isSorted = false;
    isTimed = false;
    data = nullptr;
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
SerialInsertionSort::~SerialInsertionSort() {
    // Free any leftover data
    if (data != nullptr) {
        delete data;
    }
}

// Main function. Do the sorting
void SerialInsertionSort::Sort() {
    // Outer loop
    for (int i = 1; i < size_; i++) {
        int temp = data[i];
        int j = i - 1;
        // Inner loop
        while (temp < data[j] && j >= 0) {
            data[j+1] = data[j];
            --j;
        }
        data[j+1] = temp;
    }
}

// Verifies that the underlying data is sorted
// Also updates the isSorted member
bool SerialInsertionSort::VerifySort() {
    // Null pointer check
    if (data == nullptr) {
        std::cout << "Cannot verify a null dataset" << std::endl;
        isFilled = false;
        return isFilled;
    }
    // Iterate through the vector and make sure that
    // ascending order is true
    for (int i = 0; i < size_ - 1; i++) {
        if (data[i] > data[i+1]) {
            std::cout << "Data is not in sorted order for Serial Insertion Sort" << std::endl;
            isSorted = false;
            return isSorted;
        }
    }

    // If here, then the sort was successful
    std::cout << "Data is in sorted order for Serial Insertion Sort" << std::endl;
    isSorted = true;

    return isSorted;
}

// Prints the data
void SerialInsertionSort::Print() {
    // Null pointer check
    if (data == nullptr) {
        std::cout << "Cannot print a null dataset" << std::endl;
        isFilled = false;
        return;
    }
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
void SerialInsertionSort::FillData(int size, std::string filename) {
    // Clear the data
    ClearData();
    data = new int[size];

    if (filename != "") {
        isDataRandom = false;
    } else {
        // Use C++ libraries to generate random values
        std::random_device rd;
        std::mt19937 rng(rd());
        std::uniform_int_distribution<int> uni(RAND_MINIMUM, RAND_MAXIMUM);

        for (int i = 0; i < size; i++) {
            data[i] = uni(rng);
        }
        isDataRandom = true;
    }

    size_ = size;
    isFilled = true;
}

// Clear the data
void SerialInsertionSort::ClearData() {
    delete data;
    data = nullptr;
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
    // Serial methods have an efficiency of 1 by default
    return 1.0;
}

double SerialInsertionSort::ComputeSpeedup() {
    // Serial methods have a speedup of 1 by default
    return 1.0;
}