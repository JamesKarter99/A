/*
* ------------ ПРЕОБРАЗОВАНИЕ МНОГОКЛЕТОЧНЫХ ------------
& простые_числа
~ gcd ~ факторизация
? Даны два числа. Требуеться из одного получить другое, сделав наименьшее кол-во операций. Точнее, нужно определить, какое наименьшее кол-во операций
? для этого потребуется. РАЗРЕШАЕТСЯ делить на простое число и умножать на простое число. Или если говорить в терминах разложения на простые множители
? разрешается убрать простой множитель из разложения (факторизации) и добавить. Кол-во этих операций и будет ответом. А как его найти?
? Можно убрать из разложений двух чисел одинаковые множители, поделив оба числа на их НОД, и посчитать кол-во оставшихся множителей. Это и будет ответом.

warning: если два числа поделить на их НОД, то из их разложений будут убраны их общие множители
*/

#include <iostream>
#include <vector>
#include <math.h>

using namespace std;

using line = vector <int>;

line factorization(int p) {
    double e = sqrt(p + .0) + 1;

    line d;
    int i(2);

    while (i < e) {
        if (p % i == 0) {
            d.push_back(i);
            p /= i;
            continue;
        }

        i++;
    }

    if (p > 1)
        d.push_back(p);

    return d;
}

int gcd(int a, int b) {
    if (!b)
        return a;

    return gcd(b, a % b);
}

int main() {
    // ...
    int a, b;
    cin >> a >> b;

    int g = gcd(a, b);

    cout << factorization(a / g).size() + factorization(b / g).size();

    return 0;
}