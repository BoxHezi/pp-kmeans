# CMAKE generated file: DO NOT EDIT!
# Generated by "Unix Makefiles" Generator, CMake Version 3.13

# Delete rule output on recipe failure.
.DELETE_ON_ERROR:


#=============================================================================
# Special targets provided by cmake.

# Disable implicit rules so canonical targets will work.
.SUFFIXES:


# Remove some rules from gmake that .SUFFIXES does not remove.
SUFFIXES =

.SUFFIXES: .hpux_make_needs_suffix_list


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
CMAKE_SOURCE_DIR = /home/boxhezi/Documents/Monash/FIT5124/pp-kmeans

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /home/boxhezi/Documents/Monash/FIT5124/pp-kmeans/cmake-build-debug

# Include any dependencies generated for this target.
include CMakeFiles/pp_kmeans.dir/depend.make

# Include the progress variables for this target.
include CMakeFiles/pp_kmeans.dir/progress.make

# Include the compile flags for this target's objects.
include CMakeFiles/pp_kmeans.dir/flags.make

CMakeFiles/pp_kmeans.dir/main.cpp.o: CMakeFiles/pp_kmeans.dir/flags.make
CMakeFiles/pp_kmeans.dir/main.cpp.o: ../main.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/boxhezi/Documents/Monash/FIT5124/pp-kmeans/cmake-build-debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object CMakeFiles/pp_kmeans.dir/main.cpp.o"
	/usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/pp_kmeans.dir/main.cpp.o -c /home/boxhezi/Documents/Monash/FIT5124/pp-kmeans/main.cpp

CMakeFiles/pp_kmeans.dir/main.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/pp_kmeans.dir/main.cpp.i"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/boxhezi/Documents/Monash/FIT5124/pp-kmeans/main.cpp > CMakeFiles/pp_kmeans.dir/main.cpp.i

CMakeFiles/pp_kmeans.dir/main.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/pp_kmeans.dir/main.cpp.s"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/boxhezi/Documents/Monash/FIT5124/pp-kmeans/main.cpp -o CMakeFiles/pp_kmeans.dir/main.cpp.s

CMakeFiles/pp_kmeans.dir/Point.cpp.o: CMakeFiles/pp_kmeans.dir/flags.make
CMakeFiles/pp_kmeans.dir/Point.cpp.o: ../Point.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/boxhezi/Documents/Monash/FIT5124/pp-kmeans/cmake-build-debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Building CXX object CMakeFiles/pp_kmeans.dir/Point.cpp.o"
	/usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/pp_kmeans.dir/Point.cpp.o -c /home/boxhezi/Documents/Monash/FIT5124/pp-kmeans/Point.cpp

CMakeFiles/pp_kmeans.dir/Point.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/pp_kmeans.dir/Point.cpp.i"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/boxhezi/Documents/Monash/FIT5124/pp-kmeans/Point.cpp > CMakeFiles/pp_kmeans.dir/Point.cpp.i

CMakeFiles/pp_kmeans.dir/Point.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/pp_kmeans.dir/Point.cpp.s"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/boxhezi/Documents/Monash/FIT5124/pp-kmeans/Point.cpp -o CMakeFiles/pp_kmeans.dir/Point.cpp.s

CMakeFiles/pp_kmeans.dir/Cluster.cpp.o: CMakeFiles/pp_kmeans.dir/flags.make
CMakeFiles/pp_kmeans.dir/Cluster.cpp.o: ../Cluster.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/boxhezi/Documents/Monash/FIT5124/pp-kmeans/cmake-build-debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_3) "Building CXX object CMakeFiles/pp_kmeans.dir/Cluster.cpp.o"
	/usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/pp_kmeans.dir/Cluster.cpp.o -c /home/boxhezi/Documents/Monash/FIT5124/pp-kmeans/Cluster.cpp

CMakeFiles/pp_kmeans.dir/Cluster.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/pp_kmeans.dir/Cluster.cpp.i"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/boxhezi/Documents/Monash/FIT5124/pp-kmeans/Cluster.cpp > CMakeFiles/pp_kmeans.dir/Cluster.cpp.i

CMakeFiles/pp_kmeans.dir/Cluster.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/pp_kmeans.dir/Cluster.cpp.s"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/boxhezi/Documents/Monash/FIT5124/pp-kmeans/Cluster.cpp -o CMakeFiles/pp_kmeans.dir/Cluster.cpp.s

# Object files for target pp_kmeans
pp_kmeans_OBJECTS = \
"CMakeFiles/pp_kmeans.dir/main.cpp.o" \
"CMakeFiles/pp_kmeans.dir/Point.cpp.o" \
"CMakeFiles/pp_kmeans.dir/Cluster.cpp.o"

# External object files for target pp_kmeans
pp_kmeans_EXTERNAL_OBJECTS =

pp_kmeans: CMakeFiles/pp_kmeans.dir/main.cpp.o
pp_kmeans: CMakeFiles/pp_kmeans.dir/Point.cpp.o
pp_kmeans: CMakeFiles/pp_kmeans.dir/Cluster.cpp.o
pp_kmeans: CMakeFiles/pp_kmeans.dir/build.make
pp_kmeans: CMakeFiles/pp_kmeans.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=/home/boxhezi/Documents/Monash/FIT5124/pp-kmeans/cmake-build-debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_4) "Linking CXX executable pp_kmeans"
	$(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/pp_kmeans.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
CMakeFiles/pp_kmeans.dir/build: pp_kmeans

.PHONY : CMakeFiles/pp_kmeans.dir/build

CMakeFiles/pp_kmeans.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles/pp_kmeans.dir/cmake_clean.cmake
.PHONY : CMakeFiles/pp_kmeans.dir/clean

CMakeFiles/pp_kmeans.dir/depend:
	cd /home/boxhezi/Documents/Monash/FIT5124/pp-kmeans/cmake-build-debug && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /home/boxhezi/Documents/Monash/FIT5124/pp-kmeans /home/boxhezi/Documents/Monash/FIT5124/pp-kmeans /home/boxhezi/Documents/Monash/FIT5124/pp-kmeans/cmake-build-debug /home/boxhezi/Documents/Monash/FIT5124/pp-kmeans/cmake-build-debug /home/boxhezi/Documents/Monash/FIT5124/pp-kmeans/cmake-build-debug/CMakeFiles/pp_kmeans.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : CMakeFiles/pp_kmeans.dir/depend

