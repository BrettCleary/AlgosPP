add_executable(VebTests "Data Structures/VebTreeTests.cpp")
target_link_libraries(VebTests PRIVATE gtest_main AlgosPPLibthree)
SET_TARGET_PROPERTIES(VebTests PROPERTIES LINK_FLAGS "/PROFILE")