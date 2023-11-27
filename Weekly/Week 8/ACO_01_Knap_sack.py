import random

# Define the knapsack problem parameters
capacity = 50
items = [
    {"name": "Item1", "weight": 10, "value": 130},
    {"name": "Item2", "weight": 20, "value": 120},
    {"name": "Item3", "weight": 30, "value": 110},
]

# ACO parameters
num_ants = 10
max_iterations = 100
pheromone_evaporation = 0.5
alpha = 1.0  # Pheromone influence
beta = 2.0   # Heuristic information influence

# Initialize pheromone levels on items
pheromone_levels = [1.0] * len(items)

# Initialize the best solution found so far
best_solution = {"items": [], "value": 0}

# ACO algorithm
for iteration in range(max_iterations):
    solutions = []

    for ant in range(num_ants):
        knapsack = []
        knapsack_weight = 0
        knapsack_value = 0

        while knapsack_weight < capacity:
            # Calculate item selection probabilities
            probabilities = [
                (i, (pheromone_levels[i] ** alpha) * (items[i]["value"] ** beta))
                for i in range(len(items))
                if i not in knapsack and knapsack_weight + items[i]["weight"] <= capacity
            ]

            if not probabilities:
                break

            # Select an item based on probabilities
            total_prob = sum(prob for _, prob in probabilities)
            probabilities = [(i, prob / total_prob) for i, prob in probabilities]  # Normalize the probabilities
            print(probabilities)
            selected_item = None
            rand = random.uniform(0, 1)
            x = 0.0
            for i, prob in probabilities:
                x+=prob
                if rand <= x:
                    selected_item = i
                    break

            # Add the selected item to the knapsack
            knapsack.append(selected_item)
            knapsack_weight += items[selected_item]["weight"]
            knapsack_value += items[selected_item]["value"]

        # Store the solution
        solutions.append({"items": knapsack, "value": knapsack_value})

    # Display selected items for each ant
    print("Iteration {}: ".format(iteration + 1))
    for ant, solution in enumerate(solutions):
        item_names = [items[i]["name"] for i in solution['items']]
        print("Ant {} - Items: {}, Total Value: {}".format(ant + 1, ', '.join(item_names), solution['value']))

    # Update pheromone levels
    for i in range(len(pheromone_levels)):
        pheromone_levels[i] *= pheromone_evaporation

    for solution in solutions:
        for item in solution["items"]:
            pheromone_levels[item] += 1.0 / solution["value"]

    # Update the best solution
    solutions.sort(key=lambda x: x["value"], reverse=True)
    if solutions[0]["value"] > best_solution["value"]:
        best_solution = solutions[0]

# Print the best solution
best_item_names = [items[i]["name"] for i in best_solution["items"]]
print("Best Solution:")
print("Items: {}, Total Value: {}".format(', '.join(best_item_names), best_solution["value"]))

