def makeGraph():
    graph = {}
    with open('path-info.txt', 'r') as connections:
        paths = connections.readlines()
        for edges in paths:
            curr = edges.split()
            if curr[0] not in graph:
                graph[curr[0]] = [curr[1]]
            else:
                graph[curr[0]].append(curr[1])
    return graph


