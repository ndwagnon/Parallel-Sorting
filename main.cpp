#include "serial_insertion_sort.h"

#include <iostream>


int main() {
    SerialInsertionSort mySorter;

    mySorter.FillData(50000, 0, 9999);

    if (mySorter.VerifySort()) {
        std::cout << "Sorted!" << std::endl;
    } else {
        std::cout << "Not Sorted!" << std::endl;
    }

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