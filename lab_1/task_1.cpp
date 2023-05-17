#include <omp.h>
#include <cstdio>
#include <iostream>

using namespace std;

int main(void)
{
#pragma omp parallel
    {
        int id, n;
        id = omp_get_thread_num();
        n = omp_get_num_threads();

        printf("Номер потока: %d, Число потоков в группе: %d\n", id, n);
    }
    return 0;
}