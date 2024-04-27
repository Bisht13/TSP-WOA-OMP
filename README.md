# Traveling Salesman Problem Optimized with Whale Optimization Algorithm Using OMP

The Traveling Salesman Problem (TSP) is a classic algorithmic problem in the field of computer science and operations research. It involves finding the shortest possible route that visits a set of cities exactly once and returns to the origin city. This problem is NP-hard, meaning that no efficient solution exists for solving all instances of the problem. However, various optimization algorithms can be used to find approximate solutions for large instances in a reasonable amount of time.

## Whale Optimization Algorithm (WOA)

The Whale Optimization Algorithm is a relatively new bio-inspired metaheuristic algorithm that mimics the social behavior of humpback whales. It is used for solving optimization problems. The algorithm is characterized by its unique hunting method, known as the bubble-net feeding method, which involves creating bubbles in a spiral shape to encircle prey.

## Using OMP for Parallelization

OpenMP (Open Multi-Processing) is an API that supports multi-platform shared memory multiprocessing programming in C, C++, and Fortran on most processor architectures and operating systems. It consists of a set of compiler directives, library routines, and environment variables that influence run-time behavior. OMP is used in this context to parallelize the WOA for the TSP, allowing for faster computation by utilizing multiple processors simultaneously.

## Implementation Overview

The implementation involves the following key components:

1. **Distance Matrix Generation**: A matrix representing the distances between each pair of cities is generated. This matrix serves as the input for the optimization process.

2. **Initial Population**: A set of candidate solutions (paths) is generated randomly. Each path represents a possible solution to the TSP.

3. **Fitness Evaluation**: The fitness of each candidate solution is evaluated based on the total distance of the path. The objective is to minimize this distance.

4. **WOA Operators**: The algorithm applies two main operators - encircling prey and bubble-net attacking method. These operators are used to update the positions (solutions) in the search space towards the best current solution.

5. **Parallelization with OMP**: The fitness evaluation of the population and the application of WOA operators are parallelized using OMP directives to enhance performance.

6. **Iteration**: The process of fitness evaluation and applying WOA operators is repeated for a set number of iterations or until a convergence criterion is met.

7. **Result**: The best solution found during the iterations is presented as the output, which is the shortest path that visits all cities and returns to the origin.

## How to Run the Implementation

To run this implementation of the Traveling Salesman Problem optimized with the Whale Optimization Algorithm using OMP, follow these steps:

1. **Prerequisites**:
   - Ensure you have a C++ compiler installed that supports OpenMP. GCC (G++ compiler) is recommended.
   - Install OpenMP if it is not already available on your system. On Linux, you can install it using your package manager, for example, `sudo apt-get install libomp-dev` for Ubuntu.

2. **Compile the Program**:
   - Open a terminal or command prompt.
   - Navigate to the directory containing the `tsp_woa.cpp` file.
   - Compile the program using the following command:
     ```
     g++ -fopenmp tsp_woa.cpp -o tsp_woa
     ```
     This command tells the compiler to use the OpenMP library and compiles the `tsp_woa.cpp` file into an executable named `tsp_woa`.

3. **Prepare the Data File**:
   - Ensure you have a data file containing the distance matrix for the cities. The file should be formatted as shown in `data/data_1.txt` or `data/data_2.txt`.
   - Place the data file in the same directory as the executable or specify the path to the file when running the program.

4. **Run the Program**:
   - Execute the program by running the following command in the terminal:
     ```
     ./tsp_woa
     ```
   - If your data file is named differently or located in a different directory, you may need to modify the `filename` variable in the `main` function of `tsp_woa.cpp` accordingly.

5. **View the Results**:
   - After the program finishes running, it will output the optimal path found and the total distance of that path.
   - The output will be displayed in the terminal.

By following these steps, you can run the TSP optimization using the Whale Optimization Algorithm and OpenMP for parallel processing to find a near-optimal solution to the problem.

## Advantages of Using WOA with OMP for TSP

- **Efficiency**: Parallelization with OMP significantly reduces the computation time, making it feasible to solve larger instances of the TSP.
- **Simplicity**: The WOA algorithm is simple to understand and implement, yet powerful in finding good solutions.
- **Flexibility**: The algorithm can be easily adapted and combined with other optimization techniques to improve solution quality.

## Conclusion

The combination of the Whale Optimization Algorithm with OMP parallelization presents a powerful approach to solving the Traveling Salesman Problem. By leveraging the natural hunting strategies of whales and the computational power of modern processors, it is possible to find near-optimal solutions to this classic problem in a fraction of the time required by traditional methods.
