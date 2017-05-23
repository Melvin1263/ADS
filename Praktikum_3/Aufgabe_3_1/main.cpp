#include <iostream>
#include <fstream>
#include <iomanip>
#include <functional>
#include <omp.h>
#include <algorithm>
#include <map>
#include "MyAlgorithms.h"
using namespace MyAlgorithms;

std::map<int, std::vector<int>*> rvectormap;

void measure(const std::string& filename, std::function<void(std::vector<int>& vector)> func)
{
    std::ofstream file;
    file.open(filename);

    double dtime, start, diff;
    double maxMeasuringTime = 600.0;

    int n_start = 1000;
    int n_step = 1000;
    int n_end = 1000000;

    std::vector<int> copy;

    start = omp_get_wtime();

    for (int n = n_start; n <= n_end; n += n_step)
    {
        double percent = (100.0 / n_end) * n;
        std::cout << "\r" << "Step: [" << n << "/" << n_end << "] " << std::fixed << std::setprecision(2) << percent << "% ";

        // Generate random vector with n elements
        std::map<int, std::vector<int>*>::iterator it = rvectormap.find(n);
        std::vector<int> random;
        if (it != rvectormap.end())
        {
            random = *it->second;
        }
        else
        {
            std::vector<int>* ptrv = new std::vector<int>();
            RandomVectorGenerator(ptrv, n);
            rvectormap.insert(std::make_pair(n, ptrv));
        }

        copy = random;

        // Measuring
        dtime = omp_get_wtime();
        func(copy);
        dtime = omp_get_wtime() - dtime;

        file << n << "\t" << std::scientific << std::setprecision(10) << dtime << std::endl;

        diff = omp_get_wtime() - start;
        if (diff > maxMeasuringTime)
        {
            std::cout << "--> Messung laenger als " << maxMeasuringTime << " Sekunden";
            break;
        }
    }

    std::cout << std::endl;
    file.close();
}

void measureMatrix(const std::string& filename, std::function<void(std::vector<double> &a, std::vector<double> &b, std::vector<double> &c, int n)> func)
{
    std::ofstream file;
    file.open(filename);

    double dtime, start, diff;
    double maxMeasuringTime = 600.0;

    int n_start = 2;
    int n_end = 800;

    std::vector<int> copy;

    start = omp_get_wtime();

    for (int n = 2; n <= n_end; ++n)
    {
        double percent = (100.0 / n_end) * n;
        std::cout << "\r" << "Step: [" << n << "/" << n_end << "] " << std::fixed << std::setprecision(2) << percent << "% ";

        // Generate random vector with n elements
        std::vector<double> a, b, result(n * n);
        RandomVectorGenerator(a, n * n);
        RandomVectorGenerator(b, n * n);

        // Measuring
        dtime = omp_get_wtime();
        func(a, b, result, n);
        dtime = omp_get_wtime() - dtime;

        file << n << "\t" << std::scientific << std::setprecision(10) << dtime << std::endl;

        diff = omp_get_wtime() - start;
        if (diff > maxMeasuringTime)
        {
            std::cout << "--> Messung laenger als " << maxMeasuringTime << " Sekunden";
            break;
        }
    }

    std::cout << std::endl;
    file.close();
}

void sortTest()
{
    std::vector<int> myList = { 98, 44, 30, 22, 64, 63, 11, 23, 8, 18 };
    std::vector<int> copy(myList.size(), 0);

    std::cout << "Liste: " << VectorToString(myList) << std::endl;

    copy = myList;
    QuickSort(copy, 0, (int)myList.size() - 1);
    std::cout << "Quicksort: " << VectorToString(copy) << std::endl << std::endl;

    copy = myList;
    HeapSort(copy);
    std::cout << "Heapsort: " << VectorToString(copy) << std::endl << std::endl;

    copy = myList;
    ShellSort(copy);
    std::cout << "Shellsort: " << VectorToString(copy) << std::endl << std::endl;

    copy = myList;
    std::vector<int> tmp = copy;
    MergeSort(copy, tmp, 0, (int)copy.size() - 1);
    std::cout << "Mergesort: " << VectorToString(copy) << std::endl << std::endl;
}

void matrixTest()
{
    std::vector<double> a = { 1, 3, 2, 4 };
    std::vector<double> b = { 5, 7, 6, 8 };
    std::vector<double> c(4);

    std::cout << "spaltenweise" << std::endl;

    std::cout << "****** A ******" << std::endl;
    std::cout << a << std::endl;

    std::cout << "****** B ******" << std::endl;
    std::cout << b << std::endl;

    MatrixMul_ColMajor(a, b, c, 2);

    std::cout << "****** C ******" << std::endl;
    std::cout << c << std::endl;

    a = { 1, 2, 3, 4 };
    b = { 5, 6, 7, 8 };

    std::cout << "zeilenweise" << std::endl;

    std::cout << "****** A ******" << std::endl;
    std::cout << a << std::endl;

    std::cout << "****** B ******" << std::endl;
    std::cout << b << std::endl;

    MatrixMul_RowMajor(a, b, c, 2);

    std::cout << "****** C ******" << std::endl;
    std::cout << c << std::endl;
}

int main()
{
    MeasureManager manager = MeasureManager::getInstance();
    manager.addAlgorithm("mergesort", 
        [](std::vector<int>& data)
        {
            std::vector<int> tmp = data;
            MyAlgorithms::MergeSort(data, tmp, 0, int(data.size() - 1));
        }
    );
    manager.addAlgorithm("quicksort",
        [](std::vector<int>& data)
        {
            MyAlgorithms::QuickSort(data, 0, (int)data.size() - 1);
        }
    );

    //manager.doMeasure();

    
    matrixTest();
    sortTest();

#ifndef _DEBUG
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
        measure("mergesort.txt", [](std::vector<int>& data)
        {
            std::vector<int> tmp = data;
            MyAlgorithms::MergeSort(data, tmp, 0, int(data.size() - 1));
        });
    });

    QUESTION("Messe Quicksort Alt, lange Laufzeit!", {
        measure("quicksortold.txt", [](std::vector<int>& data)
        {
            MyAlgorithms::QuickSortOld(data, 0, int(data.size() - 1));
        });
    });

    QUESTION("Messe Quicksort", {
        measure("quicksort.txt", [](std::vector<int>& data)
        {
            //std::sort(data.begin(), data.end());
            MyAlgorithms::QuickSort(data, 0, (int)data.size() - 1);
        });
    });

    QUESTION("Messe Shellsort", {
        measure("shellsort.txt", [](std::vector<int>& data)
        {
            MyAlgorithms::ShellSort(data);
        });
    });

    QUESTION("Messe Heapsort", {
        measure("heapsort.txt", [](std::vector<int>& data)
        {
            MyAlgorithms::HeapSort(data);
        });
    });

    QUESTION("Messe stdsort", {
        measure("stdsort.txt", [](std::vector<int>& data)
        {
            std::sort(data.begin(), data.end());
        });
    });
#endif

    std::cout << "Beliebige Taste druecken zum Beenden..." << std::endl;
    std::cin.get();
    return 0;
}
