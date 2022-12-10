cmake_minimum_required(VERSION 3.9.1)

project(TicTactoe)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_FLAGS "-fdiagnostics-color=always  -Wshadow -Wall -Wno-unused-result")
#set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -D _DEBUG")
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -D _FIGHTTEST")

SET(CMAKE_COLOR_MAKEFILE ON)
# And optionally
SET(CMAKE_VERBOSE_MAKEFILE ON)


#set(CMAKE_CXX_CLANG_TIDY clang-tidy -checks=cppcoreguidelines-*, -header-filter=., -checks=-*;)

#set(CMAKE_CXX_CLANG_TIDY clang-tidy -checks=-*,readability-*, -header-filter=.*)

#Need to delete the whole build directory so that "make" command properly executes clang-tidy
set(CMAKE_CXX_CLANG_TIDY clang-tidy -checks=cppcoreguidelines-*,readability-*, -header-filter=.*)

#set(CMAKE_CXX_CLANG_TIDY "clang-tidy;-checks=google-*,cppcoreguidelines-*")

#set(-DCMAKE_EXPORT_COMPILE_COMMANDS 1) Currently only works from the command line

include_directories(includes)

file(GLOB SOURCES src/*.cpp)

# compiles the files defined by SOURCES to generante the executable defined by EXEC
add_executable(tictactoe_bin ${SOURCES})
target_compile_options(tictactoe_bin PRIVATE -Wall -Wextra -Wpedantic -Werror)
