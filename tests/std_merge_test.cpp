#include "../std_parallel_sorts/std_parallel_merge_sort.h"


#include <iostream>


int main() {
    StdParallelMergeSort mySorter;

    mySorter.FillData(50000000, 0, 99);
    mySorter.SetNumCores(1);

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
    return 0;
}