project(puzzle_day_17)

configure_file(input.txt ${CMAKE_CURRENT_BINARY_DIR}/input.txt)
configure_file(input_example.txt ${CMAKE_CURRENT_BINARY_DIR}/input_example.txt)

add_executable(puzzle_day_17 main.cpp ../helpers.h TrajectoryCalculator.cpp TrajectoryCalculator.h)