#include <iostream>
#include <omp.h>
#include <cmath>
#include <time.h>
#include <math.h>

using namespace std;

double f(double x)
{
    // функция, интеграл которой нужно найти
    return exp(x);
}

int main(void)
{
    int n = 10000; // число разбиений отрезка
    double a = 0.0; // левый конец отрезка
    double b = 1.0; // правый конец отрезка
    double h = (b-a)/n; // шаг интегрирования
    double integral = 0.0; // значение интеграла

    #pragma omp parallel for reduction(+:integral)
    for(int i=0; i<n; i++)
    {
        double x = a + i*h + h/2.0; // координата середины прямоугольника
        integral += f(x)*h; // площадь прямоугольника
    }

    cout << "Integral: " << integral << endl;

    return 0;
} 
