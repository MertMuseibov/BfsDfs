/*
Единственный способ попасть в Зал Круглых Столов – пройти через Колонный Коридор.
Стены Коридора изображаются на карте прямыми линиями, которые параллельны оси OY системы координат.
Вход в Коридор находится снизу, а выход из Коридора в Зал – сверху.
В Коридоре есть цилиндрические (на карте круглые) Колонны одинакового радиуса R.
Разработайте алгоритм, который по информации о размерах Коридора, и размещения Колонн определяет диаметр наибольшего из Круглых Столов,
который можно пронести через такой Коридор, сохраняя поверхность Стола горизонтальной.


Для решения этой задачи я сначала использовал бинпоиск, а потом для каждого радиуса стола строил граф, соединяя стены и колоны
 ребрами, в итоге если находился путь с помощью DFS из левой стены до правой, то стол протащить нельзя*/

#include <iostream>
#include <vector>
#include <cmath>
#include <stack>

void clear(int *used, int N)
{
    for (int i = 0; i < N + 2; i++)
        *(used + i) = 0;
}

void enterXY(int *massifX,int *massifY, int N)
{
    for (int i = 0; i < N; i++)
        std::cin >> *(massifX + i) >> *(massifY + i);

}

double len(int x1, int y1, int x2, int y2, int R, double current)
{
    return sqrt(pow(x1 - x2, 2) + pow(y1 - y2, 2)) - 2 * (R + current) ;
}


bool dfs(std::vector < std::vector < int > > &graph, int N)
{


    int used[N + 2];
    clear(&used[0], N);
    std::stack <int> road;
    road.push(N);
    //std::cout << N << std::endl;
    used[N] = 1;
    while (!road.empty())
    {
        int a = road.top();
        //    std::cout << a << " ";
        road.pop();
        for (int i = 0; i < graph[a].size(); i++)
        {
            //    std::cout << graph[a][i] << " ";
            if (used[graph[a][i]] == 0) {
                used[graph[a][i]] = 1;
                road.push(graph[a][i]);
            }
        }
    }

    if (used[N + 1] == 1) {
        graph.clear();
        clear(&used[0], N);
        return false;
    }
    else {
        graph.clear();
        clear(&used[0], N);
        return true;
    }


}


bool graph_construction(std::vector < std::vector < int > > &graph, int *massifX, int *massifY, int R, double current, int N)
{
    for (int i = 0; i < N + 2; i++)
    {
        for (int j = 0; j < N + 2; j++)
        {
            if (i == j)
                continue;
            if (i >= N && j >= N)
            {
                if (abs(massifX[i] - massifX[j]) - 2 * current < 0)
                {
                    graph[i].push_back(j);
                    //graph[j].push_back(i);
                }
            }
            else if (j >= N || i >= N)
            {
                if (abs(massifX[i] - massifX[j]) - 2 * current - R < 0)
                {
                    graph[i].push_back(j);
                    //graph[j].push_back(i);
                }
            }
            else if(len (massifX[i], massifY[i], massifX[j], massifY[j], R, current) < 0)
            {
                graph[i].push_back(j);
                //graph[j].push_back(i);
            }
        }
    }
/*    for (int i = 0; i < N + 2; i++)
    {
        for (int j = 0; j < graph[i].size(); j++)
            std::cout << graph[i][j] << " ";
        std::cout << std::endl;
    } */
    bool flag = dfs(graph, N);
    return flag;
}




int main()
{
    int XL, XR, R, N;
    std::cin >> XL >> XR;
    std::cin >> R;
    std::cin >> N;

    double right = XR - XL;
    double left = 0;

    int massifX[N + 2];

    massifX[N] = XL;
    massifX[N + 1] = XR;

    int massifY[N];
    enterXY(&massifX[0], &massifY[0], N);
    double epsilon = 0.000001;



    while (right - left > epsilon)
    {
        std::vector < std::vector < int > > graph(N + 2);
        bool control = graph_construction(graph, &massifX[0], &massifY[0], R, (right + left)/4, N);
        if (control == true)
            left = (right + left) / 2;
        else
            right = (right + left) / 2;
        //    std::cout << left << " " << right << std::endl;
    }

    printf("%.3lf", right);
}