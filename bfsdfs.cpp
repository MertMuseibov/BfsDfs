/*
Задан неориентированный граф, каждое ребро которого обладает целочисленной пропускной способностью. Найдите максимальный поток из вершины с номером
1 в вершину с номером n.

Формат ввода
    Первая строка входного файла содержит n и m — количество вершин и количество ребер графа (2 ≤ n ≤ 100, 1 ≤ m ≤ 1000). Следующие m
строк содержат по три числа: номера вершин, которые соединяет соответствующее ребро графа и его пропускную способность.
Пропускные способности не превосходят 105.

Формат вывода
В выходной файл выведите одно число — величину максимального потока из вершины с номером 1 в вершину с номером n.
 */

#include <iostream>
#include <cstring>
#include <vector>


const int INF = 1000000000; // константа-бесконечность

struct edge {
    int a, b, cap, flow;
};



void add_edge (int a, int b, int cap, std::vector<edge> &e,std::vector <std::vector<int>> &g) {
    edge e1 = { a, b, cap, 0 };
    edge e2 = { b, a, 0, 0 };
    g[a].push_back ((int) e.size());
    e.push_back (e1);
    g[b].push_back ((int) e.size());
    e.push_back (e2);
}

bool bfs(int *q, int n, int *d, std::vector<edge> &e, int t, std::vector <std::vector<int>> &g, int s) {
    int qh=0, qt=0;
    q[qt++] = s;
    memset (d, -1, n * sizeof d[0]);
    d[s] = 0;
    while (qh < qt && d[t] == -1) {
        int v = q[qh++];
        for (size_t i=0; i<g[v].size(); ++i) {
            int id = g[v][i],
                    to = e[id].b;
            if (d[to] == -1 && e[id].flow < e[id].cap) {
                q[qt++] = to;
                d[to] = d[v] + 1;
            }
        }
    }
    return d[t] != -1;
}

int dfs (int v, int flow, int t, std::vector <int>  &ptr, int *d, std::vector <std::vector<int>> &g, std::vector<edge> &e) {
    if (!flow)  return 0;
    if (v == t)  return flow;
    for (; ptr[v]<(int)g[v].size(); ++ptr[v]) {
        int id = g[v][ptr[v]],
                to = e[id].b;
        if (d[to] != d[v] + 1)  continue;
        int pushed = dfs (to, std::min (flow, e[id].cap - e[id].flow), t, ptr, d, g, e);
        if (pushed) {
            e[id].flow += pushed;
            e[id^1].flow -= pushed;
            return pushed;
        }
    }
    return 0;
}

int dinic(std::vector <int>  &ptr, int n, int *q, int *d, std::vector<edge> &e, int t, int s, std::vector <std::vector<int>> &g) {
    int flow = 0;
    for (;;) {
        if (!bfs(q, n, d, e, t, g, s))  break;
        memset ((void*)&ptr[0], 0, ptr.size());
        while (int pushed = dfs (s, INF,  t, ptr, d, g, e))
            flow += pushed;
    }
    return flow;
}

int main()
{
    int Vertex, Edge;
    std::cin >> Vertex >> Edge;

    std::vector <int>  ptr(Vertex);
    int  source, sink, d[Vertex], q[Vertex]; // номер вершины-истока, номер вершины-стока
    source = 0;
    sink = Vertex - 1;
    std::vector<edge> e;
    std::vector <std::vector<int>> g(Vertex);
    for (int i = 0; i < Edge; i++)
    {
        int first, second, price;
        std::cin >> first >> second >> price;
        add_edge(first - 1, second - 1, price, e, g);
    }
    std::cout << dinic(ptr, Vertex, q, d, e, sink, source, g);
}