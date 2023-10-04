nodes = int(input("Enter no of nodes - "))  # input number of nodes
adj_matrix = [[] for _ in range(nodes)]

for i in range(nodes):  # input adjacency matrix
    print("Enter Node ", i + 1, " edges - ", end="")
    adj_matrix[i] = list(map(int, input().split()))


def get_nodes():  # Get the node with indegree = 0
    zero_node = -1

    for i in range(nodes):
        count = 0
        for j in range(nodes):  # counting no of nodes with no edge with current chosen node
            if adj_matrix[j][i] == 0:
                count += 1
            else:
                break
        if count == nodes:  # if indegree = 0 then we update
            zero_node = i
            break

    return zero_node


def topological_sort():
    current_node = get_nodes()

    if current_node == -1:  # if -1 then all the nodes are visited 
        return

    print(current_node + 1, end=" ")

    adj_matrix[current_node] = [0 for _ in range(nodes)]  # removing the connections from the node
    adj_matrix[current_node][current_node] = -1  # updating so that -1 so that ambiguity doesn't occur

    topological_sort()  # recall the function to continue


print("Topological sort is - ", end="")
topological_sort()

'''
0 0 0 0 0 0
0 0 0 0 0 0
0 0 0 1 0 0
0 1 0 0 0 0
1 1 0 0 0 0
1 0 1 0 0 0
'''
