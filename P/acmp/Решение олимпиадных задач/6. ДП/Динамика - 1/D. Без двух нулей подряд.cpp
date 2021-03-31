/*
* ------------ БЕЗ ДВУХ НУЛЕЙ ПОДРЯД ------------
& Дианмика - 1
~ одномерная_динамика
? Будем поддерживать два массива o и d - где o[i] равно кол-ву чисел длинной i в системе счисления с основанием k, которые оканчиваются на 0, а d[i] - таких же чисел, которые оканчиваются не но ноль. Изначально o[1] = 0, т.к. у чисел не может быть ведущих нулей, а d[i] = k-1. Будем заполнять массивы по порядку от i = 2 до n. Итак, сразу заметим, что т.к. двух нулей подряд в чисел быть не может, то o[i] равно d[i-1], т.е. ранво кол-ву чисел, которые оканчиваются не на ноль. С d[i] сложнее. Мы можем дописать k-1 разных цифр к o[i - 1] числам, а так же к d[i - 1] разным числам. То есть получаем (o[i - 1] + d[i - 1]) * (k-1). 

? Все помещается в int.
*/

#include <iostream>
#include <vector>

using namespace std;

using line = vector <int>;

int main() {
	// ...
	ios::sync_with_stdio(false);
	int n, k;
	cin >> n >> k;

	line o(n + 1);
	line d(n + 1);

	d[1] = k - 1;

	for (int i(2); i <= n; i++) {
		o[i] = d[i - 1];
		d[i] = (o[i - 1] + d[i - 1]) * (k - 1);
	}

	cout << o[n] + d[n];
	
	return 0;
}