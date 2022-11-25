// Local Includes
#include "sorter_base.h"

// Standard Includes
#include <vector>

class SerialInsertionSort : public SorterBase {
    // Constructor and Destructor
    SerialInsertionSort();
    ~SerialInsertionSort();

    // Basic API calls for testing and reporting
    // results
    void Sort() override;
    bool VerifySort() override;
    void Print() override;
    void ReportTiming() override;
    void ReportEfficiency() override;
    void ReportSpeedup() override;
    void FillData(int size, std::string fileName = "") override;
    void ClearData() override;
};