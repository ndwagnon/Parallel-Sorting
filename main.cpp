//#include "serial_merge_sort.h"
// #include "serial_merge_sort.h"
#include "std_parallel_merge_sort.h"
#include <iostream>


int main() {
    StdParallelMergeSort mySorter;

     mySorter.FillData(500000007, 0, 9999);
    //mySorter.FillData(50, 0, 99);
    mySorter.SetNumCores(8);

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

    //mySorter.Print();

    mySorter.ReportTiming();
    return 0;
}