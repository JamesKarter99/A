/*
* ------------ АЛГОРИТМ ФОРДА БЕЛЛМАНА - 2 ------------
^ O(n*m)
$ форд_беллман $ форд_беллман_проверка_на_наличие_отрицательного_цикла $ форд_беллман_проверка_на_наличие_отриц_цикла_c_восстановлением
# список_ребер
? Алгоритм находит кратчайшие расстояния из начальной вершины во все вершины графа. Алгоритм применим к любым графам, не содержащим цикла с отрицательной длинной. 

? Граф представлен в виде списка ребер edge, содержащим кортежи вида (a, b, w); каждый кортеж означает, что существует ребро веса w, соединяющее вершины a и b. Алгоритм состоит из n-1 раундов (n – кол-во вершин). На каждом раунде алгоритм перебирает все ребра и пытается уменьшить расстояния. В массиве dist хранятся расстояния от вершины s до кажой вершины графа, изначально инициализированные как INF.
*/

vector <int> dist(n, INF);
dist[s] = 0; // начальная вершина

for (int i(0); i < n-1; i++) {
	for (const auto& e : d) {
		auto [a, b, w] = e; // рассматриваемое ребро

		if (dist[a] < INF && dist[a] + w < dist[b])
			dist[b] = dist[a] + w;
	}
}

/*
& проверка на наличие отрицательного цикла
? Необходимо правильно обработать случай наличия достижимого отрицательного цикла из начальной вершины. Если алгоритм не ограничивать n-1 раундом, то в этом случае он будет бесконечно много раз «улучшать» расстояния вершин, лежащих на таком цикле. Поэтому достаточно проверить: если на n-1 фазе произошло хотя бы одно изменения расстояния, то в графе существует цикл отрицательного веса, достижимый из стартовой вершины.

? После выполнения n-1 раунда будет выполнен n-ый (__1__). Если на нем была изменена хотя бы одна вершина, алгоритм запомнит ее (если таких вершин несколько, то последнюю из них) в переменную x.

? Чтоб за n итераций не произошло переполнения типа данных, минимальным значением расстояния устанавливется -INF.

? ВАЖНО!!! В задачах на такие темы не гарантируется, что граф связан, так что проверки на наличие цикоа для одной вершины может быть недостаточно.
*/

bool fordBellmanCycle(int start) {
    dist[start] = 0;
 
    int x;
    for (int i(0); i < n; i++) {
        x = -1;
 
        for (const auto& e : d) {
            auto [a, b, w] = e;
 
            if (dist[a] < INF && dist[a] + w < dist[b]) {
                dist[b] = max(-INF, dist[a] + w);
                x = b;
            }
        }
    }
 
    return x != -1; // в графе присутствует отрицательный цикл
}

/*
& проверка на наличие отрицательного цикла с восстановлением пути
? Для того, чтобы восстановить отрицательный цикл, достижимый из данной вершины, необходимо использовать алгоритм Форда-Беллмана, как и для проверки на наличие такого цикла. Однако теперь нужно поддерживать массив предков parents: parent[b] = a, если существует ребро из a в b. Так же необходимо запомнить номер вершины x, в которой произошла релаксация на n-ой фазе.

? Если отрицательный цикл будет найден, то вершина x либо лежит на этом цикле, либо достижима из него. Чтобы получить номер вершины y, которая грантированно лежит на цикле, достаточно n раз пройти по предкам.
*/

bool fordBellmanCycleWithPath(int start) {
    dist[start] = 0;

    int x;
    for (int i(0); i < n; i++) {
        x = -1;

        for (const auto& e : d) {
            auto [a, b, w] = e;

            if (dist[a] < INF && dist[a] + w < dist[b]) {
                dist[b] = max(-INF, dist[a] + w);
                parent[b] = a;
                x = b;
            }
        }
    }
    
    if (x != -1) {
        // цикл найден: вывод цикла

        // найдем вершину y такую, что она гарантированно лежит на цикле (см. теорию по ФОрду-Беллмана)
        int y = x; 
        for (int i(0); i < n; i++)
            y = parent[y];

        // обойдем массив предков и восстановим цикл
        int start = y;
        vector <int> path;

        do {
            path.push_back(y);
            y = parent[y];
        } while (y != start);

        path.push_back(start);

        // вывод пути в порядке обхода
        reverse(path.begin(), path.end());

        // code: на данном моементе в path хранится цикл отрицательного веса

        return true;
    }

    return false; // цикла нет
}