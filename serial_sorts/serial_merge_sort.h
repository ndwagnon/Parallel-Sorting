// Local Includes
#include "../sorter_base.h"

class SerialMergeSort : public SorterBase {
public:
    // Constructor and Destructor
    SerialMergeSort();
    SerialMergeSort(int size, int min, int max);
    ~SerialMergeSort();

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
    // Helper function to merge two halves
    void MergeHalves(int start, int middle, int end);

    // Helper function to include start/end arguments
    void MergeSortHelper(int start, int end);
    
    // Underlying data
    int *data;

    // Execution time
    double exec_time_ms;
};