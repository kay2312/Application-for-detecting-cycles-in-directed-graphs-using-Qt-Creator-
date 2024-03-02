import networkx as nx
import matplotlib.pyplot as plt
from matplotlib.animation import FuncAnimation
import sys

visited_nodes = None
graph = None
pos = None
traversal_sequence = None  # Оголошуємо traversal_sequence глобально


# Функція для зчитування графу з файлу
def read_graph_from_file(file_name):
    global graph
    graph = nx.DiGraph()

    with open(file_name, 'r') as file:
        next(file)
        for line in file:
            nodes = list(map(int, line.strip().split()))
            graph.add_edge(nodes[0], nodes[1])


# Функція для зчитування послідовності вершин проходження графу з файлу
def read_traversal_sequence(file_name):
    global traversal_sequence
    with open(file_name, 'r') as file:
        traversal_sequence = [list(map(int, line.strip().split())) for line in file]


def update(frame, ax):
    global visited_nodes, graph, pos, traversal_sequence
    ax.clear()
    nx.draw(graph, pos, with_labels=True, node_size=500, node_color='skyblue', font_weight='bold', ax=ax)

    current_traversal = traversal_sequence[frame]
    for node in current_traversal:
        if node not in visited_nodes:
            visited_nodes.add(node)
            nx.draw_networkx_nodes(graph, pos, nodelist=[node], node_color='yellow', node_size=600, ax=ax)
        else:
            nx.draw_networkx_nodes(graph, pos, nodelist=[node], node_color='yellow', node_size=600, ax=ax)

    chain = ' '.join(map(str, current_traversal))
    ax.text(0.5, -0.1, f"Шлях: {chain}", horizontalalignment='center', verticalalignment='center', transform=ax.transAxes)


def main():
    global visited_nodes, graph, pos, traversal_sequence

    if len(sys.argv) > 1:
        graph_file_name = sys.argv[1]
        print(graph_file_name)

        read_graph_from_file(graph_file_name)
        read_traversal_sequence("D:/Qt/graphtestproject/path.txt")

        pos = nx.spring_layout(graph, k=2.5)

        visited_nodes = set()

        plt.figure(figsize=(3.5, 3.5))
        nx.draw(graph, pos, with_labels=True, node_size=500, node_color='skyblue', font_weight='bold')
        plt.savefig('D:/Qt/graphtestproject/graph_image.png')

        fig, ax = plt.subplots(figsize=(3.5, 3.5))
        ani = FuncAnimation(fig, update, frames=len(traversal_sequence), interval=1000, repeat=False, fargs=(ax,))

        #plt.show()
        ani.save('D:/Qt/graphtestproject/graph_animation.gif', writer='pillow')


if __name__ == "__main__":
    main()
