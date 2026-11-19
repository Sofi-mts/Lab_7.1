// Юніт-тест до лабораторної роботи № 7.1, варіант 8

#define main lab_main          // беремо функції з лаби, але без її main()
#include "Lab_7.1.cpp"
#undef main

int main()
{
    int r0[] = { 5, -3, -4 };
    int r1[] = { 0, -6,  9 };
    int* R[] = { r0, r1 };     // матриця 2 x 3

    int S, k;
    Calc(R, 2, 3, S, k);       // підходять 5, -4, 9

    cout << (S == 10 ? "[ OK ] " : "[FAIL] ") << "Calc: S = " << S << endl;
    cout << (k == 3  ? "[ OK ] " : "[FAIL] ") << "Calc: k = " << k << endl;
    cout << (R[0][0] == 0 && R[0][1] == -3 ? "[ OK ] " : "[FAIL] ")
         << "Calc: elements replaced by 0" << endl;

    system("pause");
    return 0;
}
