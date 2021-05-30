#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <cstdlib>
using namespace std;
#define N 6// количество вершин в нашем графе

// void initMatrix(int matrix[N][N])
// {
//     int distance = 0;
//     for (int i = 0; i < N; i++)
//     {
//         matrix[i][i] = 0;
//         for (int j = i + 1; j < N; j++) {
//             cout << "Enter the distance: " << endl;
//             cin >> distance;
//             matrix[i][j] = distance;
//             matrix[j][i] = distance;
//         }
//     }
// }

void printMatrix(int matrix[N][N])
{
    for (int i = 0; i < N; i++)
    {
        for (int j = 0; j < N; j++)
            cout << matrix[i][j] << " ";
        cout << endl;
    }
}

void findShortestDistance(int matrix[N][N], int min_d[], int vert[], int start)
{
    int minindex = 10000, min = 10000; // индекс вершины с минимальным весом и вес
    int dist = 0; // начальное расстояние

    for (int i = 0; i < N; i++)
    {
        min_d[i] = 10000;//присваивает всем вершинам вес бесконечность
        vert[i] = 1;//отмечает все вершины как необработанные.
    }
    min_d[start] = 0; // обнуляем вес вершины с которой начинаем расчет пути
    // Шаг алгоритма
    do {
        for (int i = 0; i < N; i++)
        { // Если вершину ещё не обошли и вес меньше min
            if ((vert[i] == 1) && (min_d[i] < min))
            { // Переприсваиваем переменной с минимальным значением вес вершины, 
            //а переменной хранящей индекс вершины с минимальным весом индекс текущей вершины
                min = min_d[i];
                minindex = i;
            }
        }
        // Добавляем найденный минимальный вес
        // к текущему весу вершины
        // и сравниваем с текущим минимальным весом вершины
        if (minindex != 10000)
        {
            for (int i = 0; i < N; i++)
            {
                if (matrix[minindex][i] > 0)//если есть ребро между вершинами
                {
                    dist = min + matrix[minindex][i]; //считаем вес текущей метки = равен минимальному расстоянию до этого + вес вершины
                    if (dist < min_d[i]) // если полученный путь меньше веса соседа, 
                    {
                        min_d[i] = dist; // заменим метку самого короткого пути текущим индексом
                    }
                }
            }
            vert[minindex] = 0;// пометим вершину как пройденную
        }
    } while (minindex < 10000);// пока остались не пройденные вершины повторим алгоритм
}

void vertex_path(int matrix[N][N], int min_d[], int start)
{
    int ver[N]; // массив посещенных вершин - обратный путь
    int end = N - 1; // индекс конечной вершины = 6 - 1
    ver[0] = end + 1; // начальный элемент - конечная вершина
    int k = 1; // индекс предыдущей вершины
    int weight = min_d[end]; // вес конечной вершины

    while (end != start) // пока не дошли до начальной вершины
    {
        for (int i = 0; i < N; i++) // просматриваем все вершины ??? ИЛИ (int i = N - 1; i >=0; i--)
            if (matrix[i][end] != 0)   // если вершины соеденены ребром
            {
                int temp = weight - matrix[i][end]; // определяем вес пути из предыдущей вершины: общий вес - вес вершины
                if (temp == min_d[i]) // если вес совпал с рассчитанным
                {                 // значит из этой вершины и был переход
                    weight = temp; // сохраняем новый вес
                    end = i;       // сохраняем предыдущую вершину
                    ver[k] = i + 1; // и записываем ее в массив
                    k++;
                }
            }
    }
    // Вывод кратчайших расстояний до вершин
    cout << endl;
    cout << "The shortest path to vertex: " << endl;
    for (int i = 0; i < N; i++)
        cout << min_d[i];
    cout << endl;

    // Вывод пути (начальная вершина оказалась в конце массива из k элементов)
    cout << "The shortest path: " << endl;
    for (int i = k - 1; i >= 0; i--)
        cout << ver[i];
}

int main()
{
    // создаем матрицу смежности взвешеного графа
    int matrix[N][N] = {
    { 0,  7,  9,  0,  0, 14 }, 
    { 7,  0,  10, 15, 0, 0 },
    { 9,  10, 0,  11, 0, 2 },
    { 0,  15, 11, 0,  6, 0 },
    { 0,  0,  0,  6,  0, 9 },
    { 14, 0,  2,  0,  9, 0 } };
    // создаем массивы
    int vertex[N]; // посещенные вершины
    int min_distance[N]; // минимальное расстояние
    
    int start = 0;//задаем индекс начальной вершины, от которой будем искать путь
    
    // создаем переменные для веса и индекса вершины
    //int min;
    //int minindex;

    // Инициализация матрицы связей
    //initMatrix(matrix);

    // Вывод матрицы связей
    printMatrix(matrix);

    // поиск кратчайшего расстояния
    findShortestDistance(matrix, min_distance, vertex, start);
    
    // Восстановление пути
    vertex_path(matrix, min_distance, start);
   
    getchar();
    return 0;
}