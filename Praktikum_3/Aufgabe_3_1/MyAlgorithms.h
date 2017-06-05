#ifndef _MYALGORITHMS_H_
#define _MYALGORITHMS_H_

#include <vector>
#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include <list>
#include <functional>
#include <algorithm>
#include <iomanip>
#include <map>
#include <omp.h>

#ifdef _DEBUG
#define DEBUG(str) { std::cout << str; }
#else
#define DEBUG(str)
#endif

#define QUESTION(message, execute) do { char i = 'n'; \
do { \
    std::cout << message << std::endl; \
    std::cout << "[J]a/[N]ein? "; \
    std::cin >> i; \
\
    if (i != 'j') \
        break; \
\
    execute \
} while (i != 'n');  } while(0)

namespace MyAlgorithms
{
    template <typename T>
    void RandomVectorGenerator(std::vector<T>&vector, int n)
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

            T tmp = vector[i%n];
            vector[i%n] = vector[num1];
            vector[num1] = tmp;
        }
    }

    template <typename T>
    void RandomVectorGenerator(std::vector<T>* vector, int n)
    {
        vector->resize(n);

        for (int i = 0; i < n; i++)
        {
            (*vector)[i] = i + 1;
        }

        for (int i = 0; i < n; i++)
        {
            int num1 = rand();
            num1 = num1 << 16;
            num1 = num1 | rand();
            num1 %= n;

            T tmp = (*vector)[i%n];
            (*vector)[i%n] = (*vector)[num1];
            (*vector)[num1] = tmp;
        }
    }

    class MeasureManager
    {
        typedef std::function<void(std::vector<int>&)> Func;

        MeasureManager()
        {
        }
    public:
        class Algorithm
        {
            std::string m_filename;
            std::string m_algoname;
            Func m_function;
        public:
            Algorithm(std::string algoname, Func function) :
                m_algoname(algoname), m_function(function)
            {
                std::transform(algoname.begin(), algoname.end(), algoname.begin(), ::tolower);
                m_filename = algoname;
                m_filename.append(".txt");
            }
            Algorithm(std::string filename, std::string algoname, Func function) :
                m_filename(filename), m_algoname(algoname), m_function(function)
            {
                
            }
            std::string getFilename() { return m_filename; }
            std::string getAlgoName() { return m_algoname; }

            void call(std::vector<int>& data) { m_function(data); }

            void operator()(std::vector<int>& data) { return m_function(data); }
        };

        typedef std::list<MeasureManager::Algorithm> AlgorithmList;

    public:
        static MeasureManager& getInstance()
        {
            static MeasureManager instance;
            return instance;
        }

        void addAlgorithm(std::string filename, std::string algoname, Func function) 
        {
            m_algorithms.push_back(Algorithm(filename, algoname, function));
        }

        void addAlgorithm(std::string algoname, Func function)
        {
            m_algorithms.push_back(Algorithm(algoname, function));
        }

        void doMeasure()
        {

            for (auto it = m_algorithms.begin(); it != m_algorithms.end(); ++it)
            {
                bool breakit = false;
                do {
                    char choose;
                    std::cout << "Messung durchfuehren fuer: " << it->getAlgoName() << "? [J]a/[N]ein > ";
                    std::cin >> choose;
                    if (choose == 'j')
                    {
                        std::cout << "Messung ..." << std::endl;
                        internal_doMeasure(it);
                        breakit = true;
                    }
                    else if (choose == 'n')
                        breakit = true;
                    else
                        continue;
                } while (!breakit);
            }
          
        }
    private:
        void internal_doMeasure(AlgorithmList::iterator current)
        {
            std::ofstream file;
            file.open(current->getFilename());

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
                std::vector<int> randomData;
                RandomVectorGenerator(randomData, n);

                // Measuring
                dtime = omp_get_wtime();
                current->call(randomData);
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

    private:
        std::list<MeasureManager::Algorithm> m_algorithms;
        std::map<int, std::vector<int>*> m_rvectormap;
    };

	template<typename T>
	std::ostream& operator<< (std::ostream& os, std::vector<T>& vec);

    typedef std::function<void(std::vector<int>&)> Func;
    typedef std::list<Func> SortFuncList;

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
    std::string VectorToString(std::vector<T>& values)
    {
        std::stringstream result;

        for (std::vector<T>::const_iterator it = values.begin(); it != values.end(); ++it)
        {
            result << *it;
            result << ' ';
        }
        return result.str();
    }

	// Heapsort
    size_t LeftChild(size_t i);
	void max_heapify(std::vector<int> &a, int i, int n);
	void HeapSort(std::vector<int> &a);

	// MergeSort
	void Merge(std::vector<int> &a, std::vector<int> &b, int low, int pivot, int high);
    void MergeSort(std::vector<int> &a, std::vector<int> &b, int low, int high);

	// Quicksort
    // Median von 3 Werten berechnen
    int Median3(std::vector<int> a, int left, int right);
	void QuickSortOld(std::vector<int> &arr, int left, int right);

    // Verbesserte Implementierung
    void QuickSort(std::vector<int>& arr, int left, int right);

	// Shellsort
    void ShellSort(std::vector<int> &values);

	// Matrix Multiplikation
	void MatrixMul_ColMajor(std::vector<double> &a, std::vector<double> &b, std::vector<double> &c, int n);
	void MatrixMul_RowMajor(std::vector<double> &a, std::vector<double> &b, std::vector<double> &c, int n);

    // Matrix Multiplikation - Parallel
    void MatrixMul_ColMajorThreaded(std::vector<double> &a, std::vector<double> &b, std::vector<double> &c, int n);
    void MatrixMul_RowMajorThreaded(std::vector<double> &a, std::vector<double> &b, std::vector<double> &c, int n);

	template<typename T>
	std::ostream & operator<<(std::ostream & os, std::vector<T>& vec)
	{
		for(auto it = vec.begin(); it != vec.end(); ++it)
		{
			os << *it << std::endl;
		}
		return os;
	}
    
} // end namespace MyAlgorithms

#endif // !_MYALGORITHMS_H_
