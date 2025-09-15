import random
import os
import time

class Vacuum2DEnv:
    def __init__(self, rows, cols, dirt_prob=0.3):
        self.rows, self.cols = rows, cols
        self.grid = [['dirty' if random.random() < dirt_prob else 'clean' for _ in range(cols)] for _ in range(rows)]
    
    def is_dirty(self, pos): r, c = pos; return self.grid[r][c] == 'dirty'
    def clean(self, pos): r, c = pos; self.grid[r][c] = 'clean'
    def all_clean(self): return all(v == 'clean' for row in self.grid for v in row)
    def neighbors(self, pos): 
        r, c = pos
        d = [(r-1,c), (r+1,c), (r,c-1), (r,c+1)]
        return [(x,y) for x,y in d if 0<=x<self.rows and 0<=y<self.cols]
    def dirty_rooms(self): 
        return [(r,c) for r in range(self.rows) for c in range(self.cols) if self.grid[r][c]=='dirty']
    
    def print(self, agent=None, title=""):
        print(title)
        for r in range(self.rows):
            print(''.join('A' if agent==(r,c) else ('D' if self.grid[r][c]=='dirty' else '.') for c in range(self.cols)))
        print()

def clear_screen():
    os.system('cls' if os.name == 'nt' else 'clear')

class ReflexAgent:
    def __init__(self, env): 
        self.env, self.pos = env, (random.randrange(env.rows), random.randrange(env.cols))
        self.actions = []
        self.step = 0
    
    def run(self):
        env = self.env
        max_steps = env.rows * env.cols * 20
        
        while not env.all_clean() and self.step < max_steps:
            self.step += 1
            clear_screen()
            env.print(self.pos, f"SIMPLE REFLEX AGENT - Step {self.step}")
            time.sleep(0.5)
            
            if env.is_dirty(self.pos):
                env.clean(self.pos)
                self.actions.append(f"Step {self.step}: Cleaned {self.pos}")
            
            nbrs = env.neighbors(self.pos)
            if nbrs: 
                self.pos = random.choice(nbrs)
                self.actions.append(f"Step {self.step}: Moved to {self.pos}")
        
        return self.actions

class ModelAgent:
    def __init__(self, env): 
        self.env, self.pos, self.vis = env, (random.randrange(env.rows), random.randrange(env.cols)), set()
        self.actions = []
        self.step = 0
    
    def run(self):
        env = self.env
        
        while not env.all_clean():
            self.step += 1
            clear_screen()
            env.print(self.pos, f"MODEL-BASED AGENT - Step {self.step}")
            time.sleep(0.5)
            
            self.vis.add(self.pos)
            if env.is_dirty(self.pos):
                env.clean(self.pos)
                self.actions.append(f"Step {self.step}: Cleaned {self.pos}")
            
            n = env.neighbors(self.pos)
            unv = [p for p in n if p not in self.vis]
            if unv or n:
                self.pos = random.choice(unv if unv else n)
                self.actions.append(f"Step {self.step}: Moved to {self.pos}")
        
        return self.actions

class GoalAgent:
    def __init__(self, env):
        self.env = env
        self.path = [(r,c) for r in range(env.rows) for c in (range(env.cols) if r%2==0 else reversed(range(env.cols)))]
        self.idx = 0
        self.actions = []
    
    def run(self):
        env = self.env
        
        while not env.all_clean() and self.idx < len(self.path):
            self.idx += 1
            pos = self.path[self.idx-1]
            clear_screen()
            env.print(pos, f"GOAL-BASED AGENT - Step {self.idx}")
            time.sleep(0.5)
            
            if env.is_dirty(pos):
                env.clean(pos)
                self.actions.append(f"Step {self.idx}: Cleaned {pos}")
            else:
                self.actions.append(f"Step {self.idx}: Visited {pos}")
        
        return self.actions

class UtilityAgent:
    def __init__(self, env):
        self.env = env
        self.start = (0,0)
        self.path = self.calc_path()
        self.idx = 0
        self.actions = []
    
    def calc_path(self):
        env = self.env
        dirty = env.dirty_rooms()
        if not dirty: return []
        path, pos, unvisited = [], self.start, set(dirty)
        while unvisited:
            nearest = min(unvisited, key=lambda x: abs(pos[0]-x[0])+abs(pos[1]-x[1]))
            path.append(nearest)
            unvisited.remove(nearest)
            pos = nearest
        return path
    
    def run(self):
        env = self.env
        
        while not env.all_clean() and self.idx < len(self.path):
            self.idx += 1
            pos = self.path[self.idx-1]
            clear_screen()
            env.print(pos, f"UTILITY-BASED AGENT - Step {self.idx}")
            time.sleep(0.5)
            
            if env.is_dirty(pos):
                env.clean(pos)
                self.actions.append(f"Step {self.idx}: Cleaned {pos}")
            else:
                self.actions.append(f"Step {self.idx}: Moved to {pos}")
        
        return self.actions

def run_all_agents():
    random.seed(42)
    
    agents = [
        (ReflexAgent, "Simple Reflex Agent"),
        (ModelAgent, "Model-Based Agent"),
        (GoalAgent, "Goal-Based Agent"),
        (UtilityAgent, "Utility-Based Agent")
    ]
    
    rows, cols = 4, 5
    dirt_prob = 0.4
    all_logs = []
    performance = {}
    
    # Run each agent with animation
    for AgentClass, name in agents:
        random.seed(42)  # Same environment for fair comparison
        env = Vacuum2DEnv(rows, cols, dirt_prob)
        agent = AgentClass(env)
        actions = agent.run()
        
        all_logs.append(f"{'='*50}")
        all_logs.append(f"{name.upper()}")
        all_logs.append(f"{'='*50}")
        all_logs.extend(actions)
        all_logs.append(f"Total Actions: {len(actions)}")
        all_logs.append("")
        
        performance[name] = len(actions)
    
    # Clear screen and show all logs
    clear_screen()
    print("🤖 VACUUM CLEANER AGENTS - COMPLETE LOG")
    print("="*60)
    print()
    
    for line in all_logs:
        print(line)
    
    # Performance comparison
    print("="*60)
    print("PERFORMANCE COMPARISON")
    print("="*60)
    for name, actions in performance.items():
        print(f"{name}: {actions} actions")
    
    best_agent = min(performance.items(), key=lambda x: x[1])
    print(f"\nMost Efficient: {best_agent[0]} ({best_agent[1]} actions)")

if __name__ == '__main__':
    run_all_agents()
