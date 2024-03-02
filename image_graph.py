import sys
import os
import networkx as nx
import matplotlib.pyplot as plt


def draw_directed_graph(vertex_count, edges, save_path=None):
    G = nx.DiGraph()

    G.add_nodes_from(range(1, vertex_count + 1))

    for edge in edges:
        G.add_edge(edge[0], edge[1])

    # Відображення графа
    plt.figure(figsize=(3, 3))
    pos = nx.spring_layout(G)
    nx.draw(G, pos, with_labels=True, node_size=500, node_color='skyblue', font_weight='bold', arrows=True)
    plt.title("Directed Graph")

    image_path = os.path.join(save_path, 'graph.png')

    if os.path.exists(image_path):
        os.remove(image_path)

    plt.savefig(image_path)
    plt.close()
    print(f"Граф збережено у '{image_path}'")


def main():
    if len(sys.argv) > 1:
        file_path_from_qt = sys.argv[1]  # Отримуємо переданий шлях до файлу з C++
        print(f"File path received from Qt: {file_path_from_qt}")

        with open(file_path_from_qt, 'r') as file:
            vertex_count, edge_count = map(int, file.readline().split())
            edges = [tuple(map(int, line.split())) for line in file]

        # Вказати шлях для збереження графа
        save_directory = 'D:/Qt/graphtestproject/pictures'
        draw_directed_graph(vertex_count, edges, save_path=save_directory)


if __name__ == "__main__":
    main()
