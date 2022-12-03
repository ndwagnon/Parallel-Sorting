// Local Includes
#include "../sorter_base.h"

// Standard library includes
#include <thread>
#include <vector>

class StdParallelInsertionSort : public SorterBase {
public:
    // Constructor and Destructor
    StdParallelInsertionSort();
    StdParallelInsertionSort(int size, int min, int max, int numCores_a);
    ~StdParallelInsertionSort();

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
    // Helper functionss
    void InsertionSortThreadHelper(int tid);
    void FinalMerge(int thread_factor, int aggregation_factor);
    void MergeHalves(int start, int middle, int end);
    void InsertionSortHelper(int low, int high);

    // Underlying data
    int *data;

    // Execution time
    double exec_time_ms;

    // Threads to split the sorting with
    std::vector<std::thread> threads;
};