# CMAKE generated file: DO NOT EDIT!
# Generated by "Unix Makefiles" Generator, CMake Version 3.16

# Delete rule output on recipe failure.
.DELETE_ON_ERROR:


#=============================================================================
# Special targets provided by cmake.

# Disable implicit rules so canonical targets will work.
.SUFFIXES:


# Remove some rules from gmake that .SUFFIXES does not remove.
SUFFIXES =

.SUFFIXES: .hpux_make_needs_suffix_list


# Produce verbose output by default.
VERBOSE = 1

# Suppress display of executed commands.
$(VERBOSE).SILENT:


# A target that is always out of date.
cmake_force:

.PHONY : cmake_force

#=============================================================================
# Set environment variables for the build.

# The shell in which to execute make rules.
SHELL = /bin/sh

# The CMake executable.
CMAKE_COMMAND = /usr/bin/cmake

# The command to remove a file.
RM = /usr/bin/cmake -E remove -f

# Escaping for special characters.
EQUALS = =

# The top-level source directory on which CMake was run.
CMAKE_SOURCE_DIR = /home/anarchturandot/Documents/C++/CodinGame/TicTacToe

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /home/anarchturandot/Documents/C++/CodinGame/TicTacToe/build

# Include any dependencies generated for this target.
include CMakeFiles/tictactoe_bin.dir/depend.make

# Include the progress variables for this target.
include CMakeFiles/tictactoe_bin.dir/progress.make

# Include the compile flags for this target's objects.
include CMakeFiles/tictactoe_bin.dir/flags.make

CMakeFiles/tictactoe_bin.dir/src/main.cpp.o: CMakeFiles/tictactoe_bin.dir/flags.make
CMakeFiles/tictactoe_bin.dir/src/main.cpp.o: ../src/main.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/anarchturandot/Documents/C++/CodinGame/TicTacToe/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object CMakeFiles/tictactoe_bin.dir/src/main.cpp.o"
	$(CMAKE_COMMAND) -E __run_co_compile --tidy="clang-tidy;-checks=cppcoreguidelines-*,readability-*,;-header-filter=.*" --source=/home/anarchturandot/Documents/C++/CodinGame/TicTacToe/src/main.cpp -- /usr/bin/clang++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/tictactoe_bin.dir/src/main.cpp.o -c /home/anarchturandot/Documents/C++/CodinGame/TicTacToe/src/main.cpp

CMakeFiles/tictactoe_bin.dir/src/main.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/tictactoe_bin.dir/src/main.cpp.i"
	/usr/bin/clang++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/anarchturandot/Documents/C++/CodinGame/TicTacToe/src/main.cpp > CMakeFiles/tictactoe_bin.dir/src/main.cpp.i

CMakeFiles/tictactoe_bin.dir/src/main.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/tictactoe_bin.dir/src/main.cpp.s"
	/usr/bin/clang++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/anarchturandot/Documents/C++/CodinGame/TicTacToe/src/main.cpp -o CMakeFiles/tictactoe_bin.dir/src/main.cpp.s

# Object files for target tictactoe_bin
tictactoe_bin_OBJECTS = \
"CMakeFiles/tictactoe_bin.dir/src/main.cpp.o"

# External object files for target tictactoe_bin
tictactoe_bin_EXTERNAL_OBJECTS =

tictactoe_bin: CMakeFiles/tictactoe_bin.dir/src/main.cpp.o
tictactoe_bin: CMakeFiles/tictactoe_bin.dir/build.make
tictactoe_bin: CMakeFiles/tictactoe_bin.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=/home/anarchturandot/Documents/C++/CodinGame/TicTacToe/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Linking CXX executable tictactoe_bin"
	$(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/tictactoe_bin.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
CMakeFiles/tictactoe_bin.dir/build: tictactoe_bin

.PHONY : CMakeFiles/tictactoe_bin.dir/build

CMakeFiles/tictactoe_bin.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles/tictactoe_bin.dir/cmake_clean.cmake
.PHONY : CMakeFiles/tictactoe_bin.dir/clean

CMakeFiles/tictactoe_bin.dir/depend:
	cd /home/anarchturandot/Documents/C++/CodinGame/TicTacToe/build && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /home/anarchturandot/Documents/C++/CodinGame/TicTacToe /home/anarchturandot/Documents/C++/CodinGame/TicTacToe /home/anarchturandot/Documents/C++/CodinGame/TicTacToe/build /home/anarchturandot/Documents/C++/CodinGame/TicTacToe/build /home/anarchturandot/Documents/C++/CodinGame/TicTacToe/build/CMakeFiles/tictactoe_bin.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : CMakeFiles/tictactoe_bin.dir/depend

