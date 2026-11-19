// Юніт-тести до лабораторної роботи № 7.1, варіант 8
// Перевіряються функції Calc, Change, Sort, Create.
// Запуск: відкрити цей файл у VS Code і натиснути F5.

#define main lab_main          // беремо функції з лаби, але без її main()
#include "Lab_7.1.cpp"
#undef main

int passed = 0, failed = 0;

void Check(bool ok, const char* name)
{
    if (ok) passed++; else failed++;
    cout << (ok ? "[ OK ] " : "[FAIL] ") << name << endl;
}

// створення матриці rowCount x colCount і заповнення значеннями з масиву data
int** Make(const int* data, const int rowCount, const int colCount)
{
    int** R = new int*[rowCount];
    for (int i = 0; i < rowCount; i++)
    {
        R[i] = new int[colCount];
        for (int j = 0; j < colCount; j++)
            R[i][j] = data[i * colCount + j];
    }
    return R;
}

// чи збігається матриця R з очікуваними значеннями
bool Equal(int** R, const int* expected, const int rowCount, const int colCount)
{
    for (int i = 0; i < rowCount; i++)
        for (int j = 0; j < colCount; j++)
            if (R[i][j] != expected[i * colCount + j])
                return false;
    return true;
}

void Free(int** R, const int rowCount)
{
    for (int i = 0; i < rowCount; i++)
        delete[] R[i];
    delete[] R;
}

void TestCalc()
{
    // підходять: додатні (5, 9, 37, 1) і не кратні 3 (-4, -11, -1)
    // не підходять: 0, -3, -6, -12
    const int data[] = {  5, -3, -4,  0,
                          9, -6, 37, -11,
                        -12,  1, -1, -3 };
    const int expected[] = { 0, -3,  0,  0,
                             0, -6,  0,  0,
                           -12,  0,  0, -3 };
    int** R = Make(data, 3, 4);
    int S = -100, k = -100;           // Calc має сам обнулити S і k
    Calc(R, 3, 4, S, k);
    Check(S == 5 - 4 + 9 + 37 - 11 + 1 - 1, "Calc: sum S = 36");
    Check(k == 7, "Calc: count k = 7");
    Check(Equal(R, expected, 3, 4), "Calc: matching elements replaced by 0");
    Free(R, 3);
}

void TestCalc_NoneMatch()
{
    const int data[] = { 0, -3, -6, -9, -12, 0 };
    int** R = Make(data, 2, 3);
    int S, k;
    Calc(R, 2, 3, S, k);
    Check(S == 0 && k == 0 && Equal(R, data, 2, 3),
          "Calc: no matching elements, matrix unchanged");
    Free(R, 2);
}

void TestChange()
{
    const int data[] = { 1, 2, 3,
                         4, 5, 6 };
    const int expected[] = { 3, 2, 1,
                             6, 5, 4 };
    int** R = Make(data, 2, 3);
    Change(R, 2, 0, 2);
    Check(Equal(R, expected, 2, 3), "Change: columns 0 and 2 swapped");
    Free(R, 2);
}

void TestSort_FirstRow()
{
    const int data[] = {  7, -2, 15,  0,
                          1,  2,  3,  4,
                          5,  6,  7,  8 };
    const int expected[] = { -2,  0,  7, 15,
                              2,  4,  1,  3,
                              6,  8,  5,  7 };
    int** R = Make(data, 3, 4);
    Sort(R, 3, 4);
    Check(Equal(R, expected, 3, 4), "Sort: columns ascending by row 1");
    Free(R, 3);
}

void TestSort_SecondAndThirdRow()
{
    // однакові в 1-му рядку -> за 2-м рядком; однакові в 1-му і 2-му -> за 3-м
    const int data[] = {  5,  5,  5,  1,
                          9,  3,  3, 20,
                          0, 11, -4,  6,
                         -1, -2, -3, -4 };
    const int expected[] = {  1,  5,  5,  5,
                             20,  3,  3,  9,
                              6, -4, 11,  0,
                             -4, -3, -2, -1 };
    int** R = Make(data, 4, 4);
    Sort(R, 4, 4);
    Check(Equal(R, expected, 4, 4), "Sort: ties resolved by rows 2 and 3");
    Free(R, 4);
}

void TestCreate()
{
    int** R = new int*[7];
    for (int i = 0; i < 7; i++) R[i] = new int[9];
    srand(2026);
    Create(R, 7, 9, -12, 37);
    bool inRange = true;
    for (int i = 0; i < 7; i++)
        for (int j = 0; j < 9; j++)
            if (R[i][j] < -12 || R[i][j] > 37) inRange = false;
    Check(inRange, "Create: all values in [-12, 37]");
    Free(R, 7);
}

int main()
{
    cout << "Lab 7.1 unit tests" << endl;
    TestCalc();
    TestCalc_NoneMatch();
    TestChange();
    TestSort_FirstRow();
    TestSort_SecondAndThirdRow();
    TestCreate();

    cout << endl << "Passed: " << passed << ", failed: " << failed << endl;
    cout << (failed == 0 ? "ALL TESTS PASSED" : "SOME TESTS FAILED") << endl;
    system("pause");
    return failed == 0 ? 0 : 1;
}
