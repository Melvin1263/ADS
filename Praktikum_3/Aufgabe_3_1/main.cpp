#include <iostream>
#include <fstream>
#include <iomanip>
#include <functional>
#include <omp.h>
#include "MyAlgorithms.h"
using namespace std;
using namespace MyAlgorithms;

void measure(const string& filename, function<void(vector<int>& vector)> func)
{
    ofstream file;
    file.open(filename);

    double dtime, start, diff;
	double maxMeasuringTime = 180.0;

    int n_start = 1000;
    int n_step = 1000;
    int n_end = 1000000;

    vector<int> copy;

	start = omp_get_wtime();

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

		diff = omp_get_wtime() - start;
		if (diff > maxMeasuringTime)
		{
			cout << "Messung laenger als " << maxMeasuringTime << endl;
			break;
		}
    }

    file.close();
}

void matrix()
{
	cout << "spaltenweise" << endl;
	vector<double> a = {1, 3, 2, 4};
	vector<double> b = {5, 7, 6, 8};
	vector<double> c(4);

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
	matrix();

    measure("mergesort.txt", [](vector<int>& data)
    {
        vector<int> tmp = data;
        MyAlgorithms::MergeSort(data, tmp, 0, int(data.size() - 1));
    });

    measure("quicksort.txt", [](vector<int>& data)
    {
        MyAlgorithms::QuickSort(data, 0, int(data.size() - 1));
    });

	measure("shellsort.txt", [](vector<int>& data)
	{
		MyAlgorithms::ShellSort(data);
	});

	measure("heapsort.txt", [](vector<int>& data)
	{
		MyAlgorithms::HeapSort(data, 0);
	});


    cin.get();
    return 0;
}
