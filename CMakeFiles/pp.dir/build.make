# CMAKE generated file: DO NOT EDIT!
# Generated by "Unix Makefiles" Generator, CMake Version 3.5

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
CMAKE_SOURCE_DIR = /home/parallel/2018/PPCgrivag/ROSS

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /home/parallel/2018/PPCgrivag/ROSS-build

# Include any dependencies generated for this target.
include models/ROSS-Models/predator-prey/CMakeFiles/pp.dir/depend.make

# Include the progress variables for this target.
include models/ROSS-Models/predator-prey/CMakeFiles/pp.dir/progress.make

# Include the compile flags for this target's objects.
include models/ROSS-Models/predator-prey/CMakeFiles/pp.dir/flags.make

models/ROSS-Models/predator-prey/CMakeFiles/pp.dir/pp.c.o: models/ROSS-Models/predator-prey/CMakeFiles/pp.dir/flags.make
models/ROSS-Models/predator-prey/CMakeFiles/pp.dir/pp.c.o: /home/parallel/2018/PPCgrivag/ROSS/models/ROSS-Models/predator-prey/pp.c
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/parallel/2018/PPCgrivag/ROSS-build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building C object models/ROSS-Models/predator-prey/CMakeFiles/pp.dir/pp.c.o"
	cd /home/parallel/2018/PPCgrivag/ROSS-build/models/ROSS-Models/predator-prey && /usr/local/mpich-3.2/bin/mpicc  $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -o CMakeFiles/pp.dir/pp.c.o   -c /home/parallel/2018/PPCgrivag/ROSS/models/ROSS-Models/predator-prey/pp.c

models/ROSS-Models/predator-prey/CMakeFiles/pp.dir/pp.c.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing C source to CMakeFiles/pp.dir/pp.c.i"
	cd /home/parallel/2018/PPCgrivag/ROSS-build/models/ROSS-Models/predator-prey && /usr/local/mpich-3.2/bin/mpicc  $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -E /home/parallel/2018/PPCgrivag/ROSS/models/ROSS-Models/predator-prey/pp.c > CMakeFiles/pp.dir/pp.c.i

models/ROSS-Models/predator-prey/CMakeFiles/pp.dir/pp.c.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling C source to assembly CMakeFiles/pp.dir/pp.c.s"
	cd /home/parallel/2018/PPCgrivag/ROSS-build/models/ROSS-Models/predator-prey && /usr/local/mpich-3.2/bin/mpicc  $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -S /home/parallel/2018/PPCgrivag/ROSS/models/ROSS-Models/predator-prey/pp.c -o CMakeFiles/pp.dir/pp.c.s

models/ROSS-Models/predator-prey/CMakeFiles/pp.dir/pp.c.o.requires:

.PHONY : models/ROSS-Models/predator-prey/CMakeFiles/pp.dir/pp.c.o.requires

models/ROSS-Models/predator-prey/CMakeFiles/pp.dir/pp.c.o.provides: models/ROSS-Models/predator-prey/CMakeFiles/pp.dir/pp.c.o.requires
	$(MAKE) -f models/ROSS-Models/predator-prey/CMakeFiles/pp.dir/build.make models/ROSS-Models/predator-prey/CMakeFiles/pp.dir/pp.c.o.provides.build
.PHONY : models/ROSS-Models/predator-prey/CMakeFiles/pp.dir/pp.c.o.provides

models/ROSS-Models/predator-prey/CMakeFiles/pp.dir/pp.c.o.provides.build: models/ROSS-Models/predator-prey/CMakeFiles/pp.dir/pp.c.o


# Object files for target pp
pp_OBJECTS = \
"CMakeFiles/pp.dir/pp.c.o"

# External object files for target pp
pp_EXTERNAL_OBJECTS =

models/ROSS-Models/predator-prey/pp: models/ROSS-Models/predator-prey/CMakeFiles/pp.dir/pp.c.o
models/ROSS-Models/predator-prey/pp: models/ROSS-Models/predator-prey/CMakeFiles/pp.dir/build.make
models/ROSS-Models/predator-prey/pp: core/libROSS.a
models/ROSS-Models/predator-prey/pp: models/ROSS-Models/predator-prey/CMakeFiles/pp.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=/home/parallel/2018/PPCgrivag/ROSS-build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Linking C executable pp"
	cd /home/parallel/2018/PPCgrivag/ROSS-build/models/ROSS-Models/predator-prey && $(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/pp.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
models/ROSS-Models/predator-prey/CMakeFiles/pp.dir/build: models/ROSS-Models/predator-prey/pp

.PHONY : models/ROSS-Models/predator-prey/CMakeFiles/pp.dir/build

models/ROSS-Models/predator-prey/CMakeFiles/pp.dir/requires: models/ROSS-Models/predator-prey/CMakeFiles/pp.dir/pp.c.o.requires

.PHONY : models/ROSS-Models/predator-prey/CMakeFiles/pp.dir/requires

models/ROSS-Models/predator-prey/CMakeFiles/pp.dir/clean:
	cd /home/parallel/2018/PPCgrivag/ROSS-build/models/ROSS-Models/predator-prey && $(CMAKE_COMMAND) -P CMakeFiles/pp.dir/cmake_clean.cmake
.PHONY : models/ROSS-Models/predator-prey/CMakeFiles/pp.dir/clean

models/ROSS-Models/predator-prey/CMakeFiles/pp.dir/depend:
	cd /home/parallel/2018/PPCgrivag/ROSS-build && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /home/parallel/2018/PPCgrivag/ROSS /home/parallel/2018/PPCgrivag/ROSS/models/ROSS-Models/predator-prey /home/parallel/2018/PPCgrivag/ROSS-build /home/parallel/2018/PPCgrivag/ROSS-build/models/ROSS-Models/predator-prey /home/parallel/2018/PPCgrivag/ROSS-build/models/ROSS-Models/predator-prey/CMakeFiles/pp.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : models/ROSS-Models/predator-prey/CMakeFiles/pp.dir/depend

