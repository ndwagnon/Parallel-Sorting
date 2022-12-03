// Local includes
#include "std_parallel_quick_sort.h"

// Standard library includes
#include <chrono>
#include <iostream>
#include <random>

// Standard Constuctor
StdParallelQuickSort::StdParallelQuickSort() {
    // Initialize all of the private data
    isFilled = false;
    isSorted = false;
    numCores = 1;
    size_ = 0;
    exec_time_ms = 0;
    data = nullptr;
}

// Size-Specified Constructor
StdParallelQuickSort::StdParallelQuickSort(int size, int min, int max, int numCores_a) {
    // Initialize all of the private data
    isFilled = false;
    isSorted = false;
    numCores = numCores_a;
    size_ = 0;
    exec_time_ms = 0;
    data = nullptr;

    // Fill the data
    FillData(size, min, max);
}

// Destructor
StdParallelQuickSort::~StdParallelQuickSort() {
    // Free any leftover data
    if (data != nullptr) {
        delete data;
    }
}

// Main function. Do the sorting
void StdParallelQuickSort::Sort() {
    // Start the timer
    auto t1 = std::chrono::high_resolution_clock::now();

    // Spawn the threads
    for (int i = 0; i < numCores; i++) {
        threads.push_back(std::thread(&StdParallelQuickSort::QuickSortThreadHelper, this, i));
    }

    // Join the threads
    for (int i = 0; i < numCores; i++) {
        threads.at(i).join();
    }

    // Merge the final halves
    FinalMerge(numCores, 1);

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
bool StdParallelQuickSort::VerifySort() {
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
void StdParallelQuickSort::Print() {
    // Make sure data exists
    if (!isFilled) {
        std::cout << "Cannot print an empty dataset" << std::endl;
        return;
    }

    std::cout << "Begin Data for Parallel Quick Sort" << std::endl;
    // Loop through and print the data
    for (int i = 0; i < size_; i++) {
        std::cout << data[i] << std::endl;
    }
    std::cout << "End Data for Parallel Quick Sort" << std::endl;
}

// Report timing
void StdParallelQuickSort::ReportTiming() {
    std::cout << "The most recent run used parallel Quick sort to sort " <<
        size_ << " values in " << exec_time_ms / 1000 << " seconds" << 
        " using " << numCores << " cores." << std::endl;
}

// Fill the data. If the filename is specified, ingest the data from a file
void StdParallelQuickSort::FillData(int size, int min, int max) {
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
void StdParallelQuickSort::ClearData() {
    delete data;
    data = nullptr;
    size_ = 0;
    isFilled = false;
    isSorted = false;
}

void StdParallelQuickSort::SetNumCores(int numCores_a) { numCores = numCores_a; }

// Getters
bool StdParallelQuickSort::IsSorted() { return isSorted; }
bool StdParallelQuickSort::IsFilled() { return isFilled; }
int StdParallelQuickSort::Size() { return size_; }
int StdParallelQuickSort::NumCores() { return numCores; }

void StdParallelQuickSort::MergeHalves(int start, int middle, int end) {
    int half_one_size = middle - start + 1;
    int half_two_size = end - middle;

    int *temp1 = new int[half_one_size];
    int *temp2 = new int[half_two_size];

    for (int i = 0; i < half_one_size; i++)
        temp1[i] = data[start + i];
    for (int j = 0; j < half_two_size; j++)
        temp2[j] = data[middle + 1 + j];

    // indexing
    int a, b, c;
    a = 0;
    b = 0;
    c = start;

    while (a < half_one_size && b < half_two_size) {
        if (temp1[a] <= temp2[b]) {
            data[c] = temp1[a];
            a++;
        } else {
            data[c] = temp2[b];
            b++;
        }
        c++;
    }

    while (a < half_one_size) {
        data[c] = temp1[a];
        a++;
        c++;
    }

    while (b < half_two_size) {
        data[c] = temp2[b];
        b++;
        c++;
    }

    // Free memory
    delete temp1;
    delete temp2;
}

void StdParallelQuickSort::QuickSortThreadHelper(int tid) {
    int low = tid * (size_ / numCores);
    int high = (tid + 1) * (size_ / numCores) - 1;

    // Double check boundaries on the last tid
    if (tid == (numCores - 1)) {
        while (high < (size_ - 1)) {
            high++;
        }
        while (high > (size_ - 1)) {
            high--;
        }
    }
    QuickSortHelper(low, high);
}

void StdParallelQuickSort::FinalMerge(int thread_factor, int aggregation_factor) {
    int numbers_per_thread = size_ / numCores;
    for (int i = 0; i < thread_factor; i += 2) {
        int left = i * (numbers_per_thread * aggregation_factor);
        int right = ((i + 2) * numbers_per_thread * aggregation_factor) - 1;
        int middle = left + (numbers_per_thread * aggregation_factor) - 1;
        if (right >= size_)
            right = size_ - 1;
        if (thread_factor > 2) {
            threads.at(i) = std::thread(&StdParallelQuickSort::MergeHalves, this, left, middle, right);
        } else {
            MergeHalves(left, middle, right);
        }
        
    }

    // Join the threads
    for (int i = 0; i < numCores; i++) {
        if (threads.at(i).joinable())
            threads.at(i).join();
    }
    if ((thread_factor / 2) >= 1) {
        FinalMerge(thread_factor / 2, aggregation_factor * 2);
    }
}

void StdParallelQuickSort::Swap(int indexA, int indexB) {
    int temp = data[indexA];
    data[indexA] = data[indexB];
    data[indexB] = temp;
}

int StdParallelQuickSort::Partition(int low, int high) {
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

void StdParallelQuickSort::QuickSortHelper(int low, int high) {
    if (low < high) {
        int pivot = Partition(low, high);
        QuickSortHelper(low, pivot - 1);
        QuickSortHelper(pivot + 1, high);
    }
}