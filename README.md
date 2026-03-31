# GRASP-based Weighted Graph Coloring

## Overview

This project implements a **GRASP (Greedy Randomized Adaptive Search Procedure)** metaheuristic to solve a **Weighted Graph Coloring** problem.

The goal is to color the vertices of a graph using a fixed number of colors while minimizing the **maximum color weight**, where each vertex has an associated weight and the weight of a color is the sum of weights of vertices assigned to it.

This is a typical **combinatorial optimization / NP-hard** problem, approached here using:

• Greedy randomized construction
• Local search via neighbourhood exploration
• Iterative improvement under a time limit

---

## Problem Definition

Given:

• A graph ( G = (V, E) )
• A weight ( w(v) ) for each vertex
• A fixed number of colors ( k )

Find a valid coloring such that:

1. Adjacent vertices cannot share the same color.
2. The objective function is minimized:

[
\min \max_{c \in Colors} \sum_{v \in color(c)} w(v)
]

This is known as the **Min-Max Weighted Coloring Problem**.

---

## Algorithm Summary

Each GRASP iteration performs:

### 1) Greedy Construction Phase

Implemented in `greedy.cpp`

Builds a feasible coloring using:

* Priority queue based on node degree
* Randomized tie-breaking
* Dynamic recoloring when no feasible color exists

The heuristic tries to assign the **lowest total weight color available**.

### 2) Local Search Phase

Implemented in `neighbours.cpp`

Explores the neighbourhood by:

* Trying pairwise recoloring of nodes
* Evaluating swaps and recolorings
* Accepting moves that reduce the maximum color weight

This continues until no improving neighbour is found.

### 3) GRASP Iteration Loop

Implemented in `grasp.cpp`

The process repeats until:

* Time limit is reached
* The theoretical lower bound (max vertex weight) is achieved

The best solution found across iterations is returned.

---

## Project Structure

```
.
├── main.cpp
├── grasp.cpp / grasp.hpp
├── greedy.cpp / greedy.hpp
├── neighbours.cpp / neighbours.hpp
├── utils.cpp / utils.hpp
```

### File Responsibilities

main.cpp
• Input parsing
• Graph construction
• GRASP execution loop
• Output writing

utils.*
• Color availability tracking
• Node recoloring operations
• Auxiliary utilities and hashing

greedy.*
• Greedy randomized construction heuristic

neighbours.*
• Local search and neighbourhood evaluation

grasp.*
• Integration of greedy + local search

---

## Building

Requires a C++ compiler supporting C++11 or newer.

Compile with:

```bash
g++ -O3 -std=c++11 *.cpp -o cmb
```

---

## Running

```bash
./cmb <output_file> <time_in_seconds> <seed>
```

Arguments:

| Argument        | Description                          |
| --------------- | ------------------------------------ |
| output_file     | File where final solution is written |
| time_in_seconds | Execution time limit                 |
| seed            | Random seed                          |

If parameters are omitted:

* Default time = 60 seconds
* Default seed = current time

Example:

```bash
./cmb result.txt 120 42
```

---

## Input Format (STDIN)

The program reads the instance from **standard input**.

Format:

```
<number_of_nodes>
<number_of_edges>
<number_of_colors>
<w1 w2 w3 ... wn>
<u1 v1>
<u2 v2>
...
<um vm>
```

Where:

* Nodes are indexed from **0 to n-1**
* Edges are **undirected**

Example:

```
5
6
3
4.5 2.1 3.0 5.2 1.8
0 1
0 2
1 2
1 3
2 4
3 4
```

---

## Output

Results are printed to console and written to the output file.

Output format:

```
finalMaxValue: <value>
coloration:
c0 c1 c2 ... cn
```

Where:

* `finalMaxValue` is the objective function value
* `ci` is the color assigned to node i

---

## Key Implementation Details

• Adjacency stored both as:

* adjacency lists
* hash set for O(1) edge lookup

• Color feasibility tracked via matrix:

```
availableColors[node][color]
```

• Objective updates done incrementally for performance.

• Multiple GRASP iterations improve robustness.

---

## Notes

This implementation is designed for experimentation and research in:

* Metaheuristics
* Graph coloring
* Combinatorial optimization

Performance strongly depends on:

* Time limit
* Instance size and density
