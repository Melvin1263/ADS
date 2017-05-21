#ifndef _MYALGORITHMS_H_
#define _MYALGORITHMS_H_

#include <vector>
#include <iostream>
#include <string>
#include <sstream>
using namespace std;

#ifdef _DEBUG
#define DEBUG(str) { cout << str; }
#else
#define DEBUG(str)
#endif

namespace MyAlgorithms
{
	template<typename T>
	std::ostream& operator<< (std::ostream& os, std::vector<T>& vec);

    // Dreieckstausch
    template <typename T>
    inline void Swap(T& lft, T& rht)
    {
        T tmp = lft;
        lft = rht;
        rht = tmp;
    }

    // Vektor Ausgeben
    template <typename T>
    string VectorToString(vector<T>& values)
    {
        stringstream result;

        for (vector<T>::const_iterator it = values.begin(); it != values.end(); ++it)
        {
            result << *it;
            result << ' ';
        }
        return result.str();
    }

	// Heapsort
    size_t LeftChild(size_t i);
	void max_heapify(vector<int> &a, int i, int n);
	void HeapSort(vector<int> &a, int n);

	// MergeSort
	void Merge(vector<int> &a, vector<int> &b, int low, int pivot, int high);
	void MergeSort(vector<int> &a, vector<int> &b, int low, int high);

	// Quicksort
    // Median von 3 Werten berechnen
    int Median3(vector<int> a, int left, int right);
	void QuickSort(vector<int> &arr, int left, int right);

	// Shellsort
    void ShellSort(vector<int> &values);

	// Matrix Multiplikation
	void MatrixMul_ColMajor(vector<double> &a, vector<double> &b, vector<double> &c, int n);
	void MatrixMul_RowMajor(vector<double> &a, vector<double> &b, vector<double> &c, int n);

    template <typename T>
    void RandomVectorGenerator(vector<T>&vector, int n)
    {
        vector.resize(n);

        for (int i = 0; i < n; i++)
        {
            vector[i] = i + 1;
        }

        for (int i = 0; i < n; i++)
        {
            int num1 = rand();
            num1 = num1 << 16;
            num1 = num1 | rand();
            num1 %= n;

            int tmp = vector[i%n];
            vector[i%n] = vector[num1];
            vector[num1] = tmp;
        }
    }

	template<typename T>
	std::ostream & operator<<(std::ostream & os, std::vector<T>& vec)
	{
		for(auto it = vec.begin(); it != vec.end(); ++it)
		{
			os << *it << endl;
		}
		return os;
	}

} // end namespace MyAlgorithms

#endif // !_MYALGORITHMS_H_
