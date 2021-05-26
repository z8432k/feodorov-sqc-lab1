set(CMAKE_INCLUDE_CURRENT_DIR_IN_INTERFACE  ON)

include(GoogleTest)

find_package(GTest REQUIRED)
include_directories(${GTEST_INCLUDE_DIRS})

add_executable(tests tests.cc)
gtest_add_tests(tests "" AUTO)
target_link_libraries(tests ${GTEST_LIBRARIES} pthread GSL::gsl gauss)
