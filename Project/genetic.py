import random

class PacketRoutePlanning:
    def __init__(self):
        self.servers, self.cache = {}, {}
        self.all_operations = []

    def makeGraph(self):
        with open('path.txt', 'r') as connections:
            paths = connections.readlines()
            for edges in paths:
                curr = edges.split()
                if curr[0] not in self.servers:
                    self.servers[curr[0]] = [curr[1]]
                    self.cache[curr[0]] = {}
                else:
                    self.servers[curr[0]].append(curr[1])

    def askPath(self):
        with open('oper.txt', 'r') as operation_info:
            network = operation_info.readlines()
            for operations in network:
                self.all_operations.append(operations.split())

    def isPathInCache(self, curr_operation):
        return curr_operation[1] in self.cache[curr_operation[0]]

    def updatePathInCache(self, curr_path):  # call for both curr_path and curr_path[::-1]
        for i in range(len(curr_path)):
            for j in range(i + 1, len(curr_path)):
                if not self.isPathInCache([curr_path[i], curr_path[j]]) or len(curr_path[i:j + 1]) < len(self.cache[curr_path[i]][curr_path[j]]):
                    self.cache[curr_path[i]][curr_path[j]] = curr_path[i:j + 1]

    def removePathInCache(self, nodes):
        for server in list(self.cache.keys()):
            remove = [links for links in self.cache[server] if nodes[0] in self.cache[server][links] and nodes[1] in self.cache[server][links]]
            for links in remove:
                self.cache[server].pop(links)

    def clearCache(self):
        self.cache.clear()
        for server in self.servers:
            self.cache[server] = {}

    def printPath(self, path):
        print("[ ", end="")
        for server in range(len(path)):
            if server == len(path) - 1:
                print(path[server], " ]")
                continue
            print(f"{path[server]} -> ", end="")

    def breakLink(self, nodes):
        self.removePathInCache(nodes)
        if nodes[1] in self.servers[nodes[0]]:
            self.servers[nodes[0]].remove(nodes[1])

    def addLink(self, nodes):
        if nodes[1] not in self.servers[nodes[0]]:
            self.servers[nodes[0]].append(nodes[1])

    def geneticAlgorithm(self, start_node, end_node, population_size=100, generations=100):
        population = []
        for _ in range(population_size):
            remaining_nodes = list(self.servers.keys())
            remaining_nodes.remove(start_node)
            remaining_nodes.remove(end_node)
            random.shuffle(remaining_nodes)
            path = [start_node] + remaining_nodes + [end_node]
            population.append(path)

        for _ in range(generations):
            population = self.crossover(population)
            population = self.mutate(population)
            fitness = [(path, self.pathLength(path)) for path in population]
            fitness.sort(key=lambda x: x[1])
            population = [path for path, _ in fitness[:population_size]]
            if end_node in population[0]:
                return population[0]

        return []

    def crossover(self, population):
        new_population = []
        for _ in range(len(population) // 2):
            parent1, parent2 = random.sample(population, 2)
            crossover_point = random.randint(1, len(parent1) - 2)
            child1 = parent1[:crossover_point] + [node for node in parent2 if node not in parent1[:crossover_point]] + parent1[crossover_point:]
            child2 = parent2[:crossover_point] + [node for node in parent1 if node not in parent2[:crossover_point]] + parent2[crossover_point:]
            new_population.extend([child1, child2])
        return new_population

    def mutate(self, population, mutation_rate=0.1):
        for path in population:
            if random.random() < mutation_rate and len(path) > 2:
                mutation_point = random.randint(1, len(path) - 2)
                available_nodes = [node for node in self.servers.keys() if node not in path]
                if available_nodes:
                    new_node = random.choice(available_nodes)
                    path[mutation_point] = new_node
        return population

    def pathLength(self, path):
        return sum(1 for _ in zip(path, path[1:]))

    # Modify findShortestPath to use geneticAlgorithm
    def findShortestPath(self, start_node, end_node):
        path = self.geneticAlgorithm(start_node, end_node)
        return path[1:-1] if path else []

    def sendPacket(self, nodes):
        if self.isPathInCache(nodes):
            # print(f"Packet sent from {nodes[0]} to {nodes[1]} in path - ", self.cache[nodes[0]][nodes[1]])
            print(f"[{nodes[0]} to {nodes[1]}] cache path: ", end="")
            self.printPath(self.cache[nodes[0]][nodes[1]])
            return
        best_path = self.findShortestPath(nodes[0], nodes[1])
        if len(best_path) == 0:
            print(f"[{nodes[0]} to {nodes[1]}] Packet dropped - no path")
        else:
            best_path.insert(0, nodes[0])
            self.updatePathInCache(best_path)
            print(f"[{nodes[0]} to {nodes[1]}] calculated path: ", end="")
            self.printPath(self.cache[nodes[0]][nodes[1]])

    def runPackets(self):
        for current_packet in self.all_operations:
            if current_packet[0] == 'Break':
                print(f"[{current_packet[1]} - {current_packet[2]}] Link is removed")
                self.breakLink(current_packet[1:])
                continue
            if current_packet[0] == 'Add':
                print(f"[{current_packet[1]} - {current_packet[2]}] Link is added")
                self.addLink(current_packet[1:])
                self.clearCache()
                continue
            if current_packet[0] == 'Send':
                self.sendPacket(current_packet[1:])
                continue


if __name__ == '__main__':
    channel = PacketRoutePlanning()
    channel.makeGraph()
    channel.askPath()
    channel.runPackets()
