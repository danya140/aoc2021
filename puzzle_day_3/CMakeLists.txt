project(puzzle_day_3)

configure_file(input.txt ${CMAKE_CURRENT_BINARY_DIR}/input.txt)

add_executable(puzzle_day_3 main.cpp ../helpers.h)