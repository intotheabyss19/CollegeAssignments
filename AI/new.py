import random

class Room:
    def __init__(self, x, y, state="clean"):
        self.x = x
        self.y = y
        self.state = state

class VacuumAgent:
    def __init__(self, num_rows, num_cols, dirty_rooms):
        self.num_rows = num_rows
        self.num_cols = num_cols
        self.grid = [[Room(r, c) for c in range(num_cols)] for r in range(num_rows)]
        self.current_x = 0
        self.current_y = 0
        self.grid[0][0].state = "vacuum"

        for r, c in dirty_rooms:
            if 0 <= r < num_rows and 0 <= c < num_cols:
                self.grid[r][c].state = "dust"

    def display_grid(self, current_pos=None):
        for r in range(self.num_rows):
            row_states = []
            for c in range(self.num_cols):
                if current_pos and current_pos[0] == r and current_pos[1] == c:
                    row_states.append("V")
                elif self.grid[r][c].state == "dust":
                    row_states.append("D")
                else:
                    row_states.append("C")
            print(" ".join(row_states))
        print("-" * (self.num_cols * 2))

    def run(self):
        print("Vacuum agent started.")
        print("Initial grid configuration:")
        self.display_grid(current_pos=(self.current_x, self.current_y))

        while True:
            all_cleaned = True
            for r in range(self.num_rows):
                for c in range(self.num_cols):
                    if self.grid[r][c].state == "dust":
                        all_cleaned = False
                        break
                if not all_cleaned:
                    break

            if all_cleaned:
                break

            if self.grid[self.current_x][self.current_y].state == "dust":
                self.grid[self.current_x][self.current_y].state = "clean"
                print(f"Cleaned room ({self.current_x},{self.current_y}).")

            if self.current_y > 0:
                print("Moving left.")
                self.current_y -= 1
            else:
                if self.current_x < self.num_rows - 1:
                    print("Can no longer go left. Moving one step down.")
                    self.current_x += 1
                    print("Moving to the far right.")
                    self.current_y = self.num_cols - 1
                else:
                    break

        print("All dirty rooms cleaned. Vacuum agent finished.")
        print("Final grid configuration:")
        self.display_grid()

rows_cols_input = input("Enter the grid dimensions (e.g., 3x3): ")
num_rows, num_cols = map(int, rows_cols_input.split('x'))

dirty_percentage = int(input("Enter the percentage of dirty rooms (e.g., 30 for 30%): "))

total_rooms = num_rows * num_cols
num_dirty_rooms = int(total_rooms * (dirty_percentage / 100))

all_possible_rooms = [(r, c) for r in range(num_rows) for c in range(num_cols)]
dirty_rooms_coords = random.sample(all_possible_rooms, num_dirty_rooms)

agent = VacuumAgent(num_rows, num_cols, dirty_rooms_coords)
agent.run()