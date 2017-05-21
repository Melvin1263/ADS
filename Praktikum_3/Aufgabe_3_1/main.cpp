#include <iostream>
#include <fstream>
#include <iomanip>
#include <functional>
#include <omp.h>
#include "MyAlgorithms.h"
using namespace std;

void measure(const string& filename, function<void(vector<int>& vector)> func)
{
    ofstream file;
    file.open(filename);

    double dtime;

    int n_start = 100;
    int n_step = 1000;
    int n_end = 1000000;

    vector<int> copy;

    for (int n = n_start; n < n_end; n += n_step)
    {
        cout << "n: " << n << endl;

        // Generate random vector with n elements
        vector<int> random;
        MyAlgorithms::RandomVectorGenerator(random, n);
        copy = random;

        // Measuring
        dtime = omp_get_wtime();
        func(copy);
        dtime = omp_get_wtime() - dtime;

        file << n << "\t" << scientific << setprecision(10) << dtime << endl;
    }

    file.close();
}

int main()
{
    measure("mergesort.txt", [](vector<int>& data)
    {
        vector<int> tmp = data;
        MyAlgorithms::MergeSort(data, tmp, 0, int(data.size() - 1));
    });

    measure("quicksort.txt", [](vector<int>& data)
    {
        vector<int> tmp = data;
        MyAlgorithms::QuickSort(data, 0, int(data.size() - 1));
    });

    cin.get();
    return 0;
}
