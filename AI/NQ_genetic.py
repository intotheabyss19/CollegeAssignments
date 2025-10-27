import random

def calculate_fitness(individual):
    n = len(individual)
    non_attacking_pairs = 0
    for i in range(n):
        for j in range(i + 1, n):
            if abs(i - j) != abs(individual[i] - individual[j]):
                non_attacking_pairs += 1
                
    return non_attacking_pairs

def crossover(parent1, parent2):
    n = len(parent1)
    crossover_point = random.randint(1, n - 1)
    child = parent1[:crossover_point]
    
    for gene in parent2:
        if gene not in child:
            child.append(gene)
            
    return child

def mutate(individual, mutation_rate):
    if random.random() < mutation_rate:
        n = len(individual)
        idx1, idx2 = random.sample(range(n), 2)
        individual[idx1], individual[idx2] = individual[idx2], individual[idx1]
    return individual

def solve_n_queens_ga(n, population_size, max_generations, mutation_rate):
    max_fitness = n * (n - 1) // 2
    population = []
    for _ in range(population_size):
        individual = list(range(n))
        random.shuffle(individual)
        population.append(individual)

    for generation in range(max_generations):
        fitness_scores = [calculate_fitness(ind) for ind in population]
        best_fitness = 0
        best_individual = None
        for i in range(population_size):
            if fitness_scores[i] > best_fitness:
                best_fitness = fitness_scores[i]
                best_individual = population[i]
            if fitness_scores[i] == max_fitness:
                print(f"\nSolution found in generation {generation}!")
                return population[i], generation

        print(f"Generation {generation}: Best Fitness = {best_fitness}/{max_fitness}")

        new_population = []
        parents = random.choices(population, weights=fitness_scores, k=population_size * 2)

        for i in range(0, len(parents), 2):
            parent1 = parents[i]
            parent2 = parents[i+1]
            
            child = crossover(parent1, parent2)
            
            child = mutate(child, mutation_rate)
            
            new_population.append(child)
        
        population = new_population

    print("\nNo solution found within the maximum number of generations.")
    return best_individual, max_generations

def print_solution(solution):
    if solution is None:
        print("No solution to print.")
        return
    n = len(solution)
    print(f"Board Configuration: {solution}")
    for row in range(n):
        line = ""
        for col in range(n):
            if solution[row] == col:
                line += "Q "
            else:
                line += ". "
        print(line)

if __name__ == "__main__":
    N = 8
    POPULATION_SIZE = 150
    MAX_GENERATIONS = 1000
    MUTATION_RATE = 0.2
    
    solution, generations_ran = solve_n_queens_ga(N, POPULATION_SIZE, MAX_GENERATIONS, MUTATION_RATE)
    
    print("\n--- Final Result ---")
    print_solution(solution)