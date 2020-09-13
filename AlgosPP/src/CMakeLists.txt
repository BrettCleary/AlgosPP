add_library(AlgosPPDataStructures STATIC "Data Structures/VanEmdeBoasTree.h" "Data Structures/VanEmdeBoasTree.cpp")
set_target_properties(AlgosPPDataStructures PROPERTIES LINKER_LANGUAGE CXX)
set_target_properties(AlgosPPDataStructures PROPERTIES VERSION "1.0.0")
set_target_properties(AlgosPPDataStructures PROPERTIES SOVERSION "1")

add_library(AlgosPPSorting STATIC "Sorting/Heapsort.h" "Sorting/Heapsort.cpp" "Sorting/InsertionSort.h" "Sorting/InsertionSort.cpp" "Sorting/Quicksort.h" "Sorting/Introsort.h")
set_target_properties(AlgosPPSorting PROPERTIES LINKER_LANGUAGE CXX)
set_target_properties(AlgosPPSorting PROPERTIES VERSION "1.0.0")
set_target_properties(AlgosPPSorting PROPERTIES SOVERSION "1")

add_library(AlgosPPGraph STATIC "Graph Algorithms/BreadthFirstSearch.h" "Graph Algorithms/BreadthFirstSearch.cpp" "Graph Algorithms/Graph.h" "Graph Algorithms/Graph.cpp" 
"Graph Algorithms/DepthFirstSearch.h" "Graph Algorithms/DepthFirstSearch.cpp" "Graph Algorithms/TopologicalSort.h" "Graph Algorithms/TopologicalSort.cpp" 
"Graph Algorithms/StronglyConnectedComponents.h" "Graph Algorithms/StronglyConnectedComponents.cpp" "Graph Algorithms/PrimsMST.h" "Graph Algorithms/PrimsMST.cpp"
"Graph Algorithms/BellmanFord.h" "Graph Algorithms/BellmanFord.cpp" "Graph Algorithms/Dijkstras.h" "Graph Algorithms/Dijkstras.cpp" "Graph Algorithms/FloydWarshall.cpp" "Graph Algorithms/FloydWarshall.h" "Graph Algorithms/JohnsonAllPairs.cpp" "Graph Algorithms/JohnsonAllPairs.h")
set_target_properties(AlgosPPGraph PROPERTIES LINKER_LANGUAGE CXX)
set_target_properties(AlgosPPGraph PROPERTIES VERSION "1.0.0")
set_target_properties(AlgosPPGraph PROPERTIES SOVERSION "1")