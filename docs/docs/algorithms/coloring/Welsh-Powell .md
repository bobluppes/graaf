# Welsh-Powell Graph Coloring Algorithm

The Welsh-Powell algorithm is a graph coloring algorithm used to assign colors to the vertices of an undirected graph such that no two adjacent vertices have the same color. This algorithm was introduced by Welsh and Powell in 1967 and is a simple and efficient approach for solving graph coloring problems.

## Algorithm

The Welsh-Powell algorithm follows these steps:

1. **Sort vertices:** Start by sorting the vertices of the graph in descending order based on their degrees. The vertex with the highest degree is considered first.

2. **Coloring:** Begin with the first (highest-degree) vertex. Assign it a color and mark it as "colored." Then, proceed to the next uncolored vertex in the sorted list.

3. **Color Neighbors:** For each uncolored vertex encountered, assign the lowest available color that has not been used by its already colored neighbors. This ensures that no two adjacent vertices share the same color.

4. **Repeat:** Continue this process until all vertices are colored. The resulting color assignment will be a valid graph coloring.

## Algorithm Syntax

Here's an example of the Welsh-Powell algorithm in pseudocode:

```plaintext
function WelshPowell(graph):
    sortVerticesByDegree(graph)  # Sort vertices in descending order of degree
    colors = {}  # Initialize an empty color dictionary
    
    for vertex in sortedVertices:
        usedColors = set()  # Initialize a set of colors used by neighbors
        
        # Iterate over neighbors of the current vertex
        for neighbor in graph.neighbors(vertex):
            if neighbor in colors:
                usedColors.add(colors[neighbor])
        
        # Find the lowest available color
        for color in range(len(usedColors) + 1):
            if color not in usedColors:
                colors[vertex] = color
                break
    
    return colors
