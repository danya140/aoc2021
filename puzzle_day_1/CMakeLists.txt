project(puzzle_day_1)

configure_file(input.txt ${CMAKE_CURRENT_BINARY_DIR}/input.txt)

add_executable(puzzle_day_1 main.cpp)