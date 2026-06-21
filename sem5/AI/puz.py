import random
import os
import time
# from IPython.display import clear_output

def printG(grid):
    for i in range(0, 9, 3):
        print(grid[i:i+3])
    print()

def clear_screen():
    # os.system('cls' if os.name == 'nt' else 'clear')
    os.system('clear')

Grid = [7, 2, 4, 5, 0, 6, 8, 3, 1]
Goal = [0, 1, 2, 3, 4, 5, 6, 7, 8]

class Puzzle():
    def __init__(self, grid, goal):
        self.grid = grid
        self.goal = goal


    def find_index(self, num):
        for i, val in enumerate(self.grid):
            if val == num:
                return i
        return -1

    def get_valid_moves(self):
        i = self.find_index(0)
        valid_moves = [(1, 3), (0, 2, 4), (1, 5), (0, 4, 6), (1, 3, 5, 7), (2, 4, 8), (3, 7), (4, 6, 8), (5, 7)]

        if self.correct_rows() == 1:
            valid_moves = [(3), (4), (5), (4, 6), (3, 5, 7), (4, 8), (3, 7), (4, 6, 8), (5, 7)]
        if self.correct_rows() == 3:
            valid_moves = [(1, 3), (0, 2, 4), (1, 5), (0, 4), (1, 3, 5), (2, 4), (3), (4, 6), (5)]

        return valid_moves[i]

    def move(self, x):
        i = self.find_index(0)
        if x in self.get_valid_moves():
            self.grid[x], self.grid[i] = self.grid[i], self.grid[x]
    
    def correct_rows(self):
        if (0, 1, 2) == (self.grid[i], self.grid[i+1], self.grid[i+2]):
            return 1
        if (6, 7, 8) == (self.grid[i], self.grid[i+1], self.grid[i+2]):
            return 3

def ReflexAgent():
    puzzle = Puzzle(Grid, Goal)
    moves_count = 0
    while puzzle.grid != puzzle.goal:
        moves = puzzle.get_valid_moves()
        move = random.choice(moves)
        if move == puzzle.grid[move] and random.random() > 0.3:
            move = random.choice(moves)

        puzzle.move(move)
        moves_count += 1

        clear_output()
        print(f"Move {moves_count}:")
        printG(puzzle.grid)
        # time.sleep(0.5)
    print("Solved!")

ReflexAgent()
