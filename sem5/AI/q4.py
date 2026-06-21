from collections import deque

def is_safe(board):
    """
    Checks if the last queen placed on the board is in a safe position.
    A board is represented as a tuple of column indices for each row.
    """
    last_queen_row = len(board) - 1
    last_queen_col = board[-1]

    # Check against all previously placed queens
    for r, c in enumerate(board[:-1]):
        # Check column conflict
        if c == last_queen_col:
            return False
        # Check diagonal conflict
        # abs(row_diff) == abs(col_diff)
        if abs(last_queen_row - r) == abs(last_queen_col - c):
            return False
    
    return True

def solve_n_queens_bfs(n):
    """
    Solves the N-Queens problem using Breadth-First Search (BFS).
    
    Returns:
        - The first solution found (tuple).
        - The total number of states explored.
    """
    if n < 1:
        return None, 0

    # The queue will store partial board solutions
    queue = deque([()])
    explored_states = 0

    while queue:
        board = queue.popleft()
        explored_states += 1

        # If a full, valid solution is found
        if len(board) == n:
            return board, explored_states

        # Try placing a queen in the next row in every possible column
        next_row = len(board)
        for col in range(n):
            new_board = board + (col,)
            if is_safe(new_board):
                queue.append(new_board)
    
    return None, explored_states # Should not be reached for solvable N

def solve_n_queens_dfs(n):
    """
    Solves the N-Queens problem using Depth-First Search (DFS).

    Returns:
        - The first solution found (tuple).
        - The total number of states explored.
    """
    if n < 1:
        return None, 0

    # The stack will store partial board solutions
    stack = [()]
    explored_states = 0

    while stack:
        board = stack.pop()
        explored_states += 1

        # If a full, valid solution is found
        if len(board) == n:
            return board, explored_states

        # Try placing a queen in the next row in every possible column
        # Iterate in reverse to add to stack, so col 0 is processed first
        next_row = len(board)
        for col in reversed(range(n)):
            new_board = board + (col,)
            if is_safe(new_board):
                stack.append(new_board)
    
    return None, explored_states # Should not be reached for solvable N

def print_solution(solution):
    """Prints the board in a user-friendly format."""
    if solution is None:
        print("No solution found.")
        return
    n = len(solution)
    for row in range(n):
        line = ""
        for col in range(n):
            if solution[row] == col:
                line += "Q "
            else:
                line += ". "
        print(line)

# --- Main Execution ---
if __name__ == "__main__":
    # N-Queens for N=8 is a standard benchmark.
    # Note: BFS is very slow for N > 6. For N=8, it can take a very long time.
    N = 8
    
    print(f"--- Solving the {N}-Queens Problem ---")

    # --- Depth-First Search ---
    print("\n[1] Running Depth-First Search (DFS)...")
    dfs_solution, dfs_states = solve_n_queens_dfs(N)
    
    print(f"DFS found a solution after exploring {dfs_states} states.")
    print("DFS Solution:")
    print_solution(dfs_solution)
    
    # --- Breadth-First Search ---
    # Warning: This will be very slow and memory-intensive for N=8.
    # We set it to N=6 to demonstrate it works without taking too long.
    N_BFS = 6
    print(f"\n[2] Running Breadth-First Search (BFS) for N={N_BFS} (N=8 is too slow for BFS)...")
    bfs_solution, bfs_states = solve_n_queens_bfs(N_BFS)
    
    print(f"BFS found a solution after exploring {bfs_states} states.")
    print("BFS Solution:")
    print_solution(bfs_solution)

    # --- Comparison ---
    print("\n--- Comparison of Search Strategies ---")
    print("The N-Queens problem is a classic example of a constraint-satisfaction problem.")
    print("DFS is generally much more efficient because it explores one full path at a time.")
    print("It can find a solution deep in the search tree without having to store all nodes at each level.")
    print("\nBFS must explore the tree level-by-level, meaning its memory and time usage grow exponentially.")
    print("For N=8, DFS finds a solution by exploring a few thousand states, while BFS would need to explore millions.")