//#include "serial_merge_sort.h"
#include "serial_quick_sort.h"
// #include "std_parallel_merge_sort.h"
// #include "std_parallel_quick_sort.h"
#include <iostream>


int main() {
    SerialQuickSort mySorter;

     //mySorter.FillData(500000007, 0, 9999);
    mySorter.FillData(500000, 0, 99);
    //mySorter.SetNumCores(8);

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