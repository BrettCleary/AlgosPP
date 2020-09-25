add_executable(VebTests "Data Structures/VebTreeTests.cpp")
target_link_libraries(VebTests PRIVATE gtest_main AlgosPPDataStructures)
SET_TARGET_PROPERTIES(VebTests PROPERTIES LINK_FLAGS "/PROFILE")

add_executable(FibHeapTests "Data Structures/FibHeapTests.cpp")
target_link_libraries(FibHeapTests PRIVATE gtest_main AlgosPPDataStructures)
SET_TARGET_PROPERTIES(FibHeapTests PROPERTIES LINK_FLAGS "/PROFILE")

add_executable(SortTests "Sorting/SortTests.cpp")
target_link_libraries(SortTests PRIVATE gtest_main AlgosPPSorting)
SET_TARGET_PROPERTIES(SortTests PROPERTIES LINK_FLAGS "/PROFILE")

add_executable(GraphBstTests "Graph Algorithms/BstTests.cpp")
target_link_libraries(GraphBstTests PRIVATE gtest_main AlgosPPGraphBasic)
SET_TARGET_PROPERTIES(GraphBstTests PROPERTIES LINK_FLAGS "/PROFILE")

add_executable(DirGraphTests "Graph Algorithms/DirGraphRandomTests.cpp")
target_link_libraries(DirGraphTests PRIVATE gtest_main AlgosPPGraphBasic)
SET_TARGET_PROPERTIES(DirGraphTests PROPERTIES LINK_FLAGS "/PROFILE")

add_executable(MinSpanTreeTests "Graph Algorithms/MinSpanningTreeTests.cpp")
target_link_libraries(MinSpanTreeTests PRIVATE gtest_main AlgosPPGraphBasic AlgosPPGraphAdv)
SET_TARGET_PROPERTIES(MinSpanTreeTests PROPERTIES LINK_FLAGS "/PROFILE")

add_executable(ShortPathsTests "Graph Algorithms/ShortestPathsTests.cpp")
target_link_libraries(ShortPathsTests PRIVATE gtest_main AlgosPPGraphBasic AlgosPPGraphAdv)
SET_TARGET_PROPERTIES(ShortPathsTests PROPERTIES LINK_FLAGS "/PROFILE")