# A* Search Algorithm in C++

This program implements the A* search algorithm to find the shortest path between cities in a weighted graph, where each node represents a city, and edges represent the cost of traveling between cities.

## Features

- **Node and Edge Representation**: Each city is represented as a `Nodo`, and each connection between cities is an `Arista`.
- **Heuristic Function**: Each node has a heuristic value (`puntaje_h`), which represents the estimated cost to reach the goal city.
- **A* Algorithm**: The `A_Estrella` function implements the A* search algorithm to find the optimal path from a start city to a goal city.
- **Path Printing**: Once the algorithm finishes, the program prints the path from the start city to the goal city.

## Code Structure

The main components of the program are:

- **Nodo**: Represents a city with its name, heuristic value (`puntaje_h`), cost from the start (`puntaje_g`), and total estimated cost (`puntaje_f = puntaje_g + puntaje_h`).
- **Arista**: Represents a connection between two cities, including the cost of travel.
- **Lista**: A linked list used to manage priority queues and explored nodes during the search.
- **A_Estrella**: The function implementing the A* algorithm to find the shortest path between the start and goal cities.

## Usage

1. **Adding Nodes**: Each city is added using the `AgregaNodo` function, which initializes the city name and its heuristic value.
2. **Associating Edges**: The `AsociaArista` function connects two cities with a given travel cost.
3. **Running A* Algorithm**: The `A_Estrella` function is called with a start city and a goal city to compute the optimal path.
4. **Displaying the Path**: The path found by the algorithm is printed with the `ImprimeCamino` function.

## Example

In this example, the program calculates the shortest path from **Arad** to **Bucharest** using the A* algorithm.

```cpp
int main(void)
{
    // Create and connect cities
    nodo_ptr_t Arad = new Nodo();
    AgregaNodo(Arad, "Arad", 366);
    nodo_ptr_t Bucharest = new Nodo();
    AgregaNodo(Bucharest, "Bucharest", 0);

    // Add connections (edges)
    AsociaArista(Arad, Bucharest, 75);

    // Run A* algorithm
    A_Estrella(Arad, Bucharest);

    // Print the shortest path
    ImprimeCamino(Bucharest);

    return 0;
}
```

## How It Works

- **A* Algorithm**: A priority queue (`col_prio`) is used to explore nodes based on their `puntaje_f`. The algorithm iteratively explores the city with the lowest `puntaje_f`, updates its neighbors, and continues until it reaches the goal city.
- **Heuristic**: The heuristic function (the second parameter in `AgregaNodo`) estimates the remaining distance to the goal city. For instance, in the example, `366` is the heuristic estimate from Arad to Bucharest.
  
## Output

After running the program, the console will display the cities visited in the shortest path, for example:

```
Camino de Arad hacia Bucharest: 
Arad, Bucharest.
```

## Dependencies

The program uses basic C++ libraries like `iostream`, `vector`, and `list`. No external dependencies are required.

## Compilation

To compile and run the program, use the following commands:

```bash
g++ -o a-estrella a-estrella.cpp
./a-estrella
```
