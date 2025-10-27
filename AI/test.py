class Graph:
    def __init__(self, edges):
        self.edges = edges

    def get_neighbors(self, node):
        return self.edges.get(node, [])


def ida_star_search(graph, start, goal, heuristic):
    threshold = heuristic[start]  # Initial threshold
    path = [start]

    while True:
        temp = ida_star_dls(graph, path, 0, threshold, goal, heuristic)
        if temp is True:  # Goal found
            return path
        if temp is None:  # No path found
            return None
        threshold = temp  # Update threshold


def ida_star_dls(graph, path, g, threshold, goal, heuristic):
    current = path[-1]
    f = g + heuristic[current]

    if f > threshold:
        return f  # Return cost if over the threshold

    if current == goal:
        return True  # Goal found

    min_threshold = float('inf')  # Track the minimum threshold encountered

    for neighbor, cost in graph.get_neighbors(current):
        if neighbor in path:  # Avoid cycles
            continue
        path.append(neighbor)
        
        temp = ida_star_dls(graph, path, g + cost, threshold, goal, heuristic)
        
        if temp is True:
            return True  # Goal found at this path
        if temp is not None:
            min_threshold = min(min_threshold, temp)  # Update minimum threshold

        path.pop()  # Backtrack

    return min_threshold if min_threshold != float('inf') else None  # No valid paths


# Example heuristic
heuristic = {
    'A': 7, 'B': 6, 'C': 2, 'D': 1,
    'E': 5, 'F': 1, 'G': 0, 'H': 3,
    'I': 1, 'J': 4, 'K': 0, 'L': 0,
    'M': 2, 'N': 1, 'O': 0, 'P': 0
}

# Graph as given:
G = {
    'A': [('B', 3), ('C', 5), ('D', 4)],
    'B': [('E', 2), ('F', 4), ('G', 7), ('H', 4)],
    'C': [('F', 3), ('H', 2), ('I', 4), ('O', 7)],
    'D': [('J', 9)],
    'E': [('K', 2)],
    'F': [('K', 1)],
    'G': [],
    'H': [('L', 9), ('M', 7)],
    'I': [('M', 3), ('N', 2)],
    'J': [('O', 3), ('P', 1)],
    'L': [],
    'K': [],
    'M': [],
    'N': [],
    'O': [],
    'P': []
}

# Example usage
if __name__ == "__main__":
    graph = Graph(G)
    start_node = 'A'
    goal_node = 'G'

    path_ida_star = ida_star_search(graph, start_node, goal_node, heuristic)
    print("IDA* Search Path:", path_ida_star)
