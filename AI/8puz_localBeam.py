import random
import heapq # Used to efficiently find the 'k' best states

class State:
    """Represents a state in the 8-puzzle problem."""
    def __init__(self, board, parent=None, move=""):
        self.board = board
        self.parent = parent
        self.move = move
        self.depth = 0
        if parent:
            self.depth = parent.depth + 1
        
    def __lt__(self, other):
        # This allows State objects to be compared in the priority queue
        # based on their heuristic value.
        return self.heuristic() < other.heuristic()

    def __eq__(self, other):
        # Check if two states have the same board configuration.
        return self.board == other.board

    def __hash__(self):
        # Allows adding states to a set to keep track of visited boards.
        return hash(str(self.board))
        
    def find_blank(self):
        """Finds the (row, col) of the blank tile (0)."""
        for r, row_vals in enumerate(self.board):
            for c, val in enumerate(row_vals):
                if val == 0:
                    return r, c
        return None, None
        
    def heuristic(self):
        """Calculates the Manhattan distance heuristic."""
        distance = 0
        goal_state = [[1, 2, 3], [4, 5, 6], [7, 8, 0]]
        for r in range(3):
            for c in range(3):
                value = self.board[r][c]
                if value != 0:
                    goal_r, goal_c = divmod(value - 1, 3)
                    distance += abs(r - goal_r) + abs(c - goal_c)
        return distance

    def get_successors(self):
        """Generates all valid successor states from the current state."""
        successors = []
        r, c = self.find_blank()
        
        # Possible moves: Up, Down, Left, Right
        moves = {'Up': (-1, 0), 'Down': (1, 0), 'Left': (0, -1), 'Right': (0, 1)}
        
        for move_name, (dr, dc) in moves.items():
            nr, nc = r + dr, c + dc
            
            if 0 <= nr < 3 and 0 <= nc < 3:
                # Create a new board configuration by swapping the blank tile
                new_board = [list(row) for row in self.board]
                new_board[r][c], new_board[nr][nc] = new_board[nr][nc], new_board[r][c]
                
                # Convert back to tuple of tuples to be hashable
                new_board_tuple = tuple(map(tuple, new_board))
                successors.append(State(new_board_tuple, self, move_name))
                
        return successors

def local_beam_search(start_state, goal_state_board, k=5, max_iterations=1000):
    """
    Solves the 8-puzzle using Local Beam Search.
    
    Args:
        start_state (State): The initial state of the puzzle.
        goal_state_board (tuple): The board configuration of the goal.
        k (int): The beam width.
        max_iterations (int): A limit to prevent infinite loops.

    Returns:
        The goal state if found, otherwise None.
    """
    
    # The beam is a list of the k best states found so far.
    beam = [start_state]
    visited = {start_state.board}

    for iteration in range(max_iterations):
        # A priority queue to store all successors from the current beam.
        all_successors = []
        
        # Generate successors for every state in the current beam.
        for state in beam:
            if state.board == goal_state_board:
                print(f"\nSolution found at iteration {iteration}!")
                return state
            
            for successor in state.get_successors():
                if successor.board not in visited:
                    heapq.heappush(all_successors, successor)
                    visited.add(successor.board)
        
        # If there are no new successors, the search is stuck.
        if not all_successors:
            return None
        
        # Form the new beam from the top 'k' successors.
        new_beam = []
        # Use a set to avoid adding duplicate states to the new beam
        beam_boards = set()
        
        while all_successors and len(new_beam) < k:
            best_successor = heapq.heappop(all_successors)
            if best_successor.board not in beam_boards:
                new_beam.append(best_successor)
                beam_boards.add(best_successor.board)
        
        beam = new_beam
        
        # Print progress
        best_in_beam = min(beam, key=lambda s: s.heuristic())
        print(f"Iteration {iteration}: Best Heuristic in Beam = {best_in_beam.heuristic()}")

    return None # No solution found within the iteration limit

def print_solution_path(solution_state):
    """Prints the path from the start state to the solution."""
    if solution_state is None:
        print("No solution found.")
        return
        
    path = []
    current = solution_state
    while current:
        path.append(current)
        current = current.parent
    path.reverse()
    
    print(f"\nSolution Path Found in {len(path) - 1} moves:")
    for i, state in enumerate(path):
        if i > 0:
            print(f"\nStep {i}: Move {state.move}")
        else:
            print("Start State:")
        
        for row in state.board:
            print(" ".join(map(str, row)))

# --- Main Execution ---
if __name__ == "__main__":
    # Define the start and goal states
    # Note: Ensure the start state is solvable. Not all initial configurations are.
    start_board = tuple(map(tuple, [[2, 8, 3], [1, 6, 4], [7, 0, 5]]))
    goal_board = tuple(map(tuple, [[1, 2, 3], [4, 5, 6], [7, 8, 0]]))

    initial_state = State(start_board)

    BEAM_WIDTH = 10 # The 'k' value
    
    print(f"--- Solving 8-Puzzle with Local Beam Search (k={BEAM_WIDTH}) ---")
    print("Initial Board:")
    for row in initial_state.board:
        print(" ".join(map(str, row)))
    print("-" * 20)
    
    solution = local_beam_search(initial_state, goal_board, k=BEAM_WIDTH)
    
    print("-" * 20)
    print_solution_path(solution)