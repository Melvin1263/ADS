#include "MyAlgorithms.h"
namespace MyAlgorithms
{
    size_t LeftChild(size_t i)
    {
        return 2 * i + 1;
    }

    void max_heapify(vector<int>& a, int i, int n)
    {
        size_t child = i;
        int tmp = a[i];

        for (size_t j = i; LeftChild(j) < n;)
        {
            child = LeftChild(j);
            if (child != n - 1 && a[child] < a[child + 1])
            {
                child++;
            }
            if (tmp < a[child])
            {
                Swap(a[j], a[child]);

                j = child;
            }
            else
                break;
        }
    }

    void HeapSort(vector<int>& a)
    {
        size_t size = a.size();

        DEBUG("MaxHeap-Aufbau von:" << endl << "Durchlauf 0: " << VectorToString(a) << endl);

        for (int i = size / 2; i >= 0; i--)
        {
            DEBUG("percDown(" << a[i] << ") Durchlauf " << i << ": ");
            max_heapify(a, i, size);
            DEBUG(VectorToString(a) << endl);
        }

        DEBUG("Heap - Sort durchfuehren : " << endl << "Durchlauf 0: " << VectorToString(a) << endl);

        for (size_t j = size - 1; j > 0; j--)
        {
            Swap(a[0], a[j]);

            DEBUG("percDown(" << a[0] << ") Durchlauf " << j << ": ");
            max_heapify(a, 0, j);
            DEBUG(VectorToString(a) << endl);
        }
    }

    void Merge(vector<int> &values, vector<int> &tmp, int low, int pivot, int high)
    {
        int leftEnd = high - 1;
        int tmpPos = low;
        int numElement = pivot - low + 1;

        DEBUG("Merge(" << low << ", " << leftEnd << ", " << high << ", " << pivot << "): ");

        for (; low <= leftEnd && high <= pivot; tmpPos++)
        {
            if (values[low] <= values[high])
            {
                tmp[tmpPos] = values[low];
                low++;
            }
            else
            {
                tmp[tmpPos] = values[high];
                high++;
            }
        }
        for (; low <= leftEnd; tmpPos++)
        {
            tmp[tmpPos] = values[low];
            low++;
        }
        for (; high <= pivot; tmpPos++)
        {
            tmp[tmpPos] = values[high];
            high++;
        }
        for (int i = 0; i < numElement; i++, pivot--)
        {
            values[pivot] = tmp[pivot];
        }

        DEBUG(VectorToString(values) << endl);
    }
    void MergeSort(vector<int> &values, vector<int> &tmp, int left, int right)
    {
        if (left < right)
        {
            int center = (left + right) / 2;
            DEBUG("MergeSort(" << left << ", " << center << ")" << endl);
            MergeSort(values, tmp, left, center);
            DEBUG("MergeSort(" << center + 1 << ", " << right << ")" << endl);
            MergeSort(values, tmp, center + 1, right);
            Merge(values, tmp, left, right, center + 1);
        }
    }

    int Median3(vector<int> a, int left, int right)
    {
        int center = (left + right) / 2;

        if (a[center] < a[left])
        {
            Swap(a[left], a[center]);
        }
        if (a[right] < a[left])
        {
            Swap(a[left], a[right]);
        }
        if (a[right] < a[center])
        {
            Swap(a[center], a[right]);
        }

        DEBUG("Pivot (Median3): a[" << center << "] = " << a[center]);

        // Pivotelement
        return a[center];
    }

    void QuickSort(vector<int>& arr, int left, int right)
    {
        if (left > right)
            return;

        DEBUG("quicksort(a, " << left << ", " << right << ")" << endl);

        int pivot = 0;

        if (right - left > 10)
            pivot = Median3(arr, left, right);
        else
        {
            pivot = arr[(left + right) / 2];
            DEBUG("Pivot: a[" << (left + right) / 2 << "] = " << pivot << endl);
        }

        DEBUG(VectorToString(arr) << endl);

        int i = left, j = right;

        for (; i < j;)
        {
            for (; arr[i] < pivot; i++);
            for (; pivot < arr[j]; j--);
            if (i < j)
            {
                Swap(arr[i], arr[j]);
            }
        }

        DEBUG(VectorToString<int>(arr) << endl);

        QuickSort(arr, left, i - 1);
        QuickSort(arr, i + 1, right);
    }

    void ShellSort(vector<int>& values)
    {
        size_t size = values.size();

        size_t gap = 1;

        // H berechnen
        for (size_t i = 1; i <= size; i = i * 2 + 1)
            gap = i;

        // Schleife über die Abstandsfolge
        for (; gap > 0; gap = (gap - 1) / 2) // H = gap
        {
            for (size_t i = gap; i < size; i++)
            {
                int tmp = values[i];
                size_t j = i;
                // Insertion Sort im Abstand von gap
                for (; j >= gap && tmp < values[j - gap]; j -= gap)
                {
                    values[j] = values[j - gap];
                }
                values[j] = tmp;
            }
        }
    }

    void MatrixMul_ColMajor(vector<double> &a, vector<double> &b, vector<double> &c, int n)
	{
		int lda = n;
		int ldb = n;
		int ldc = n;
		double s = 0.0;

		for (int i = 0; i < n; i++)
		{
			for (int j = 0; j < n; j++)
			{
				s = 0.0;
				for (int k = 0; k < n; k++)
				{
					s = s + a[i + k*lda] * b[k + j*ldb];
				}
				c[i + j*ldc] = s;
			}
		}
	}

	void MatrixMul_RowMajor(vector<double> &a, vector<double> &b, vector<double> &c, int n)
	{
		int lda = n;
		int ldb = n;
		int ldc = n;
		double s = 0.0;

        for (int i = 0; i < n; i++)
        {
            for (int j = 0; j < n; j++)
            {
                s = 0.0;
                for (int k = 0; k < n; k++)
                {
                    s = s + a[k + i*lda] * b[j + k*ldb];
                }
                c[j + i*ldc] = s;
            }
        }
	}

    void MatrixMul_ColMajorThreaded(vector<double>& a, vector<double>& b, vector<double>& c, int n)
    {
        int lda = n;
        int ldb = n;
        int ldc = n;
        double s = 0.0;

#pragma omp parallel for
        for (int i = 0; i < n; i++)
        {
#pragma omp parallel for
            for (int j = 0; j < n; j++)
            {
                s = 0.0;
                for (int k = 0; k < n; k++)
                {
                    s = s + a[i + k*lda] * b[k + j*ldb];
                }
                c[i + j*ldc] = s;
            }
        }
    }

    void MatrixMul_RowMajorThreaded(vector<double>& a, vector<double>& b, vector<double>& c, int n)
    {
        int lda = n;
        int ldb = n;
        int ldc = n;
        double s = 0.0;

#pragma omp parallel for
        for (int i = 0; i < n; i++)
        {
#pragma omp parallel for
            for (int j = 0; j < n; j++)
            {
                s = 0.0;
                for (int k = 0; k < n; k++)
                {
                    s = s + a[k + i*lda] * b[j + k*ldb];
                }
                c[j + i*ldc] = s;
            }
        }
    }
}