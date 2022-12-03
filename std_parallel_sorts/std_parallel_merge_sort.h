// Local Includes
#include "../sorter_base.h"

// Standard Library Includes
#include <thread>
#include <vector>

class StdParallelMergeSort : public SorterBase {
public:
    // Constructor and Destructor
    StdParallelMergeSort();
    StdParallelMergeSort(int size, int min, int max, int numCores_a);
    ~StdParallelMergeSort();

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
    void SetNumCores(int numCores_a);

    // Basic API calls for revealing data 
    // about the underlying object
    bool IsSorted() override;
    int Size() override;
    bool IsFilled() override;
    int NumCores();

protected:
    // Helper methods used in computations
    double ComputeEfficiency() override;
    double ComputeSpeedup() override;

private:
    // Helper function to merge two halves
    void MergeHalves(int start, int middle, int end);

    // Helper function to include start/end arguments
    void MergeSortHelper(int start, int end);

    void MergeSortThreadHelper(int tid);

    void FinalMerge(int thread_factor, int aggregation_factor);
    
    // Underlying data
    int *data;

    // Execution time
    double exec_time_ms;

    // Threads to split the sorting with
    std::vector<std::thread> threads;
};