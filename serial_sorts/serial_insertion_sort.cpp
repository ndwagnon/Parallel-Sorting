// Local includes
#include "serial_insertion_sort.h"

// Standard library includes
#include <chrono>
#include <iostream>
#include <random>

// Standard Constuctor
SerialInsertionSort::SerialInsertionSort() {
    // Initialize all of the private data
    isFilled = false;
    isSorted = false;
    numCores = 1;
    size_ = 0;
    exec_time_ms = 0;
    data = nullptr;
}

// Size-Specified Constructor
SerialInsertionSort::SerialInsertionSort(int size, int min, int max) {
    // Initialize all of the private data
    isFilled = false;
    isSorted = false;
    numCores = 1;
    size_ = 0;
    exec_time_ms = 0;
    data = nullptr;

    // Fill the data
    FillData(size, min, max);
}

// Destructor
SerialInsertionSort::~SerialInsertionSort() {
    // Free any leftover data
    if (data != nullptr) {
        delete data;
    }
}

// Main function. Do the sorting
void SerialInsertionSort::Sort() {
    // Start the timer
    auto t1 = std::chrono::high_resolution_clock::now();

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

    // End the timer
    auto t2 = std::chrono::high_resolution_clock::now();
    std::chrono::duration<double, std::milli> ms_double = t2 - t1;
    exec_time_ms = ms_double.count();

    // Data is now sorted
    isSorted = true;
    return;
}

// Verifies that the underlying data is sorted
// Also updates the isSorted member
bool SerialInsertionSort::VerifySort() {
    // Make sure data exists
    if (!isFilled) {
        std::cout << "Cannot verify an empty dataset" << std::endl;
        isSorted = false;
        return false;
    }
    // Iterate through the vector and make sure that
    // ascending order is true
    for (int i = 0; i < size_ - 1; i++) {
        if (data[i] > data[i+1]) {
            isSorted = false;
            return false;
        }
    }

    // If here, then the sort was successful
    isSorted = true;
    return true;
}

// Prints the data
void SerialInsertionSort::Print() {
    // Make sure data exists
    if (!isFilled) {
        std::cout << "Cannot print an empty dataset" << std::endl;
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
    std::cout << "The most recent run used serial insertion sort to sort " <<
        size_ << " values in " << exec_time_ms / 1000 << " seconds" << std::endl;
}

// Fill the data. If the filename is specified, ingest the data from a file
void SerialInsertionSort::FillData(int size, int min, int max) {
    // Clear the data
    ClearData();
    data = new int[size];

    // Use C++ libraries to generate random values
    std::random_device rd;
    std::mt19937 rng(rd());
    std::uniform_int_distribution<int> uni(min, max);

    // Fill the data
    for (int i = 0; i < size; i++) {
        data[i] = uni(rng);
    }

    // Update member variables
    size_ = size;
    isFilled = true;
    isSorted = false;
}

// Clear the data
void SerialInsertionSort::ClearData() {
    delete data;
    data = nullptr;
    size_ = 0;
    isFilled = false;
    isSorted = false;
}

// Getters
bool SerialInsertionSort::IsSorted() { return isSorted; }
bool SerialInsertionSort::IsFilled() { return isFilled; }
int SerialInsertionSort::Size() { return size_; }