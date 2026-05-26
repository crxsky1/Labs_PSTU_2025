#include <iostream>
#include <vector>
#include <queue>
#include <climits>
#include <algorithm>
#include <Windows.h>
#include <iomanip>

using namespace std;

const int INF = INT_MAX / 2;
const int N = 6;

int cost[N][N] = {
    {0, 7, 9, 8, 20, 12},
    {7, 0, 10, 4, 11, 6},
    {9, 10, 0, 15, 5, 9},
    {8, 4, 15, 0, 14, 7},
    {20, 11, 5, 14, 0, 10},
    {12, 6, 9, 7, 10, 0}
};

struct Node {
    vector<vector<int>> mat;
    vector<int> path;
    int level;
    int city;
    int bound;
};

int reduceMatrix(vector<vector<int>>& m, bool verbose = true) {
    int n = m.size();
    int reduction = 0;

    // Приведение строк
    for (int i = 0; i < n; ++i) {
        int rowMin = INF;
        for (int j = 0; j < n; ++j)
            rowMin = min(rowMin, m[i][j]);
        if (rowMin != INF && rowMin != 0) {
            reduction += rowMin;
            for (int j = 0; j < n; ++j)
                if (m[i][j] != INF) m[i][j] -= rowMin;
        }
    }

    // Приведение столбцов
    for (int j = 0; j < n; ++j) {
        int colMin = INF;
        for (int i = 0; i < n; ++i)
            colMin = min(colMin, m[i][j]);
        if (colMin != INF && colMin != 0) {
            reduction += colMin;
            for (int i = 0; i < n; ++i)
                if (m[i][j] != INF) m[i][j] -= colMin;
        }
    }
    return reduction;
}

Node* createChild(Node* parent, int to) {
    Node* child = new Node;
    int from = parent->city;

    child->mat = parent->mat;
    child->path = parent->path;
    child->path.push_back(to);
    child->level = parent->level + 1;
    child->city = to;

    int n = child->mat.size();
    for (int i = 0; i < n; ++i) {
        child->mat[from][i] = INF;
        child->mat[i][to] = INF;
    }
    child->mat[to][from] = INF;
    child->bound = parent->bound + parent->mat[from][to] + reduceMatrix(child->mat, true);
    return child;
}

struct Compare {
    bool operator()(Node* a, Node* b) {
        return a->bound > b->bound;
    }
};

int main() {
    SetConsoleOutputCP(CP_UTF8);
    cout << "Исходная матрица затрат:" << endl;
    for (int i = 0; i < N; ++i) {
        for (int j = 0; j < N; ++j)
            cout << setw(3) << cost[i][j] << " ";
        cout << endl;
    }
    cout << endl;

    Node* root = new Node;
    root->mat.resize(N, vector<int>(N));
    for (int i = 0; i < N; ++i)
        for (int j = 0; j < N; ++j)
            root->mat[i][j] = cost[i][j];
    root->path.push_back(0);
    root->level = 1;
    root->city = 0;

    cout << "<<< Приведение корневой матрицы >>>" << endl;
    root->bound = reduceMatrix(root->mat, true);
    cout << "Начальная нижняя граница H0 = " << root->bound << endl << endl;

    priority_queue<Node*, vector<Node*>, Compare> pq;
    pq.push(root);

    int bestCost = INF;
    vector<int> bestPath;

    while (!pq.empty()) {
        Node* cur = pq.top();
        pq.pop();

        cout << "\n--- Анализ узла: путь ";
        for (int v : cur->path) cout << v + 1 << " ";
        cout << ", граница = " << cur->bound << endl;

        if (cur->bound >= bestCost) {
            cout << "  Отсекаем (граница хуже найденного решения " << bestCost << ")" << endl;
            delete cur;
            continue;
        }

        if (cur->level == N) {
            int last = cur->city;
            int first = cur->path[0];
            int total = cur->bound + cost[last][first];
            cout << "  Полный маршрут: ";
            for (int v : cur->path) cout << v + 1 << " ";
            cout << "-> " << first + 1 << ", стоимость = " << total << endl;
            if (total < bestCost) {
                bestCost = total;
                bestPath = cur->path;
                bestPath.push_back(first);
                cout << "  *** Новое лучшее решение ***" << endl;
            }
            delete cur;
            continue;
        }

        for (int next = 0; next < N; ++next) {
            bool visited = false;
            for (int v : cur->path){
				if (v == next){
					visited = true; 
					break; 
				}
			}
            if (visited) continue;

            if (cur->mat[cur->city][next] != INF) {
                Node* child = createChild(cur, next);
                if (child->bound < bestCost) {
                    pq.push(child);
                    cout << "    Узел добавлен в очередь." << endl;
                }
                else {
                    cout << "    Узел отброшен (граница " << child->bound << " >= " << bestCost << ")" << endl;
                    delete child;
                }
            }
        }
        delete cur;
        cout << "  Очередь содержит " << pq.size() << " узлов." << endl;
    }

    cout << "\n=== Результат ===" << endl;
    cout << "Оптимальный маршрут: ";
    for (int v : bestPath) cout << v + 1 << " ";
    cout << "\nСтоимость маршрута: " << bestCost << endl;

    return 0;
}
