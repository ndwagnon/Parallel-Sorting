// Local Includes
#include "sorter_base.h"

// Standard Includes
#include <vector>

class SerialInsertionSort : public SorterBase {
public:
    // Constructor and Destructor
    SerialInsertionSort();
    SerialInsertionSort(int size);
    SerialInsertionSort(int size, std::string filename);
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

    // Basic API calls for revealing data 
    // about the underlying object
    bool IsSorted() override;
    bool IsTimed() override;
    int Size() override;
    bool IsFilled() override;
    bool IsDataRandom() override;

protected:
    // Helper methods used in computations
    double ComputeEfficiency() override;
    double ComputeSpeedup() override;

private:
    // Underlying data
    std::vector<int> data;
};