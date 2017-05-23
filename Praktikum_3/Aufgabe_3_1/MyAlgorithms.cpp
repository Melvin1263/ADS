#include "MyAlgorithms.h"
namespace MyAlgorithms
{
    size_t LeftChild(size_t i)
    {
        return 2 * i + 1;
    }

    void max_heapify(std::vector<int>& a, int i, int n)
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

    void HeapSort(std::vector<int>& a)
    {
        int size = (int)a.size();

        DEBUG("MaxHeap-Aufbau von:" << std::endl << "Durchlauf 0: " << VectorToString(a) << std::endl);

        for (int i = size / 2; i >= 0; i--)
        {
            DEBUG("percDown(" << a[i] << ") Durchlauf " << i << ": ");
            max_heapify(a, i, size);
            DEBUG(VectorToString(a) << std::endl);
        }

        DEBUG("Heap - Sort durchfuehren : " << std::endl << "Durchlauf 0: " << VectorToString(a) << std::endl);

        for (int j = size - 1; j > 0; j--)
        {
            Swap(a[0], a[j]);

            DEBUG("percDown(" << a[0] << ") Durchlauf " << j << ": ");
            max_heapify(a, 0, j);
            DEBUG(VectorToString(a) << std::endl);
        }
    }

    void Merge(std::vector<int> &values, std::vector<int> &tmp, int low, int pivot, int high)
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

        DEBUG(VectorToString(values) << std::endl);
    }
    void MergeSort(std::vector<int> &values, std::vector<int> &tmp, int left, int right)
    {
        if (left < right)
        {
            int center = (left + right) / 2;
            DEBUG("MergeSort(" << left << ", " << center << ")" << std::endl);
            MergeSort(values, tmp, left, center);
            DEBUG("MergeSort(" << center + 1 << ", " << right << ")" << std::endl);
            MergeSort(values, tmp, center + 1, right);
            Merge(values, tmp, left, right, center + 1);
        }
    }

    int Median3(std::vector<int> a, int left, int right)
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

    void QuickSortOld(std::vector<int>& arr, int left, int right)
    {
        if (left > right)
            return;

        DEBUG("quicksort(a, " << left << ", " << right << ")" << std::endl);

        int pivot = 0;

        if (right - left > 10)
            pivot = Median3(arr, left, right);
        else
        {
            pivot = arr[(left + right) / 2];
            DEBUG("Pivot: a[" << (left + right) / 2 << "] = " << pivot << std::endl);
        }

        DEBUG(VectorToString(arr) << std::endl);

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

        DEBUG(VectorToString<int>(arr) << std::endl);

        QuickSortOld(arr, left, i - 1);
        QuickSortOld(arr, i + 1, right);
    }

    void ShellSort(std::vector<int>& values)
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

    void MatrixMul_ColMajor(std::vector<double> &a, std::vector<double> &b, std::vector<double> &c, int n)
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

	void MatrixMul_RowMajor(std::vector<double> &a, std::vector<double> &b, std::vector<double> &c, int n)
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

    void MatrixMul_ColMajorThreaded(std::vector<double>& a, std::vector<double>& b, std::vector<double>& c, int n)
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

    void MatrixMul_RowMajorThreaded(std::vector<double>& a, std::vector<double>& b, std::vector<double>& c, int n)
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

    void QuickSort(std::vector<int>& arr, int left, int right) {
        DEBUG("quicksort(a, " << left << ", " << right << ")" << std::endl);

        int i = left, j = right;
        int tmp;
        int pivot = arr[(left + right) / 2];

        DEBUG("Pivot: a[" << (left + right) / 2 << "] = " << pivot << std::endl);

        /* partition */
        while (i <= j) {
            while (arr[i] < pivot)
                i++;
            while (arr[j] > pivot)
                j--;
            if (i <= j) {
                tmp = arr[i];
                arr[i] = arr[j];
                arr[j] = tmp;
                i++;
                j--;
            }
        };

        DEBUG(VectorToString<int>(arr) << std::endl);

        /* recursion */
        if (left < j)
            QuickSort(arr, left, j);
        if (i < right)
            QuickSort(arr, i, right);
    }

}