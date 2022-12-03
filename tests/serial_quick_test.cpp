#include "../serial_sorts/serial_quick_sort.h"


#include <iostream>


int main() {
    SerialQuickSort mySorter;

    mySorter.FillData(50, 0, 99);

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