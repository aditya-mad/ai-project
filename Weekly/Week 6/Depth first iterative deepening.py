import random
import networkx as nx
import matplotlib.pyplot as plt
import numpy as np

T = nx.Graph()
num_nodes = 10
edge_probability = 0.3

G = nx.Graph()

G.add_nodes_from(range(num_nodes))

branching_factor = 3

for node1 in G.nodes():
    for _ in range(branching_factor):
        node2 = random.choice(list(G.nodes()))  # Convert the dictionary view to a list
        if node1 < node2 and random.random() < edge_probability:
            G.add_edge(node1, node2)


def tre(source, target, li):
    if (source == target):
        return True
    if li <= 0:
        return False
    neig = list(G.neighbors(source))

    for j in neig:
        T.add_edge(source, j)
        if tre(j, target, li - 1):
            return True
    return False


def idf(source, target, max_depth):
    for i in range(1, max_depth):  # increasing depth from 1 to max depth
        if (tre(source, target, i)):  # call tre function with present depth,target,present depth
            print("found at depth ", i)
            pos = nx.spring_layout(T)
            nx.draw(T, pos, with_labels=True, node_color='skyblue', node_size=500,
                    font_size=10)  # print tree at present depth
            plt.show()
            return True
        pos = nx.spring_layout(T)
        nx.draw(T, pos, with_labels=True, node_color='skyblue', node_size=500, font_size=10)
        plt.show()
        print("\n")
    return False


source = 0
# target=random.randint(0,9)
target = 9
max_depth = 10
if not idf(source, target, max_depth):
    print("node not found")
