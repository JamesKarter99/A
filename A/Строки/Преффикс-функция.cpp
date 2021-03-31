/*
* ------------ Преффикс функция ------------
^ O(n)
$ преффикс_функция
? Преффикс-функция – массив длинн наибольших суффиксов подстрок строки s, одновременно являющихся преффиксами строки s. Иначе говоря – это массив длинн наибольших бордеров подстрок строки s.

? Пусть дана строка s = abacaba. Преффикс функция d для нее равна: 0 0 1 0 1 2 3. Т.е.
/   i = 0 1 2 3 4 5 6
?   s = A B A C A B A
?   d = 0 0 1 0 1 2 3

! Что это значит? d[i] равно значению p, если подстрока s[0 ... p - 1] равна подстроке s[i - p + 1 ... i]. Т.е. если говорить иными словами, преффикс подстроки s[0 ... i] длинной p, равен суффиксу этой же подстроки такой же длинны. То есть, да, d[i] равно длинне наибольшего бордера рассматриваемой подстроки s[0 ... i].
? В примере выше d[6] = 3, т.к. d[0 ... 2] = d[4 ... 6] = "ABA".


? ЭФФЕКТИВНЫЙ АЛГОРИТМ:
? Как найти преффикс-функцию для строки? Понятно, что есть наивный алгоритм O(n^3), который вычисляет проеффикс-функицю непосредственно по определению, сравнивая преффиксы и суффиксы. Каждое из действий (__1__) в алгоритме имеет временную сложность O(n) и в сумме алгоритм получается слишком медленным. Попытаемся его улучшить. 

? ПЕРВАЯ ОПТИМИЗАЦИЯ: d[i + 1] не больше чем на единицу превосходит d[i] для любого i.
? Пусть d[i + 1] > d[i] + 1. Рассмотрим ЭТОТ суффикс, который заканчивается в позиции i + 1 и имеет длинну d[i + 1]. Удалим из него один символ, тогда он будет заканчиваться в позиции i и иметь длинну d[i + 1] - 1. Получается, что его длинна больше d[i], а этого быть не может - вышло противоречие. Это позволяет снизить асимптотику до O(n^2). 
todo: этот пункт я не до конца понимаю. Точнее не понимаю, как это уменьшает сложность до O(n^2).

? ВТОРАЯ ОПТИМИЗАЦИЯ: нужно избавиться от явных сравнений подстрок. 
? Пусть мы уже вычислили d[i]. Тогда если s[i + 1] = s[d[i]] (надо еще раз прочитать определение преффикс-функции, там, где про бордеры и их длинны, если непонятно, что это значит), p[i + 1] = p[i] + 1. Если же s[i + 1] != s[d[i]], то .нужно попробовать подстроку меньшей длинны. Хотелось бы сразу перейти к такому бордеру наибольшей длинны j, чтобы его длинны была на единицу меньше, чем длинна текущего бордера, т.е. чтобы j = d[i] = 1. Чтобы найти j, нужно взять за его исходное значение d[i - 1] (__2__) (это следует из первой оптимизации). Если символы s[j] и s[i] не совпадают, то d[k - 1] - следующее наибольшее потенципльное значение j (__3__).
todo: так и не понял этот пункт (__3__)

*/

using line = vector <int>;

//^ O(n)
//& МОЯ СТАРАЯ ПРОВЕРЕННАЯ РЕАЛИЗАЦИЯ ИЗ УРОКА YOUTUBE
// названия переменных аналогичны реализации с e-max
line preffix(string s) {
    int n = s.size();
    line d(n);
 
    int i(1), j(0);
    while (i < n) {
        if (s[i] == s[j]) { // обычное сравнение
            d[i] = j + 1;
            i++;
            j++;
        }
        else if (j == 0) {
            d[i] = 0;
            i++;
        }
        else {
            j = d[j - 1];
        }
    }
 
    return d;
}

//^ O(n^3)
//& НАИВНАЯ РЕАЛИЗАЦИЯ
line preffixN3(string s) {
    int n = s.size();
    line d(n);
                                                           // % 1
    for (int i(0); i < n; i++) {                           // 1. перебор подстрок s[0 ... i] 
        for (int k(0); k <= i; k++) {                      // 2. перебор длинн всех возможных бордеров рассматриваемой подстроки
            if (s.substr(0, k) == s.substr(i - k + 1, k))  // 3. проверка бордеров на равенство
                d[i] = k;
        }
    }

    return d;
}

//& РЕАЛИЗАЦИЯ С E-MAXX, ПОКАЗАВШАЯ ХУДШИЕ РЕЗУЛЬТАТЫ, ЧЕМ МОЯ СТАРАЯ
line preffix(string s) {
    int n = s.size();
    line d(n);

    for (int i(1); i < n; i++) {
        // j - длинна текущего рассматриваемого образца
        int j = d[i - 1]; // % 2

        while (j > 0 && s[i] != s[j])
            j = d[j - 1]; // % 3
        
        if (s[i] == s[j]) // обычное сравнение
            j++;

        d[i] = j;
    }

    return d;
}

//& РЕАЛИЗАЦИЯ МЕНЬШИКОВА
line preffix(string s) {
    int n = s.size();
    line d(n + 1);

    int j(0);
    for (int i(1); i < n; i++) {
        while (true) {
            if (s[i] == s[j]) {
                j++;
                break;
            }
            if (j == 0) {
                break;
            }
            j = d[j];
        }
        d[i + 1] = j;
    }
    
    return d;
}