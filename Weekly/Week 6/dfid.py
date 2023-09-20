import random
import networkx as nx
import matplotlib.pyplot as plt

num_nodes = 10
edge_probability = 0.3

G = nx.Graph()

G.add_nodes_from(range(num_nodes))

for node1 in G.nodes():
    for node2 in G.nodes():
        if node1 < node2 and random.random() < edge_probability:
            G.add_edge(node1, node2)

def tre(source,target,li):
      if(source==target):
          return True
      if li <= 0:
        return False
      neig=list(G.neighbors(source))
      for j in neig:
        if tre(j,target,li-1):
          return True
      return False

def idf(source,target,max_depth):
  for i in range(max_depth):
    if(tre(source,target,i)):
      print("found at depth ",i)
      return True

  return False




source=0
target=random.randint(0,9) 

max_depth=5;
if not idf(source,target,max_depth):
  print("node not found")

