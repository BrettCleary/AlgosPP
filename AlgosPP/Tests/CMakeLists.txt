add_executable(VebTests "Data Structures/VebTreeTests.cpp")
target_link_libraries(VebTests PRIVATE gtest_main AlgosPPDataStructures)
SET_TARGET_PROPERTIES(VebTests PROPERTIES LINK_FLAGS "/PROFILE")

add_executable(HeapsortTests "Sorting/HeapsortTests.cpp")
target_link_libraries(HeapsortTests PRIVATE gtest_main AlgosPPSorting)
SET_TARGET_PROPERTIES(HeapsortTests PROPERTIES LINK_FLAGS "/PROFILE")