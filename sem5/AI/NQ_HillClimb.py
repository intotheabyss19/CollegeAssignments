import random

def create_board(n):
    """
    Creates a random initial state for the N-Queens problem.
    Returns a list where index=row and value=column.
    """
    board = list(range(n))
    random.shuffle(board)
    return board

def calculate_heuristic(board):
    """
    Calculates the number of attacking pairs of queens.
    A solution has a heuristic of 0.
    """
    n = len(board)
    attacking_pairs = 0
    
    # We only need to check for diagonal attacks because our representation
    # prevents row and column attacks between queens in different rows.
    for i in range(n):
        for j in range(i + 1, n):
            # Check for diagonal conflict
            # abs(row_diff) == abs(col_diff)
            if abs(i - j) == abs(board[i] - board[j]):
                attacking_pairs += 1
                
    return attacking_pairs

def greedy_hill_climbing(initial_board, max_steps=1000):
    """
    Performs one run of greedy hill climbing.
    
    Returns:
        - The final board configuration.
        - The heuristic of the final board.
    """
    current_board = list(initial_board)
    current_heuristic = calculate_heuristic(current_board)
    
    for _ in range(max_steps):
        if current_heuristic == 0:
            # Found a solution
            return current_board, 0
        
        best_neighbor = None
        best_heuristic = current_heuristic

        # --- Find the best neighbor ---
        for row_to_move in range(len(current_board)):
            original_col = current_board[row_to_move]
            # Try moving the queen in this row to every other column
            for new_col in range(len(current_board)):
                if new_col == original_col:
                    continue
                
                # Create a temporary neighbor board
                neighbor = list(current_board)
                neighbor[row_to_move] = new_col
                
                h = calculate_heuristic(neighbor)
                if h < best_heuristic:
                    best_heuristic = h
                    best_neighbor = neighbor
        
        # --- Move or Stop ---
        if best_heuristic >= current_heuristic:
            # No better neighbor found, we are stuck in a local minimum
            return current_board, current_heuristic
        
        # Move to the best neighbor
        current_board = best_neighbor
        current_heuristic = best_heuristic
        
    return current_board, current_heuristic # Reached max steps

def random_restart_hill_climbing(n, max_restarts=100):
    """
    Solves N-Queens using Random-Restart Hill Climbing.
    
    Returns:
        - The solution board if found.
        - The number of restarts it took.
        - None if no solution is found.
    """
    print(f"--- Starting Random-Restart Hill Climbing for {n}-Queens ---")
    for i in range(max_restarts):
        # 1. Generate a new random initial state
        initial_board = create_board(n)
        
        print(f"\nRestart #{i+1}")
        print(f"Initial State: {initial_board} | Heuristic: {calculate_heuristic(initial_board)}")
        
        # 2. Run a single instance of greedy hill climbing
        final_board, final_heuristic = greedy_hill_climbing(initial_board)
        
        print(f"-> Stuck at Local Minimum: {final_board} | Heuristic: {final_heuristic}")
        
        # 3. Check if a solution was found
        if final_heuristic == 0:
            print(f"\nSolution found after {i + 1} restarts!")
            return final_board, i + 1
            
    print(f"\nNo solution found after {max_restarts} restarts.")
    return None, max_restarts

def print_solution(board):
    """Prints the board in a user-friendly format."""
    if board is None:
        print("No solution to print.")
        return
    n = len(board)
    print(f"\nBoard Configuration: {board}")
    for row in range(n):
        line = ""
        for col in range(n):
            if board[row] == col:
                line += "Q "
            else:
                line += ". "
        print(line)

# --- Main Execution ---
if __name__ == "__main__":
    N = 8
    MAX_RESTARTS = 50
    
    solution_board, restarts_needed = random_restart_hill_climbing(N, MAX_RESTARTS)
    
    print("\n--- Final Result ---")
    print_solution(solution_board)