#include <string>

// Base class designed to be subclassed
// by various sorting methods
class SorterBase
{

public:
    // Constructor and Destructor
    SorterBase();
    SorterBase(int size);
    SorterBase(int size, std::string filename);
    ~SorterBase();

    // Basic API calls for testing and reporting
    // results
    virtual void Sort() = 0;
    virtual bool VerifySort() = 0;
    virtual void Print() = 0;
    virtual void ReportTiming() = 0;
    virtual void ReportEfficiency() = 0;
    virtual void ReportSpeedup() = 0;
    virtual void FillData(int size, std::string fileName = "") = 0;
    virtual void ClearData() = 0;

    // Basic API calls for revealing data 
    // about the underlying object
    virtual bool IsSorted() = 0;
    virtual bool IsTimed() = 0;
    virtual int Size() = 0;
    virtual bool IsFilled() = 0;
    virtual bool IsDataRandom() = 0;

protected:
    // Helper methods used in computations
    virtual double ComputeEfficiency() = 0;
    virtual double ComputeSpeedup() = 0;

    // Underlying object data
    // Accessible via getters
    bool isFilled;
    bool isSorted;
    bool isTimed;
    bool isDataRandom;
    int numCores;
    int size_;
};
