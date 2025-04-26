# Tower of Hanoi (4 Pegs - Reve's Puzzle)

Solve the 4-peg Tower of Hanoi puzzle using:
- **Divide and Conquer (DAC)**
- **Dynamic Programming (DP)** based on Frame-Stewart heuristic.

The DP method finds the optimal solution in **33 moves** for **8 disks**.

## Features
- Supports solving the 4-peg Tower of Hanoi for any number of disks.
- Compares two strategies: **DAC** (simple) vs **DP** (optimal).
- Uses **memoization** for fast computations.

## Problem Rules
- Move only **one disk** at a time.
- A larger disk **cannot** be placed on a smaller disk.
- All disks start on the **first peg**, ordered largest to smallest.

## Methods
### Divide and Conquer (DAC)
- Recursively moves `n-2` disks.
- Simple but **not optimal** (49 moves for 8 disks).

### Dynamic Programming (DP)
- Applies the **Frame-Stewart** strategy.
- Finds the **minimum number of moves** (33 moves for 8 disks).
- Stores optimal moves and `k` values for efficiency.

## How to Run
```bash
g++ main.cpp TowerOfHanoi.cpp -o TowerOfHanoi
./TowerOfHanoi
```

## Files
- `main.cpp` — Main program to run the solution.
- `TowerOfHanoi.h` — Header with class/function declarations.
- `TowerOfHanoi.cpp` — Implementation of solving methods.

## Results
| Method | Moves (8 disks) | Optimal |
|:------:|:---------------:|:-------:|
| DAC    | 49              | ❌      |
| DP     | 33              | ✅      |

## Conclusion
- **DP method** solves the problem **optimally** and scales for larger numbers of disks.
- **DAC method** is simpler but inefficient for optimal solutions.