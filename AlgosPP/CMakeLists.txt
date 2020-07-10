# CMakeList.txt : CMake project for AlgosPP, include source and define
# project specific logic here.
#
cmake_minimum_required (VERSION 3.8)

project ("AlgosPP")

# Add source to this project's executable.
add_executable (AlgosPP "AlgosPP.cpp" "AlgosPP.h" "Data Structures/VanEmdeBoasTree.h" "Data Structures/VanEmdeBoasTree.cpp" "Tests/Data Structures/VebTreeTests.cpp" )

# TODO: Add tests and install targets if needed.
enable_testing()

add_test(Tests/Data Structures/VebTreeTests )