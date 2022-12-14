#include <string>

// Base class designed to be subclassed
// by various sorting methods
class SorterBase
{

public:
    // Basic API calls for testing and reporting
    // results
    virtual void Sort() = 0;
    virtual bool VerifySort() = 0;
    virtual void Print() = 0;
    virtual void ReportTiming() = 0;
    virtual void FillData(int size, int min, int max) = 0;
    virtual void ClearData() = 0;

    // Basic API calls for revealing data 
    // about the underlying object
    virtual bool IsSorted() = 0;
    virtual int Size() = 0;
    virtual bool IsFilled() = 0;

protected:
    // Underlying object data
    // Accessible via getters
    bool isFilled;
    bool isSorted;
    int numCores;
    int size_;
};
