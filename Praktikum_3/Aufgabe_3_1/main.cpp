#include <iostream>
#include <fstream>
#include <iomanip>
#include <functional>
#include <omp.h>
#include <algorithm>
#include "MyAlgorithms.h"
using namespace std;
using namespace MyAlgorithms;

void measure(const string& filename, function<void(vector<int>& vector)> func)
{
    ofstream file;
    file.open(filename);

    double dtime, start, diff;
    double maxMeasuringTime = 600.0;

    int n_start = 1000;
    int n_step = 1000;
    int n_end = 1000000;

    vector<int> copy;

    start = omp_get_wtime();

    for (int n = n_start; n <= n_end; n += n_step)
    {
        double percent = (100.0 / n_end) * n;
        cout << "\r" << "Step: [" << n << "/" << n_end << "] " << fixed << std::setprecision(2) << percent << "% ";

        // Generate random vector with n elements
        vector<int> random;
        MyAlgorithms::RandomVectorGenerator(random, n);
        copy = random;

        // Measuring
        dtime = omp_get_wtime();
        func(copy);
        dtime = omp_get_wtime() - dtime;

        file << n << "\t" << scientific << setprecision(10) << dtime << endl;

        diff = omp_get_wtime() - start;
        if (diff > maxMeasuringTime)
        {
            cout << "--> Messung laenger als " << maxMeasuringTime << " Sekunden";
            break;
        }
    }

    cout << endl;
    file.close();
}

void measureMatrix(const string& filename, function<void(vector<double> &a, vector<double> &b, vector<double> &c, int n)> func)
{
    ofstream file;
    file.open(filename);

    double dtime, start, diff;
    double maxMeasuringTime = 600.0;

    int n_start = 2;
    int n_end = 800;

    vector<int> copy;

    start = omp_get_wtime();

    for (int n = 2; n <= n_end; ++n)
    {
        double percent = (100.0 / n_end) * n;
        cout << "\r" << "Step: [" << n << "/" << n_end << "] " << fixed << std::setprecision(2) << percent << "% ";

        // Generate random vector with n elements
        vector<double> a, b, result(n * n);
        MyAlgorithms::RandomVectorGenerator(a, n * n);
        MyAlgorithms::RandomVectorGenerator(b, n * n);

        // Measuring
        dtime = omp_get_wtime();
        func(a, b, result, n);
        dtime = omp_get_wtime() - dtime;

        file << n << "\t" << scientific << setprecision(10) << dtime << endl;

        diff = omp_get_wtime() - start;
        if (diff > maxMeasuringTime)
        {
            cout << "--> Messung laenger als " << maxMeasuringTime << " Sekunden";
            break;
        }
    }

    cout << endl;
    file.close();
}

void matrixTest()
{
    vector<double> a = { 1, 3, 2, 4 };
    vector<double> b = { 5, 7, 6, 8 };
    vector<double> c(4);

    cout << "spaltenweise" << endl;

    cout << "****** A ******" << endl;
    cout << a << endl;

    cout << "****** B ******" << endl;
    cout << b << endl;

    MatrixMul_ColMajor(a, b, c, 2);

    cout << "****** C ******" << endl;
    cout << c << endl;

    a = { 1, 2, 3, 4 };
    b = { 5, 6, 7, 8 };

    cout << "zeilenweise" << endl;

    cout << "****** A ******" << endl;
    cout << a << endl;

    cout << "****** B ******" << endl;
    cout << b << endl;

    MatrixMul_RowMajor(a, b, c, 2);

    cout << "****** C ******" << endl;
    cout << c << endl;
}

int main()
{
    matrixTest();

    QUESTION("Messe Matrixmultiplikation ColMajor", {
        measureMatrix("matrixcolmajor.txt", &MatrixMul_ColMajor);
    });
    QUESTION("Messe Matrixmultiplikation RowMajor", {
        measureMatrix("matrixrowmajor.txt", &MatrixMul_RowMajor);
    });

    QUESTION("Messe Matrixmultiplikation ColMajor Parallel", {
        measureMatrix("matrixcolmajorth.txt", &MatrixMul_ColMajorThreaded);
    });
    QUESTION("Messe Matrixmultiplikation RowMajor Parallel", {
        measureMatrix("matrixrowmajorth.txt", &MatrixMul_RowMajorThreaded);
    });

    
    QUESTION("Messe Mergesort", {
        measure("mergesort.txt", [](vector<int>& data)
        {
            vector<int> tmp = data;
            MyAlgorithms::MergeSort(data, tmp, 0, int(data.size() - 1));
        });
    });

    QUESTION("Messe Quicksort Alt, lange Laufzeit!", {
        measure("quicksortold.txt", [](vector<int>& data)
        {
            MyAlgorithms::QuickSort(data, 0, int(data.size() - 1));
        });
    });

    QUESTION("Messe Quicksort", {
        measure("quicksort.txt", [](vector<int>& data)
        {
            //std::sort(data.begin(), data.end());
            MyAlgorithms::QuickSort(data, 0, data.size() - 1);
        });
    });

    QUESTION("Messe Shellsort", {
        measure("shellsort.txt", [](vector<int>& data)
        {
            MyAlgorithms::ShellSort(data);
        });
    });

    QUESTION("Messe Heapsort", {
        measure("heapsort.txt", [](vector<int>& data)
        {
            MyAlgorithms::HeapSort(data);
        });
    });

    cout << "Beliebige Taste druecken zum Beenden..." << endl;
    cin.get();
    return 0;
}
