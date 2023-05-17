#include <omp.h>
#include <cstdio>
#include <iostream>

using namespace std;
int arrA[] = {1, 2, 3, 4, 5, 6, 1, 2, 3, 4, 5, 6, 1, 2, 3, 4, 5, 6, 1, 2, 3, 4, 5, 6};
int len = end(arrA) - begin(arrA);
int arrB[4];
int sumArrA = 0;

int main(void)
{
#pragma omp parallel
    {
        int id, n;
        int sumArrB = 0;
        id = omp_get_thread_num();
        n = omp_get_num_threads();

        for (int i = id * len / n; i < (id + 1) * len / n; i++)
        {
            sumArrB += arrA[i];
        }
        arrB[id] = sumArrB;
        printf("Номер потока: %d, Сумма элементов потока: %d\n", id, sumArrB);
    }
    for (int i = 0; i < 4; i++)
    {
        sumArrA += arrB[i];
    }
    printf("Сумма элементов: %d\n", sumArrA);
    return 0;
}