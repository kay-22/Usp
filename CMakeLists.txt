cmake_minimum_required(VERSION 3.0.0)
project(usp VERSION 0.1.0)

include(CTest)
enable_testing()

set(EXEC Usp)
set(CMAKE_CXX_STANDARD 11)
add_compile_options(-Wall -Werror -pedantic-errors)
find_package(SDL2 REQUIRED)

add_executable(${EXEC} main.cpp basics/CApp.cpp basics/CApp.h)
set_target_properties(${EXEC} PROPERTIES RUNTIME_OUTPUT_DIRECTORY ../bin)
target_link_libraries(${EXEC} mingw32 SDL2main SDL2)

set(CPACK_PROJECT_NAME ${PROJECT_NAME})
set(CPACK_PROJECT_VERSION ${PROJECT_VERSION})
include(CPack)
