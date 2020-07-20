add_library(AlgosPPDataStructures STATIC "Data Structures/VanEmdeBoasTree.h" "Data Structures/VanEmdeBoasTree.cpp")
set_target_properties(AlgosPPDataStructures PROPERTIES LINKER_LANGUAGE CXX)

add_library(AlgosPPSorting STATIC "Sorting/Heapsort.h" "Sorting/Heapsort.cpp" "Sorting/InsertionSort.h" "Sorting/InsertionSort.cpp" "Sorting/Quicksort.h")
set_target_properties(AlgosPPSorting PROPERTIES LINKER_LANGUAGE CXX)