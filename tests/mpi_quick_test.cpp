#include <iostream>
#include <mpi.h>

#include <chrono>
#include <iostream>
#include <random>

// Change this to alter the array size
#define GLOBAL_SIZE 50
#define MIN 0
#define MAX 99
#define PRINT_FLAG true

// Function declarations
bool VerifySort(int *data, int size);
void Print(int *data, int size);
void ReportTiming(int size, int numCores, double exec_time_ms);
void FillData(int size, int min, int max, int *data);
void MergeHalves(int *data, int start, int middle, int end);
void QuickSortHelper(int *data, int low, int high);
int Partition(int *data, int low, int high);
void Swap(int *data, int indexA, int indexB);
void FinalMerge(int *data, int core_factor, int aggregation_factor, int size, int numCores);


int main (int argc, char *argv[]) {
    int numprocs, rank;

   MPI_Init(&argc,&argv); // Initalize MPI environment
   MPI_Comm_size(MPI_COMM_WORLD,&numprocs); //get total number of processes
   MPI_Comm_rank(MPI_COMM_WORLD,&rank); // get process identity number
   
   // Establish the global array that will be sorted
   int *global_data = new int[GLOBAL_SIZE];
   int *local_data = new int[GLOBAL_SIZE/numprocs + 1];
   FillData(GLOBAL_SIZE, MIN, MAX, global_data);

   // Establish the arrays local to each process
    int *sendcounts = new int[numprocs];
    int *displs = new int[numprocs];
    int current_spot = 0;
    int num_local_elements = GLOBAL_SIZE / numprocs;
    int remainders = GLOBAL_SIZE % numprocs;
    for (int i = 0; i < numprocs; i++) {
        sendcounts[i] = num_local_elements;
        displs[i] = current_spot;
        current_spot += num_local_elements;
        if (i == numprocs - 1) {
            sendcounts[i] = sendcounts[i] + remainders;
            current_spot = current_spot + remainders;
        }
    }

    if (rank == numprocs - 1)
        num_local_elements += remainders;

    // Scatter the global array off to each process
    MPI_Scatterv(global_data, sendcounts, displs, MPI_INT, local_data, num_local_elements, MPI_INT, 0, MPI_COMM_WORLD);

    // Perform the quick sorts
    std::chrono::high_resolution_clock::time_point t1;
    if (rank == 0) {
        // Start the timer
        t1 = std::chrono::high_resolution_clock::now();

        // Local quick sort
        QuickSortHelper(local_data, 0, num_local_elements - 1);
    } else {
        // Local quick sort
        QuickSortHelper(local_data, 0, num_local_elements - 1);
    }

    // Gather the results
    MPI_Gatherv(local_data, num_local_elements, MPI_INT, global_data, sendcounts, displs, MPI_INT, 0, MPI_COMM_WORLD);

    // Perform the final merge and timing
    double exec_time_ms;
    if (rank == 0) {
        FinalMerge(global_data, numprocs, 1, GLOBAL_SIZE, numprocs);
        auto t2 = std::chrono::high_resolution_clock::now();
        std::chrono::duration<double, std::milli> ms_double = t2 - t1;
        exec_time_ms = ms_double.count();

        if (PRINT_FLAG)
            Print(global_data, GLOBAL_SIZE);
        
        // Validate the sort and report timing
        if (VerifySort(global_data, GLOBAL_SIZE)) {
            std::cout << "Correctly sorted!" << std::endl;
        } else {
            std::cout << "Incorrectly sorted!" << std::endl;
        }

        ReportTiming(GLOBAL_SIZE, numprocs, exec_time_ms);
    }

    // Free memory
    delete global_data;
    delete local_data;
    delete sendcounts;
    delete displs;

    return 0;
}


// Function definitions
// Verifies that the underlying data is sorted
bool VerifySort(int *data, int size) {
    // Make sure data exists
    if (data == NULL) {
        std::cout << "Cannot verify an empty dataset" << std::endl;
        return false;
    }
    // Iterate through the vector and make sure that
    // ascending order is true
    for (int i = 0; i < size - 1; i++) {
        if (data[i] > data[i+1]) {
            return false;
        }
    }

    // If here, then the sort was successful
    return true;
}

// Prints the data
void Print(int *data, int size) {
    // Make sure data exists
    if (data == NULL) {
        std::cout << "Cannot print an empty dataset" << std::endl;
        return;
    }

    std::cout << "Begin Data for MPI Quick Sort" << std::endl;
    // Loop through and print the data
    for (int i = 0; i < size; i++) {
        std::cout << data[i] << std::endl;
    }
    std::cout << "End Data for MPI Quick Sort" << std::endl;
}

// Report timing
void ReportTiming(int size, int numCores, double exec_time_ms) {
    std::cout << "The most recent run used parallel MPI Quick sort to sort " <<
        size << " values in " << exec_time_ms / 1000 << " seconds" << 
        " using " << numCores << " cores." << std::endl;
}

// Fill the data
void FillData(int size, int min, int max, int *data) {
    // Use C++ libraries to generate random values
    std::random_device rd;
    std::mt19937 rng(rd());
    std::uniform_int_distribution<int> uni(min, max);

    // Fill the data
    for (int i = 0; i < size; i++) {
        data[i] = uni(rng);
    }
}

void MergeHalves(int *data, int start, int middle, int end) {
    int half_one_size = middle - start + 1;
    int half_two_size = end - middle;

    int *temp1 = new int[half_one_size];
    int *temp2 = new int[half_two_size];

    for (int i = 0; i < half_one_size; i++)
        temp1[i] = data[start + i];
    for (int j = 0; j < half_two_size; j++)
        temp2[j] = data[middle + 1 + j];

    // indexing
    int a, b, c;
    a = 0;
    b = 0;
    c = start;

    while (a < half_one_size && b < half_two_size) {
        if (temp1[a] <= temp2[b]) {
            data[c] = temp1[a];
            a++;
        } else {
            data[c] = temp2[b];
            b++;
        }
        c++;
    }

    while (a < half_one_size) {
        data[c] = temp1[a];
        a++;
        c++;
    }

    while (b < half_two_size) {
        data[c] = temp2[b];
        b++;
        c++;
    }

    // Free memory
    delete temp1;
    delete temp2;
}

void FinalMerge(int *data, int core_factor, int aggregation_factor, int size, int numCores) {
    int numbers_per_core = size / numCores;
    for (int i = 0; i < core_factor; i += 2) {
        int left = i * (numbers_per_core * aggregation_factor);
        int right = ((i + 2) * numbers_per_core * aggregation_factor) - 1;
        int middle = left + (numbers_per_core * aggregation_factor) - 1;

        if (right >= size)
            right = size - 1;
        
        MergeHalves(data, left, middle, right);      
    }

    if ((core_factor / 2) >= 1) {
        FinalMerge(data, core_factor / 2, aggregation_factor * 2, size, numCores);
    }
}

void Swap(int *data, int indexA, int indexB) {
    int temp = data[indexA];
    data[indexA] = data[indexB];
    data[indexB] = temp;
}

int Partition(int *data, int low, int high) {
    int pivot = data[high];

    int i = (low - 1);

    for (int j = low; j < high; j++) {
        if (data[j] <= pivot) {
            i++;
            Swap(data, i, j);
        }
    }
    Swap(data, i+1, high);

    return (i + 1);
}

void QuickSortHelper(int *data, int low, int high) {
    if (low < high) {
        int pivot = Partition(data, low, high);
        QuickSortHelper(data, low, pivot - 1);
        QuickSortHelper(data, pivot + 1, high);
    }
}

