// Lab_7.1.cpp
// Кучер Софія
// Лабораторна робота № 7.1.
// Пошук заданих елементів та впорядкування рядків / стовпчиків матриці.
// Варіант 8
//
// Діапазон значень елементів матриці: (-12, ..., 37)
// Матриця R розмірністю (7 x 9) із елементів цілого типу.
// Критерій - всі додатні або крім кратних 3.
// Ключі впорядкування: -> -> ->
//  - переставляються стовпчики, щоб елементи першого рядка були за зростанням;
//  - при однакових елементах першого рядка - за зростанням елементів другого рядка;
//  - при однакових елементах першого і другого рядків - за зростанням третього рядка.


#include <iostream>
#include <iomanip>
#include <cstdlib>
#include <time.h>

using namespace std;

// формування матриці випадковими числами з діапазону [Low, High]
void Create(int** R, const int rowCount, const int colCount, const int Low, const int High)
{
    for (int i = 0; i < rowCount; i++)
        for (int j = 0; j < colCount; j++)
            R[i][j] = Low + rand() % (High - Low + 1);
}

// виведення матриці у вигляді таблиці
void Print(int** R, const int rowCount, const int colCount)
{
    cout << endl;
    for (int i = 0; i < rowCount; i++)
    {
        for (int j = 0; j < colCount; j++)
            cout << setw(4) << R[i][j];
        cout << endl;
    }
    cout << endl;
}

// обмін місцями стовпчиків col1 і col2
void Change(int** R, const int rowCount, const int col1, const int col2)
{
    for (int i = 0; i < rowCount; i++)
        swap(R[i][col1], R[i][col2]);
}

// впорядкування стовпчиків "бульбашкою" за 1-м, 2-м і 3-м рядками (за зростанням)
void Sort(int** R, const int rowCount, const int colCount)
{
    for (int j0 = 0; j0 < colCount - 1; j0++)
        for (int j = 0; j < colCount - j0 - 1; j++)
            if (R[0][j] > R[0][j + 1] ||
                (R[0][j] == R[0][j + 1] && (R[1][j] > R[1][j + 1] ||
                (R[1][j] == R[1][j + 1] && R[2][j] > R[2][j + 1]))))
                Change(R, rowCount, j, j + 1);
}

// сума S і кількість k елементів, що є додатними або не кратні 3; заміна їх нулями
void Calc(int** R, const int rowCount, const int colCount, int& S, int& k)
{
    S = k = 0;
    for (int i = 0; i < rowCount; i++)
        for (int j = 0; j < colCount; j++)
            if (R[i][j] > 0 || R[i][j] % 3 != 0)
            {
                S += R[i][j];
                k++;
                R[i][j] = 0;
            }
}

int main()
{
    srand((unsigned)time(NULL));

    const int rowCount = 7, colCount = 9;   // розміри матриці
    int** R = new int*[rowCount];
    for (int i = 0; i < rowCount; i++)
        R[i] = new int[colCount];

    Create(R, rowCount, colCount, -12, 37);
    Print(R, rowCount, colCount);

    Sort(R, rowCount, colCount);
    Print(R, rowCount, colCount);

    int S, k;                               // сума і кількість заданих елементів
    Calc(R, rowCount, colCount, S, k);
    cout << "S = " << S << endl << "k = " << k << endl;
    Print(R, rowCount, colCount);

    for (int i = 0; i < rowCount; i++)
        delete[] R[i];
    delete[] R;

    system("pause");
    return 0;
}
