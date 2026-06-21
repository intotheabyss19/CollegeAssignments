import random
from collections import deque

class Vacuum2DEnv:
    def __init__(self, grid):
        self.grid = [row[:] for row in grid]  # Deep copy
        self.rows = len(grid)
        self.cols = len(grid[0]) if self.rows > 0 else 0
    
    def is_dirty(self, pos): r, c = pos; return self.grid[r][c] == 'dirty'
    def clean(self, pos): r, c = pos; self.grid[r][c] = 'clean'
    def all_clean(self): return all(v == 'clean' for row in self.grid for v in row)
    def neighbors(self, pos): 
        r, c = pos; d=[(r-1,c),(r+1,c),(r,c-1),(r,c+1)]
        return [(x,y) for x,y in d if 0<=x<self.rows and 0<=y<self.cols]
    def dirty_rooms(self): 
        return [(r,c) for r in range(self.rows) for c in range(self.cols) if self.grid[r][c]=='dirty']
    
    def print(self):
        for r in range(self.rows):
            print(''.join('D' if self.grid[r][c] == 'dirty' else '.' for c in range(self.cols)))
        print()

def bfs_path(env, start, end):
    if start == end: return [start]
    queue = deque([(start, [start])])
    visited = {start}
    while queue:
        current, path = queue.popleft()
        for n in env.neighbors(current):
            if n == end: return path + [n]
            if n not in visited:
                visited.add(n)
                queue.append((n, path + [n]))
    return []

class ReflexAgent:
    def __init__(self, env):
        self.env = env
        self.pos = (random.randrange(env.rows), random.randrange(env.cols))
        self.actions = []
    def run(self):
        step = 0
        while not self.env.all_clean() and step < 1000:
            step += 1
            if self.env.is_dirty(self.pos):
                self.env.clean(self.pos)
                self.actions.append(f"~ {self.pos}")
            nbrs = self.env.neighbors(self.pos)
            if nbrs:
                self.pos = random.choice(nbrs)
                self.actions.append(f"-> {self.pos}")
        return self.actions

class ModelAgent:
    def __init__(self, env):
        self.env = env
        self.pos = (random.randrange(env.rows), random.randrange(env.cols))
        self.visited = set()
        self.actions = []
    def run(self):
        step = 0
        while not self.env.all_clean():
            step += 1
            self.visited.add(self.pos)
            if self.env.is_dirty(self.pos):
                self.env.clean(self.pos)
                self.actions.append(f"~ {self.pos}")
            nbrs = self.env.neighbors(self.pos)
            unvisited = [p for p in nbrs if p not in self.visited]
            if unvisited:
                self.pos = random.choice(unvisited)
            elif nbrs:
                self.pos = random.choice(nbrs)
            self.actions.append(f"-> {self.pos}")
        return self.actions

class GoalAgent:
    def __init__(self, env):
        self.env = env
        self.path = [(r, c) for r in range(env.rows) 
                     for c in (range(env.cols) if r % 2 == 0 else reversed(range(env.cols)))]
        self.idx = 0
        self.actions = []
    def run(self):
        while not self.env.all_clean() and self.idx < len(self.path):
            self.idx += 1
            pos = self.path[self.idx - 1]
            if self.env.is_dirty(pos):
                self.env.clean(pos)
                self.actions.append(f"~ {pos}")
            else:
                self.actions.append(f"-> {pos}")
        return self.actions

class UtilityAgent:
    def __init__(self, env):
        self.env = env
        self.start = (0, 0)
        self.full_path = self.calc_full_path()
        self.idx = 0
        self.actions = []
    def calc_full_path(self):
        dirty = self.env.dirty_rooms()
        if not dirty: return []
        unvisited = set(dirty)
        current = self.start
        order = []
        while unvisited:
            nearest = min(unvisited, key=lambda x: abs(x[0] - current[0]) + abs(x[1] - current[1]))
            order.append(nearest)
            unvisited.remove(nearest)
            current = nearest
        full_path = []
        current = self.start
        for dest in order:
            path_segment = bfs_path(self.env, current, dest)
            if full_path: path_segment = path_segment[1:]
            full_path.extend(path_segment)
            current = dest
        return full_path
    def run(self):
        while not self.env.all_clean() and self.idx < len(self.full_path):
            self.idx += 1
            pos = self.full_path[self.idx - 1]
            if self.env.is_dirty(pos):
                self.env.clean(pos)
                self.actions.append(f"~ {pos}")
            else:
                self.actions.append(f"-> {pos}")
        return self.actions

def run_all_agents():
    random.seed(58)
    grid = [['dirty' if random.random() < 0.4 else 'clean' for _ in range(3)] for _ in range(2)]
    
    print("Initial Rooms:")
    for row in grid:
        print(''.join('D' if cell == 'dirty' else '.' for cell in row))
    print()
    
    agents = [(ReflexAgent, "Simple Reflex Agent"), (ModelAgent, "Model-Based Agent"), 
              (GoalAgent, "Goal-Based Agent"), (UtilityAgent, "Utility-Based Agent")]
    
    for AgentCls, name in agents:
        env = Vacuum2DEnv(grid)
        print(f"=== {name} ===")
        agent = AgentCls(env)
        for log in agent.run():
            print(log, end = " ")
        print()

if __name__ == '__main__':
    run_all_agents()