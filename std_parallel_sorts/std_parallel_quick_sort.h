// Local Includes
#include "../sorter_base.h"

#include <thread>
#include <vector>

class StdParallelQuickSort : public SorterBase {
public:
    // Constructor and Destructor
    StdParallelQuickSort();
    StdParallelQuickSort(int size, int min, int max, int numCores_a);
    ~StdParallelQuickSort();

    // Basic API calls for testing and reporting
    // results
    void Sort() override;
    bool VerifySort() override;
    void Print() override;
    void ReportTiming() override;
    void FillData(int size, int min, int max) override;
    void ClearData() override;
    void SetNumCores(int numCores_a);

    // Basic API calls for revealing data 
    // about the underlying object
    bool IsSorted() override;
    int Size() override;
    bool IsFilled() override;
    int NumCores();
    
private:
    // Helper functions
    void Swap(int indexA, int indexB);
    int Partition(int low, int high);
    void QuickSortHelper(int low, int high);
    void QuickSortThreadHelper(int tid);
    void FinalMerge(int thread_factor, int aggregation_factor);
    void MergeHalves(int start, int middle, int end);

    // Underlying data
    int *data;

    // Execution time
    double exec_time_ms;

    // Threads to split the sorting with
    std::vector<std::thread> threads;
};