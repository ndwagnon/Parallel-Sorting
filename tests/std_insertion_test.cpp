#include "../std_parallel_sorts/std_parallel_insertion_sort.h"


#include <iostream>


int main() {
    StdParallelInsertionSort mySorter;

    mySorter.FillData(50, 0, 99);
    mySorter.SetNumCores(4);

    if (mySorter.VerifySort()) {
        std::cout << "Sorted!" << std::endl;
    } else {
        std::cout << "Not Sorted!" << std::endl;
    }

    //mySorter.Print();

    std::cout << std::endl;
    mySorter.Sort();
    //mySorter.Print();

    if (mySorter.VerifySort()) {
        std::cout << "Sorted!" << std::endl;
    } else {
        std::cout << "Not Sorted!" << std::endl;
    }

    mySorter.ReportTiming();
    mySorter.ReportEfficiency();
    mySorter.ReportSpeedup();
    return 0;
}