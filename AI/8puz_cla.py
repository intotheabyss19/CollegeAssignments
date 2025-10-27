import random
import time
from collections import deque
import heapq

def printG(grid):
    """Print the grid in a 3x3 format."""
    for i in range(0, 9, 3):
        print(grid[i:i+3])
    print()

class Puzzle():
    def __init__(self, grid, goal):
        """Initializes the puzzle with a starting grid and a goal state."""
        self.grid = grid[:]
        self.goal = goal

    def find_index(self, num):
        """Finds the index of a given number in the grid."""
        for i, val in enumerate(self.grid):
            if val == num:
                return i
        return -1

    def get_valid_moves(self):
        """Returns a list of valid moves for the empty tile."""
        i = self.find_index(0)
        valid_moves = []
        
        if i >= 3:
            valid_moves.append("up")
        if i <= 5:
            valid_moves.append("down")
        if i % 3 != 0:
            valid_moves.append("left")
        if i % 3 != 2:
            valid_moves.append("right")
            
        return valid_moves

    def move(self, direction):
        """Moves the empty tile in the specified direction."""
        i = self.find_index(0)
        
        if direction not in self.get_valid_moves():
            return

        if direction == "up":
            swap_index = i - 3
        elif direction == "down":
            swap_index = i + 3
        elif direction == "left":
            swap_index = i - 1
        elif direction == "right":
            swap_index = i + 1
        
        self.grid[i], self.grid[swap_index] = self.grid[swap_index], self.grid[i]

# ==================== HEURISTIC FUNCTIONS ====================

def calculate_manhattan_distance(grid, goal):
    """Calculate the Manhattan distance heuristic."""
    distance = 0
    for i in range(9):
        if grid[i] != 0:
            row_current, col_current = divmod(i, 3)
            row_goal, col_goal = divmod(goal.index(grid[i]), 3)
            distance += abs(row_current - row_goal) + abs(col_current - col_goal)
    return distance

def misplaced_tiles(grid, goal):
    """Count the number of misplaced tiles."""
    return sum(1 for i in range(9) if grid[i] != 0 and grid[i] != goal[i])

def linear_conflict(grid, goal):
    """
    Linear conflict heuristic: two tiles are in conflict if they are in their 
    goal row/column but need to pass each other. Adds 2 moves for each conflict.
    """
    conflict = 0
    
    # Check rows
    for row in range(3):
        for i in range(3):
            for j in range(i + 1, 3):
                pos_i = row * 3 + i
                pos_j = row * 3 + j
                
                tile_i = grid[pos_i]
                tile_j = grid[pos_j]
                
                if tile_i != 0 and tile_j != 0:
                    goal_i = goal.index(tile_i)
                    goal_j = goal.index(tile_j)
                    
                    # Both tiles belong to this row in goal
                    if goal_i // 3 == row and goal_j // 3 == row:
                        # But they're in wrong order
                        if goal_i > goal_j:
                            conflict += 2
    
    # Check columns
    for col in range(3):
        for i in range(3):
            for j in range(i + 1, 3):
                pos_i = i * 3 + col
                pos_j = j * 3 + col
                
                tile_i = grid[pos_i]
                tile_j = grid[pos_j]
                
                if tile_i != 0 and tile_j != 0:
                    goal_i = goal.index(tile_i)
                    goal_j = goal.index(tile_j)
                    
                    # Both tiles belong to this column in goal
                    if goal_i % 3 == col and goal_j % 3 == col:
                        # But they're in wrong order
                        if goal_i > goal_j:
                            conflict += 2
    
    return conflict

def corner_tiles_heuristic(grid, goal):
    """
    Additional heuristic: penalize corner tiles that are far from their position.
    Corner tiles are hardest to move.
    """
    corners = [0, 2, 6, 8]
    penalty = 0
    for corner in corners:
        if grid[corner] != 0:
            tile = grid[corner]
            goal_pos = goal.index(tile)
            if goal_pos in corners:
                # Corner tile in wrong corner gets extra penalty
                if corner != goal_pos:
                    penalty += 2
    return penalty

# ==================== A* GOAL-BASED AGENT ====================

def AStarGoalBasedAgent(grid, goal, verbose=True):
    """
    Goal-based agent using A* search with Manhattan distance + Linear Conflict heuristic.
    This is the classic approach: minimize estimated total cost to reach goal.
    """
    start_state = tuple(grid)
    goal_state = tuple(goal)
    
    if start_state == goal_state:
        if verbose:
            print("Already solved!")
        return 0, True, []
    
    # Priority queue: (f_score, g_score, state, path)
    # f_score = g_score + h_score (total estimated cost)
    frontier = []
    start_h = calculate_manhattan_distance(grid, goal) + linear_conflict(grid, goal)
    heapq.heappush(frontier, (start_h, 0, start_state, []))
    
    explored = set()
    nodes_expanded = 0
    
    if verbose:
        print("="*60)
        print("A* GOAL-BASED AGENT")
        print("Heuristic: Manhattan Distance + Linear Conflict")
        print("Objective: Minimize path length to goal state")
        print("="*60)
        print("\nInitial Grid:")
        printG(list(start_state))
        print(f"Initial heuristic value: {start_h}")
        print("\nSearching for optimal path...\n")
    
    while frontier:
        f_score, g_score, current_state, path = heapq.heappop(frontier)
        
        if current_state in explored:
            continue
        
        explored.add(current_state)
        nodes_expanded += 1
        
        if verbose and nodes_expanded % 1000 == 0:
            print(f"Nodes expanded: {nodes_expanded}, Current depth: {g_score}, Queue size: {len(frontier)}")
        
        if current_state == goal_state:
            if verbose:
                print(f"\n{'='*60}")
                print(f"✓ GOAL-BASED AGENT SOLVED THE PUZZLE!")
                print(f"{'='*60}")
                print(f"Optimal moves: {len(path)}")
                print(f"Nodes expanded: {nodes_expanded}")
                print(f"Solution path: {' -> '.join(path)}")
                print(f"\nFinal Grid:")
                printG(list(current_state))
            return len(path), True, path
        
        # Generate neighbors
        current_grid = list(current_state)
        puzzle = Puzzle(current_grid, goal)
        
        for move in puzzle.get_valid_moves():
            temp_grid = current_grid[:]
            i = temp_grid.index(0)
            
            if move == "up": swap_index = i - 3
            elif move == "down": swap_index = i + 3
            elif move == "left": swap_index = i - 1
            else: swap_index = i + 1
            
            temp_grid[i], temp_grid[swap_index] = temp_grid[swap_index], temp_grid[i]
            next_state = tuple(temp_grid)
            
            if next_state not in explored:
                new_g_score = g_score + 1  # Each move costs 1
                # Heuristic: Manhattan + Linear Conflict
                h_score = calculate_manhattan_distance(temp_grid, goal) + linear_conflict(temp_grid, goal)
                new_f_score = new_g_score + h_score
                new_path = path + [move]
                
                heapq.heappush(frontier, (new_f_score, new_g_score, next_state, new_path))
    
    if verbose:
        print("✗ No solution found!")
    return -1, False, []

# ==================== A* UTILITY-BASED AGENT ====================

def AStarUtilityBasedAgent(grid, goal, verbose=True):
    """
    Utility-based agent using A* search with a multi-criteria utility function.
    Maximizes utility = quality of state - cost to reach it.
    
    Utility components:
    - Negative Manhattan distance (closer to goal = higher utility)
    - Negative misplaced tiles (fewer wrong tiles = higher utility)
    - Negative linear conflicts (fewer conflicts = higher utility)
    - Pattern bonuses (correct rows/columns get bonuses)
    - Move cost penalty (fewer moves = higher utility)
    """
    start_state = tuple(grid)
    goal_state = tuple(goal)
    
    if start_state == goal_state:
        if verbose:
            print("Already solved!")
        return 0, True, []
    
    def calculate_utility(grid, goal, moves):
        """
        Calculate utility score for a state.
        Higher utility = better state.
        """
        # Distance metrics (negative because lower is better)
        manhattan = calculate_manhattan_distance(grid, goal)
        misplaced = misplaced_tiles(grid, goal)
        conflicts = linear_conflict(grid, goal)
        
        # Pattern bonuses: reward for correct rows/columns
        row_bonus = 0
        for row in range(3):
            if grid[row*3:(row+1)*3] == goal[row*3:(row+1)*3]:
                row_bonus += 10
        
        col_bonus = 0
        for col in range(3):
            if [grid[col], grid[col+3], grid[col+6]] == [goal[col], goal[col+3], goal[col+6]]:
                col_bonus += 10
        
        # Corner bonus: corners in correct position
        corner_bonus = sum(2 for i in [0, 2, 6, 8] if grid[i] == goal[i])
        
        # Composite utility function
        utility = (
            -manhattan * 2.0      # Primary: minimize distance
            - misplaced * 1.5     # Secondary: minimize misplaced tiles
            - conflicts * 0.5     # Tertiary: minimize conflicts
            + row_bonus           # Bonus: complete rows
            + col_bonus           # Bonus: complete columns
            + corner_bonus        # Bonus: correct corners
            - moves * 0.1         # Small penalty for move count
        )
        
        return utility
    
    # Priority queue: (-utility, g_score, state, path)
    # We negate utility because heapq is a min-heap
    frontier = []
    start_utility = calculate_utility(grid, goal, 0)
    heapq.heappush(frontier, (-start_utility, 0, start_state, []))
    
    explored = set()
    nodes_expanded = 0
    
    if verbose:
        print("="*60)
        print("A* UTILITY-BASED AGENT")
        print("Heuristic: Multi-criteria Utility Function")
        print("Objective: Maximize state utility - move cost")
        print("="*60)
        print("\nInitial Grid:")
        printG(list(start_state))
        print(f"Initial utility value: {start_utility:.2f}")
        print("\nSearching for optimal path...\n")
    
    while frontier:
        neg_utility, g_score, current_state, path = heapq.heappop(frontier)
        
        if current_state in explored:
            continue
        
        explored.add(current_state)
        nodes_expanded += 1
        
        if verbose and nodes_expanded % 1000 == 0:
            print(f"Nodes expanded: {nodes_expanded}, Current depth: {g_score}, Utility: {-neg_utility:.2f}")
        
        if current_state == goal_state:
            if verbose:
                print(f"\n{'='*60}")
                print(f"✓ UTILITY-BASED AGENT SOLVED THE PUZZLE!")
                print(f"{'='*60}")
                print(f"Optimal moves: {len(path)}")
                print(f"Nodes expanded: {nodes_expanded}")
                print(f"Final utility: {-neg_utility:.2f}")
                print(f"Solution path: {' -> '.join(path)}")
                print(f"\nFinal Grid:")
                printG(list(current_state))
            return len(path), True, path
        
        # Generate neighbors
        current_grid = list(current_state)
        puzzle = Puzzle(current_grid, goal)
        
        for move in puzzle.get_valid_moves():
            temp_grid = current_grid[:]
            i = temp_grid.index(0)
            
            if move == "up": swap_index = i - 3
            elif move == "down": swap_index = i + 3
            elif move == "left": swap_index = i - 1
            else: swap_index = i + 1
            
            temp_grid[i], temp_grid[swap_index] = temp_grid[swap_index], temp_grid[i]
            next_state = tuple(temp_grid)
            
            if next_state not in explored:
                new_g_score = g_score + 1
                # Calculate utility for this state
                utility = calculate_utility(temp_grid, goal, new_g_score)
                new_path = path + [move]
                
                # Push with negative utility (min-heap maximizes utility)
                heapq.heappush(frontier, (-utility, new_g_score, next_state, new_path))
    
    if verbose:
        print("✗ No solution found!")
    return -1, False, []

# ==================== STANDARD A* (FOR COMPARISON) ====================

def StandardAStarAgent(grid, goal, verbose=True):
    """
    Standard A* search with Manhattan distance heuristic only.
    For comparison purposes.
    """
    start_state = tuple(grid)
    goal_state = tuple(goal)
    
    if start_state == goal_state:
        if verbose:
            print("Already solved!")
        return 0, True, []
    
    frontier = []
    start_h = calculate_manhattan_distance(grid, goal)
    heapq.heappush(frontier, (start_h, 0, start_state, []))
    
    explored = set()
    nodes_expanded = 0
    
    if verbose:
        print("="*60)
        print("STANDARD A* AGENT (Manhattan Distance Only)")
        print("="*60)
        print("\nInitial Grid:")
        printG(list(start_state))
        print(f"Initial heuristic: {start_h}")
        print("\nSearching...\n")
    
    while frontier:
        f_score, g_score, current_state, path = heapq.heappop(frontier)
        
        if current_state in explored:
            continue
        
        explored.add(current_state)
        nodes_expanded += 1
        
        if current_state == goal_state:
            if verbose:
                print(f"\n{'='*60}")
                print(f"✓ STANDARD A* SOLVED!")
                print(f"{'='*60}")
                print(f"Moves: {len(path)}")
                print(f"Nodes expanded: {nodes_expanded}")
                printG(list(current_state))
            return len(path), True, path
        
        current_grid = list(current_state)
        puzzle = Puzzle(current_grid, goal)
        
        for move in puzzle.get_valid_moves():
            temp_grid = current_grid[:]
            i = temp_grid.index(0)
            
            if move == "up": swap_index = i - 3
            elif move == "down": swap_index = i + 3
            elif move == "left": swap_index = i - 1
            else: swap_index = i + 1
            
            temp_grid[i], temp_grid[swap_index] = temp_grid[swap_index], temp_grid[i]
            next_state = tuple(temp_grid)
            
            if next_state not in explored:
                new_g_score = g_score + 1
                h_score = calculate_manhattan_distance(temp_grid, goal)
                new_f_score = new_g_score + h_score
                new_path = path + [move]
                
                heapq.heappush(frontier, (new_f_score, new_g_score, next_state, new_path))
    
    return -1, False, []

# ==================== MAIN EXECUTION ====================

if __name__ == "__main__":
    Grid = [7, 2, 4, 5, 0, 6, 8, 3, 1]
    Goal = [0, 1, 2, 3, 4, 5, 6, 7, 8]
    
    print("\n" + "="*60)
    print("SOLVING 8-PUZZLE WITH DIFFERENT A* VARIANTS")
    print("="*60)
    print(f"Initial: {Grid}")
    print(f"Goal:    {Goal}")
    print("="*60 + "\n")
    
    # Run Goal-Based A* Agent
    moves1, success1, path1 = AStarGoalBasedAgent(Grid, Goal, verbose=False)
    time.sleep(1)
    
    print("\n")
    
    # Run Utility-Based A* Agent
    moves2, success2, path2 = AStarUtilityBasedAgent(Grid, Goal, verbose=False)
    time.sleep(1)
    
    print("\n")
    
    # Run Standard A* for comparison
    moves3, success3, path3 = StandardAStarAgent(Grid, Goal, verbose=False)
    
    # Final Comparison
    print("\n" + "="*60)
    print("FINAL COMPARISON")
    print("="*60)
    print(f"{'Agent':<35} {'Moves':<10} {'Status':<10}")
    print("-"*60)
    print(f"{'Goal-Based A* (Manhattan+Conflict)':<35} {moves1:<10} {'✓ Success' if success1 else '✗ Failed'}")
    print(f"{'Utility-Based A* (Multi-criteria)':<35} {moves2:<10} {'✓ Success' if success2 else '✗ Failed'}")
    print(f"{'Standard A* (Manhattan only)':<35} {moves3:<10} {'✓ Success' if success3 else '✗ Failed'}")
    print("="*60)
    
    print("\nKEY INSIGHTS:")
    print("• Goal-Based: Optimizes purely for shortest path")
    print("• Utility-Based: Balances multiple quality metrics")
    print("• Both find optimal solutions guaranteed by A*")
    print("• Different heuristics may explore different numbers of nodes")