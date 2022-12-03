// Local Includes
#include "../sorter_base.h"

class SerialQuickSort : public SorterBase {
public:
    // Constructor and Destructor
    SerialQuickSort();
    SerialQuickSort(int size, int min, int max);
    ~SerialQuickSort();

    // Basic API calls for testing and reporting
    // results
    void Sort() override;
    bool VerifySort() override;
    void Print() override;
    void ReportTiming() override;
    void ReportEfficiency() override;
    void ReportSpeedup() override;
    void FillData(int size, int min, int max) override;
    void ClearData() override;

    // Basic API calls for revealing data 
    // about the underlying object
    bool IsSorted() override;
    int Size() override;
    bool IsFilled() override;

protected:
    // Helper methods used in computations
    double ComputeEfficiency() override;
    double ComputeSpeedup() override;

private:
    // Helper functions
    void Swap(int indexA, int indexB);
    int Partition(int low, int high);
    void QuickSortHelper(int low, int high);
    // Underlying data
    int *data;

    // Execution time
    double exec_time_ms;
};