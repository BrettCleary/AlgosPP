add_library(AlgosPPLibthree STATIC "VanEmdeBoasTree.cpp" "VanEmdeBoasTree.h")
#add_library(MyLibExampletwo STATIC "simple_lib.h" "simple_lib.cpp")
set_target_properties(AlgosPPLibthree PROPERTIES LINKER_LANGUAGE CXX)
#add_executable(demo AlgosPP.cpp)
#target_link_libraries(demo AlgosPPLib)

#target_include_directories(
#    AlgosPPLibthree
#    PUBLIC
#        ${CMAKE_CURRENT_LIST_DIR}
#    )

#link_directories(${CMAKE_SOURCE_DIR}/src)

add_executable(Testtwo VebTreeTests.cpp)
target_link_libraries(Testtwo PRIVATE gtest_main AlgosPPLibthree)
#target_link_libraries(Testtwo PRIVATE AlgosPPLibthree)
#add_test(NAME secondTest COMMAND Testtwo)

#target_link_libraries(Test gtest_main)
#add_test(NAME InsertSearchTestName COMMAND ${CMAKE_BINARY_DIR}/${CMAKE_INSTALL_BINDIR}/Test)

#target_link_libraries(example gtest_main)
#add_test(NAME example_test COMMAND example)

SET_TARGET_PROPERTIES(Testtwo PROPERTIES LINK_FLAGS "/PROFILE")