#include <iostream>
#include <omp.h>

using namespace std;

int findMaxRec(int A[], int left, int right)
{
    if (left == right) {
        return A[left];
    }

    int mid = (left + right) / 2;
    int maxLeft, maxRight;
    
    #pragma omp task shared(A, maxLeft) // Создание задачи
    {
        maxLeft = findMaxRec(A, left, mid); // Рекурсивный вызов для левой половины
    }
    #pragma omp task shared(A, maxRight) // Создание еще одной задачи
    {
        maxRight = findMaxRec(A, mid + 1, right); // Рекурсивный вызов для правой половины
    }
    
    #pragma omp taskwait // Ожидание завершения задач
    return max(maxLeft, maxRight); // Возвращение максимального значения из двух половин
}

int main()
{
    int A[] = {1, 4, 45, 6, -50, 10, 2};
    int n = sizeof(A) / sizeof(A[0]);
    int maxElement;
    
    #pragma omp parallel
    {
        #pragma omp single // Создание одной задачи в параллельной области
        {
            maxElement = findMaxRec(A, 0, n - 1);
        }
    }
    
    cout << "Max element: " << maxElement << endl;
    
    return 0;
}
