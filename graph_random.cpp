#include <iostream>
#include <fstream>
#include <cstdlib>
#include <ctime>
#include <set>
using namespace std;

int main() {
    int numVertices = 20; // Кількість вершин
    int numEdges = 30;   // Кількість ребер

    srand(time(0)); // Ініціалізація генератора випадкових чисел

    set<pair<int, int>> edges; // Множина для збереження ребер (щоб уникнути дублікатів)

    while (edges.size() < numEdges) {
        int from = rand() % numVertices + 1; // Випадкова вершина від 1 до numVertices
        int to = rand() % numVertices + 1;   // Випадкова вершина від 1 до numVertices

        if (from != to) {
            edges.insert({from, to});
        }
    }

    ofstream outputFile("graph.txt"); // Відкриття файлу для запису

    if (outputFile.is_open()) {
        outputFile << numVertices << " " << numEdges << endl; // Запис кількості вершин та ребер

        for (const auto &edge : edges) {
            outputFile << edge.first << " " << edge.second << endl; // Запис кожного ребра у файл
        }

        outputFile.close(); // Закриття файлу
        cout << "Файл 'graph.txt' створено з успіхом." << endl;
    } else {
        cout << "Неможливо відкрити файл для запису." << endl;
    }

    return 0;
}
