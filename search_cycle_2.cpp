#include <iostream>
#include <vector>
#include <algorithm>
#include <set>
#include <fstream>

using namespace std;


void saveCycleToFile(const vector<int>& path) {
    ofstream file("path.txt", ios::app); // Відкриття файлу для запису (append mode)

    if (file.is_open()) {
        for (int node : path) {
            file << node << " ";
        }
        file << endl;
        file.close();
    } else {
        cout << "Unable to open file" << endl;
    }
}

void dfs(int v, vector<vector<int>>& graph, vector<bool>& visited, vector<int>& path, set<vector<int>>& cycles) {
    visited[v] = true;
    path.push_back(v);
    cout << "Visiting vertex: " << v << " - Current path: ";
    for (int node : path) {
        cout << node << " ";
    }
    cout << endl;
    saveCycleToFile(path);

    for (int u : graph[v]) {
        if (!visited[u]) { // Якщо вершина не відвідана, запускаємо DFS для неї
            dfs(u, graph, visited, path, cycles);
        } else if (find(path.begin(), path.end(), u) != path.end()) {
            cout << u << "Цикл знайдено\n";
            // Якщо вершина вже в поточному шляху, знайдено цикл
            vector<int> cycle;
            auto it = find(path.begin(), path.end(), u);
            for (auto iter = it; iter != path.end(); ++iter) {
                cycle.push_back(*iter);
                cout << *iter;
            }
            cout << "\n";
            cycles.insert(cycle);
        }
    }
    path.pop_back(); // Після проходження, видаляємо вершину з поточного шляху
    saveCycleToFile(path);
    visited[v] = false; // Позначаємо вершину як невідвідану для інших шляхів
}

// Перевірка, чи один вектор є підмножиною іншого
bool isSubset(const vector<int>& a, const vector<int>& b) {
    if (a.size() > b.size()) {
        return false;
    }

    for (int vertex : a) {
        if (find(b.begin(), b.end(), vertex) == b.end()) {
            return false;
        }
    }

    return true;
}

// Перевірка, чи цикл є замкнутим (початкова вершина збігається з кінцевою)
bool isLoop(const vector<int>& cycle) {
    for (size_t i = 0; i < cycle.size() - 1; ++i) {
        if (cycle[i] == cycle[i + 1]) {
            return true;
        }
    }
    return false;
}

// Функція знаходження усіх циклів у графі
vector<vector<int>> findAllCycles(vector<vector<int>>& graph) {
    int n = graph.size();
    set<vector<int>> cycles;
    vector<bool> visited(n, false); // Масив для відстеження відвіданих вершин
    vector<int> path; // Шлях DFS

    for (int i = 1; i < n; ++i) {
        dfs(i, graph, visited, path, cycles); // Запуск DFS для кожної вершин
    }

    vector<vector<int>> uniqueCycles;

    // Фільтрація унікальних циклів та перевірка на замкнутість
    for (const auto& cycle : cycles) {
        if (cycle.size() > 1 && !isLoop(cycle)) {
            bool isSubsetOfOthers = false;

            // Перевірка, чи цей цикл є підмножиною іншого циклу
            for (const auto& existingCycle : uniqueCycles) {
                if (isSubset(cycle, existingCycle) && cycle.size() == existingCycle.size()) {
                    isSubsetOfOthers = true;
                    break;
                }
            }

            // Якщо цей цикл не є підмножиною іншого циклу, додаємо його
            if (!isSubsetOfOthers) {
                uniqueCycles.push_back(cycle);
            }
        }
    }

    return uniqueCycles;
}

int main() {
    ofstream file("path.txt", ios::trunc);
    freopen("input_1.txt", "r", stdin); // Перенаправлення вводу з файлу "input_1.txt"
    freopen("output.txt", "w", stdout); // Перенаправлення виводу у файл "output.txt"

    int vertexCount, edgeCount;
    cin >> vertexCount >> edgeCount; // Зчитування кількості вершин та ребер з файлу

    cout << "Vertex count: " << vertexCount << "\nEdge count: " << edgeCount << "\n";
    cout << "Edges:\n";

    vector<vector<int>> graph(vertexCount + 1);

    // Зчитування ребер графа та їх виведення на екран
    for (int i = 0; i < edgeCount; ++i) {
        int from, to;
        cin >> from >> to;
        cout << from << "->" << to << "\n";

        if (from < 1 || from > vertexCount || to < 1 || to > vertexCount) {
            cerr << "Invalid vertex encountered in input." << endl;
            return 1; // Помилка: неправильна вершина
        }

        graph[from].push_back(to); // Додавання ребра у граф
    }
    cout << "-------------\n";

    vector<vector<int>> cycles = findAllCycles(graph); // Пошук усіх циклів у графі

    if (cycles.empty()) {
        cout << "The graph has no cycles." << endl; // Вивід результатів: граф не містить циклів
    } else {
        cout << "The graph has the following cycles:" << endl;
        for (const auto& cycle : cycles) {
            for (size_t i = 0; i < cycle.size(); ++i) {
                cout << cycle[i] << "->"; // Виведення вершин циклу
            }
            cout << cycle[0] << endl; // Виведення першої вершини на кінець для повноти циклу
        }
    }

    return 0;
}
