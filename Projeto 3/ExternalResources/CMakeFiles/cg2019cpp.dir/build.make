# CMAKE generated file: DO NOT EDIT!
# Generated by "Unix Makefiles" Generator, CMake Version 3.14

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
CMAKE_COMMAND = /usr/local/bin/cmake

# The command to remove a file.
RM = /usr/local/bin/cmake -E remove -f

# Escaping for special characters.
EQUALS = =

# The top-level source directory on which CMake was run.
CMAKE_SOURCE_DIR = "/home/gabriel/Documentos/CGI/Projeto 3"

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = "/home/gabriel/Documentos/CGI/Projeto 3"

# Include any dependencies generated for this target.
include ExternalResources/CMakeFiles/cg2019cpp.dir/depend.make

# Include the progress variables for this target.
include ExternalResources/CMakeFiles/cg2019cpp.dir/progress.make

# Include the compile flags for this target's objects.
include ExternalResources/CMakeFiles/cg2019cpp.dir/flags.make

ExternalResources/CMakeFiles/cg2019cpp.dir/src/OBJ_Loader.cpp.o: ExternalResources/CMakeFiles/cg2019cpp.dir/flags.make
ExternalResources/CMakeFiles/cg2019cpp.dir/src/OBJ_Loader.cpp.o: ExternalResources/src/OBJ_Loader.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir="/home/gabriel/Documentos/CGI/Projeto 3/CMakeFiles" --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object ExternalResources/CMakeFiles/cg2019cpp.dir/src/OBJ_Loader.cpp.o"
	cd "/home/gabriel/Documentos/CGI/Projeto 3/ExternalResources" && /usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/cg2019cpp.dir/src/OBJ_Loader.cpp.o -c "/home/gabriel/Documentos/CGI/Projeto 3/ExternalResources/src/OBJ_Loader.cpp"

ExternalResources/CMakeFiles/cg2019cpp.dir/src/OBJ_Loader.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/cg2019cpp.dir/src/OBJ_Loader.cpp.i"
	cd "/home/gabriel/Documentos/CGI/Projeto 3/ExternalResources" && /usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E "/home/gabriel/Documentos/CGI/Projeto 3/ExternalResources/src/OBJ_Loader.cpp" > CMakeFiles/cg2019cpp.dir/src/OBJ_Loader.cpp.i

ExternalResources/CMakeFiles/cg2019cpp.dir/src/OBJ_Loader.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/cg2019cpp.dir/src/OBJ_Loader.cpp.s"
	cd "/home/gabriel/Documentos/CGI/Projeto 3/ExternalResources" && /usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S "/home/gabriel/Documentos/CGI/Projeto 3/ExternalResources/src/OBJ_Loader.cpp" -o CMakeFiles/cg2019cpp.dir/src/OBJ_Loader.cpp.s

ExternalResources/CMakeFiles/cg2019cpp.dir/src/cg_window.cpp.o: ExternalResources/CMakeFiles/cg2019cpp.dir/flags.make
ExternalResources/CMakeFiles/cg2019cpp.dir/src/cg_window.cpp.o: ExternalResources/src/cg_window.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir="/home/gabriel/Documentos/CGI/Projeto 3/CMakeFiles" --progress-num=$(CMAKE_PROGRESS_2) "Building CXX object ExternalResources/CMakeFiles/cg2019cpp.dir/src/cg_window.cpp.o"
	cd "/home/gabriel/Documentos/CGI/Projeto 3/ExternalResources" && /usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/cg2019cpp.dir/src/cg_window.cpp.o -c "/home/gabriel/Documentos/CGI/Projeto 3/ExternalResources/src/cg_window.cpp"

ExternalResources/CMakeFiles/cg2019cpp.dir/src/cg_window.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/cg2019cpp.dir/src/cg_window.cpp.i"
	cd "/home/gabriel/Documentos/CGI/Projeto 3/ExternalResources" && /usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E "/home/gabriel/Documentos/CGI/Projeto 3/ExternalResources/src/cg_window.cpp" > CMakeFiles/cg2019cpp.dir/src/cg_window.cpp.i

ExternalResources/CMakeFiles/cg2019cpp.dir/src/cg_window.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/cg2019cpp.dir/src/cg_window.cpp.s"
	cd "/home/gabriel/Documentos/CGI/Projeto 3/ExternalResources" && /usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S "/home/gabriel/Documentos/CGI/Projeto 3/ExternalResources/src/cg_window.cpp" -o CMakeFiles/cg2019cpp.dir/src/cg_window.cpp.s

# Object files for target cg2019cpp
cg2019cpp_OBJECTS = \
"CMakeFiles/cg2019cpp.dir/src/OBJ_Loader.cpp.o" \
"CMakeFiles/cg2019cpp.dir/src/cg_window.cpp.o"

# External object files for target cg2019cpp
cg2019cpp_EXTERNAL_OBJECTS =

ExternalResources/libcg2019cpp.a: ExternalResources/CMakeFiles/cg2019cpp.dir/src/OBJ_Loader.cpp.o
ExternalResources/libcg2019cpp.a: ExternalResources/CMakeFiles/cg2019cpp.dir/src/cg_window.cpp.o
ExternalResources/libcg2019cpp.a: ExternalResources/CMakeFiles/cg2019cpp.dir/build.make
ExternalResources/libcg2019cpp.a: ExternalResources/CMakeFiles/cg2019cpp.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir="/home/gabriel/Documentos/CGI/Projeto 3/CMakeFiles" --progress-num=$(CMAKE_PROGRESS_3) "Linking CXX static library libcg2019cpp.a"
	cd "/home/gabriel/Documentos/CGI/Projeto 3/ExternalResources" && $(CMAKE_COMMAND) -P CMakeFiles/cg2019cpp.dir/cmake_clean_target.cmake
	cd "/home/gabriel/Documentos/CGI/Projeto 3/ExternalResources" && $(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/cg2019cpp.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
ExternalResources/CMakeFiles/cg2019cpp.dir/build: ExternalResources/libcg2019cpp.a

.PHONY : ExternalResources/CMakeFiles/cg2019cpp.dir/build

ExternalResources/CMakeFiles/cg2019cpp.dir/clean:
	cd "/home/gabriel/Documentos/CGI/Projeto 3/ExternalResources" && $(CMAKE_COMMAND) -P CMakeFiles/cg2019cpp.dir/cmake_clean.cmake
.PHONY : ExternalResources/CMakeFiles/cg2019cpp.dir/clean

ExternalResources/CMakeFiles/cg2019cpp.dir/depend:
	cd "/home/gabriel/Documentos/CGI/Projeto 3" && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" "/home/gabriel/Documentos/CGI/Projeto 3" "/home/gabriel/Documentos/CGI/Projeto 3/ExternalResources" "/home/gabriel/Documentos/CGI/Projeto 3" "/home/gabriel/Documentos/CGI/Projeto 3/ExternalResources" "/home/gabriel/Documentos/CGI/Projeto 3/ExternalResources/CMakeFiles/cg2019cpp.dir/DependInfo.cmake" --color=$(COLOR)
.PHONY : ExternalResources/CMakeFiles/cg2019cpp.dir/depend
