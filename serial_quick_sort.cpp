// Local includes
#include "serial_quick_sort.h"

// Standard library includes
#include <chrono>
#include <iostream>
#include <random>

// Standard Constuctor
SerialQuickSort::SerialQuickSort() {
    // Initialize all of the private data
    isFilled = false;
    isSorted = false;
    numCores = 1;
    size_ = 0;
    exec_time_ms = 0;
    data = nullptr;
}

// Size-Specified Constructor
SerialQuickSort::SerialQuickSort(int size, int min, int max) {
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
SerialQuickSort::~SerialQuickSort() {
    // Free any leftover data
    if (data != nullptr) {
        delete data;
    }
}

// Main function. Do the sorting
void SerialQuickSort::Sort() {
    // Start the timer
    auto t1 = std::chrono::high_resolution_clock::now();

    // Helper function does the work
    QuickSortHelper(0, size_ - 1);

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
bool SerialQuickSort::VerifySort() {
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
void SerialQuickSort::Print() {
    // Make sure data exists
    if (!isFilled) {
        std::cout << "Cannot print an empty dataset" << std::endl;
        return;
    }

    std::cout << "Begin Data for Serial Quick Sort" << std::endl;
    // Loop through and print the data
    for (int i = 0; i < size_; i++) {
        std::cout << data[i] << std::endl;
    }
    std::cout << "End Data for Serial Quick Sort" << std::endl;
}

// Report timing
void SerialQuickSort::ReportTiming() {
    std::cout << "The most recent run used serial quick sort to sort " <<
        size_ << " values in " << exec_time_ms / 1000 << " seconds" << std::endl;
}

// Report efficiency
void SerialQuickSort::ReportEfficiency() {
    std::cout << "Since serial quick sort uses only 1 core, the efficiency is 1.0" << std::endl;
}

// Report Speedup
void SerialQuickSort::ReportSpeedup() {
    std::cout << "Since serial quick sort uses only 1 core, the speedup is 1.0" << std::endl;
}

// Fill the data. If the filename is specified, ingest the data from a file
void SerialQuickSort::FillData(int size, int min, int max) {
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
void SerialQuickSort::ClearData() {
    delete data;
    data = nullptr;
    size_ = 0;
    isFilled = false;
    isSorted = false;
}

// Getters
bool SerialQuickSort::IsSorted() { return isSorted; }
bool SerialQuickSort::IsFilled() { return isFilled; }
int SerialQuickSort::Size() { return size_; }

// Helper Computation Methods
double SerialQuickSort::ComputeEfficiency() {
    // Serial methods have an efficiency of 1 by default
    return 1.0;
}

double SerialQuickSort::ComputeSpeedup() {
    // Serial methods have a speedup of 1 by default
    return 1.0;
}

void SerialQuickSort::Swap(int indexA, int indexB) {
    int temp = data[indexA];
    data[indexA] = data[indexB];
    data[indexB] = temp;
}

int SerialQuickSort::Partition(int low, int high) {
    int pivot = data[high];

    int i = (low - 1);

    for (int j = low; j < high; j++) {
        if (data[j] <= pivot) {
            i++;
            Swap(i, j);
        }
    }
    Swap(i+1, high);

    return (i + 1);
}

void SerialQuickSort::QuickSortHelper(int low, int high) {
    if (low < high) {
        int pivot = Partition(low, high);
        QuickSortHelper(low, pivot - 1);
        QuickSortHelper(pivot + 1, high);
    }
}