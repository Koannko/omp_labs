#include <iostream>
#include <omp.h>

using namespace std;

int main()
{
  int row1, row2, col1, col2;
  double **a, **b, **c;

  cout << "A row: ";
  cin >> row1;
  cout << "A col: ";
  cin >> col1;
  cout << "B row: ";
  cin >> row2;
  cout << "B col: ";
  cin >> col2;

  if (col1 != row2)
  {
    cout << "Error!";
    cin.get();
    cin.get();
    return 0;
  }

  a = new double*[row1];
  cout << "A elements" << endl;
  for (int i = 0; i < row1; i++)
  {
    a[i] = new double[col1];
    for (int j = 0; j < col1; j++)
    {
      a[i][j] = 1;
    }
  }

  b = new double*[row2];
  cout << "B elements" << endl;
  for (int i = 0; i < row2; i++)
  {
    b[i] = new double[col2];
    for (int j = 0; j < col2; j++)
    {
      b[i][j] = 1;
    }
  }

  // Выделение памяти для матрицы С
  c = new double*[row1];
  for (int i = 0; i < row1; i++)
  {
    c[i] = new double[col2];
  }

  #pragma omp parallel for shared(a, b, c)
  for (int i = 0; i < row1; i++)
  {
    for (int j = 0; j < col2; j++)
    {
      c[i][j] = 0;
      for (int k = 0; k < col1; k++)
        c[i][j] += a[i][k] * b[k][j];
    }
  }

  cout << "Result of multiplying" << endl;
  for (int i = 0; i < row1; i++)
  {
    for (int j = 0; j < col2; j++)
      cout << c[i][j] << " ";
    cout << endl;
  }
}