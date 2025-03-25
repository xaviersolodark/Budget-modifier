set(CMAKE_CXX_STANDARD 11)
cmake_minimum_required(VERSION 3.25)

project(ChapterBudgetProgram VERSION 1.0)

include_directories(${CMAKE_SOURCE_DIR}/include)
include_directories(${CMAKE_SOURCE_DIR}/source)

add_library(TRACKER_CLASS STATIC ${CMAKE_SOURCE_DIR}/source/BudgetTracker.cpp ${CMAKE_SOURCE_DIR}/include/BudgetTracker.h)

add_executable(budget_program ${CMAKE_SOURCE_DIR}/source/main.cpp)
target_link_libraries(budget_program PRIVATE TRACKER_CLASS) 