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

void Create(int** R, const int rowCount, const int colCount, const int Low,
            const int High);
void Print(int** R, const int rowCount, const int colCount);
void Sort(int** R, const int rowCount, const int colCount);
void Change(int** R, const int rowCount, const int col1, const int col2);
void Calc(int** R, const int rowCount, const int colCount, int& S, int& k);

int main()
{
    srand((unsigned)time(NULL));    // ініціалізація генератора випадкових чисел

    int Low = -12;                  // нижня межа значень елементів
    int High = 37;                  // верхня межа значень елементів

    int rowCount = 7;               // кількість рядків матриці
    int colCount = 9;               // кількість стовпчиків матриці

    // створення динамічної матриці R розміром rowCount x colCount
    int** R = new int*[rowCount];
    for (int i = 0; i < rowCount; i++)
        R[i] = new int[colCount];

    Create(R, rowCount, colCount, Low, High);
    Print(R, rowCount, colCount);       // початкова матриця

    Sort(R, rowCount, colCount);
    Print(R, rowCount, colCount);       // матриця після впорядкування стовпчиків

    int S = 0;                          // сума елементів, що задовольняють критерію
    int k = 0;                          // кількість таких елементів
    Calc(R, rowCount, colCount, S, k);
    cout << "S = " << S << endl;
    cout << "k = " << k << endl;
    Print(R, rowCount, colCount);       // матриця після заміни елементів нулями

    // звільнення пам'яті
    for (int i = 0; i < rowCount; i++)
        delete[] R[i];
    delete[] R;

    system("pause");                    // щоб вікно не закривалося одразу
    return 0;
}

// формування матриці випадковими числами з діапазону [Low, High]
void Create(int** R, const int rowCount, const int colCount, const int Low,
            const int High)
{
    for (int i = 0; i < rowCount; i++)
        for (int j = 0; j < colCount; j++)
            R[i][j] = Low + rand() % (High - Low + 1);
}

// виведення матриці на екран у вигляді таблиці
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

// впорядкування стовпчиків матриці методом обміну ("бульбашки"):
// якщо два сусідні стовпчики стоять не в тому порядку - міняємо їх місцями
void Sort(int** R, const int rowCount, const int colCount)
{
    for (int j0 = 0; j0 < colCount - 1; j0++)           // номер проходу
        for (int j1 = 0; j1 < colCount - j0 - 1; j1++)  // поточний стовпчик
            if ((R[0][j1] > R[0][j1 + 1])
                ||
                (R[0][j1] == R[0][j1 + 1] &&
                 R[1][j1] > R[1][j1 + 1])
                ||
                (R[0][j1] == R[0][j1 + 1] &&
                 R[1][j1] == R[1][j1 + 1] &&
                 R[2][j1] > R[2][j1 + 1]))
                Change(R, rowCount, j1, j1 + 1);
}

// обмін місцями двох стовпчиків col1 і col2
void Change(int** R, const int rowCount, const int col1, const int col2)
{
    int tmp;                            // допоміжна змінна для обміну
    for (int i = 0; i < rowCount; i++)
    {
        tmp = R[i][col1];
        R[i][col1] = R[i][col2];
        R[i][col2] = tmp;
    }
}

// обчислення суми S і кількості k елементів, які задовольняють критерію
// (додатні або не кратні 3), та заміна цих елементів нулями
void Calc(int** R, const int rowCount, const int colCount, int& S, int& k)
{
    S = 0;
    k = 0;
    for (int i = 0; i < rowCount; i++)
        for (int j = 0; j < colCount; j++)
            if (R[i][j] > 0 || R[i][j] % 3 != 0)
            {
                S += R[i][j];
                k++;
                R[i][j] = 0;
            }
}
