add_executable(VebTests "Data Structures/VebTreeTests.cpp")
target_link_libraries(VebTests PRIVATE gtest_main AlgosPPDataStructures)
SET_TARGET_PROPERTIES(VebTests PROPERTIES LINK_FLAGS "/PROFILE")

add_executable(SortTests "Sorting/SortTests.cpp")
target_link_libraries(SortTests PRIVATE gtest_main AlgosPPSorting)
SET_TARGET_PROPERTIES(SortTests PROPERTIES LINK_FLAGS "/PROFILE")