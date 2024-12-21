#include <fstream>
#include <chrono>
#include "Sort.h"

int main()
{
    const int cycles = 3000;

    std::ofstream fout("benchmark.csv", std::ios_base::out | std::ios_base::trunc);
    fout << "length,qsort,insertion,fastqsort" << std::endl;

    auto comparator = [](int a, int b)
    { return a < b; };

    for (int arrayLength = 1; arrayLength <= 75; arrayLength++)
    {
        std::chrono::duration<double, std::milli> totalQsortTime;
        std::chrono::duration<double, std::milli> totalInsertionTime;
        std::chrono::duration<double, std::milli> totalFastQsortTime;

        for (int cycle = 0; cycle < cycles; cycle++)
        {
            int a[arrayLength];
            int b[arrayLength];
            int c[arrayLength];

            for (int i = 0; i < arrayLength; i++)
            {
                int number = rand();
                a[i] = number;
                b[i] = number;
                c[i] = number;
            }

            auto t1 = std::chrono::high_resolution_clock::now();
            qsort(a, a + arrayLength - 1, comparator);
            auto t2 = std::chrono::high_resolution_clock::now();
            totalQsortTime += t2 - t1;

            t1 = std::chrono::high_resolution_clock::now();
            insertionSort(b, b + arrayLength - 1, comparator);
            t2 = std::chrono::high_resolution_clock::now();
            totalInsertionTime += t2 - t1;

            t1 = std::chrono::high_resolution_clock::now();
            qsort(c, c + arrayLength - 1, comparator, 60);
            t2 = std::chrono::high_resolution_clock::now();
            totalFastQsortTime += t2 - t1;
        }
        fout << std::fixed << arrayLength << "," << totalQsortTime.count() / cycles << "," << totalInsertionTime.count() / cycles << "," << totalFastQsortTime.count() / cycles << std::endl;
    }
    fout.close();
}
