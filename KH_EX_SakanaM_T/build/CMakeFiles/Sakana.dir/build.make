# CMAKE generated file: DO NOT EDIT!
# Generated by "MinGW Makefiles" Generator, CMake Version 3.30

# Delete rule output on recipe failure.
.DELETE_ON_ERROR:

#=============================================================================
# Special targets provided by cmake.

# Disable implicit rules so canonical targets will work.
.SUFFIXES:

# Disable VCS-based implicit rules.
% : %,v

# Disable VCS-based implicit rules.
% : RCS/%

# Disable VCS-based implicit rules.
% : RCS/%,v

# Disable VCS-based implicit rules.
% : SCCS/s.%

# Disable VCS-based implicit rules.
% : s.%

.SUFFIXES: .hpux_make_needs_suffix_list

# Command-line flag to silence nested $(MAKE).
$(VERBOSE)MAKESILENT = -s

#Suppress display of executed commands.
$(VERBOSE).SILENT:

# A target that is always out of date.
cmake_force:
.PHONY : cmake_force

#=============================================================================
# Set environment variables for the build.

SHELL = cmd.exe

# The CMake executable.
CMAKE_COMMAND = "E:\Program Files\CMake\bin\cmake.exe"

# The command to remove a file.
RM = "E:\Program Files\CMake\bin\cmake.exe" -E rm -f

# Escaping for special characters.
EQUALS = =

# The top-level source directory on which CMake was run.
CMAKE_SOURCE_DIR = "D:\Project\VS Code\KH_EX_SakanaM_T\KH_EX_SakanaM_T"

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = "D:\Project\VS Code\KH_EX_SakanaM_T\KH_EX_SakanaM_T\build"

# Include any dependencies generated for this target.
include CMakeFiles/Sakana.dir/depend.make
# Include any dependencies generated by the compiler for this target.
include CMakeFiles/Sakana.dir/compiler_depend.make

# Include the progress variables for this target.
include CMakeFiles/Sakana.dir/progress.make

# Include the compile flags for this target's objects.
include CMakeFiles/Sakana.dir/flags.make

CMakeFiles/Sakana.dir/main.cpp.obj: CMakeFiles/Sakana.dir/flags.make
CMakeFiles/Sakana.dir/main.cpp.obj: CMakeFiles/Sakana.dir/includes_CXX.rsp
CMakeFiles/Sakana.dir/main.cpp.obj: D:/Project/VS\ Code/KH_EX_SakanaM_T/KH_EX_SakanaM_T/main.cpp
CMakeFiles/Sakana.dir/main.cpp.obj: CMakeFiles/Sakana.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green --progress-dir="D:\Project\VS Code\KH_EX_SakanaM_T\KH_EX_SakanaM_T\build\CMakeFiles" --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object CMakeFiles/Sakana.dir/main.cpp.obj"
	E:\MinGW\bin\c++.exe $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT CMakeFiles/Sakana.dir/main.cpp.obj -MF CMakeFiles\Sakana.dir\main.cpp.obj.d -o CMakeFiles\Sakana.dir\main.cpp.obj -c "D:\Project\VS Code\KH_EX_SakanaM_T\KH_EX_SakanaM_T\main.cpp"

CMakeFiles/Sakana.dir/main.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green "Preprocessing CXX source to CMakeFiles/Sakana.dir/main.cpp.i"
	E:\MinGW\bin\c++.exe $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E "D:\Project\VS Code\KH_EX_SakanaM_T\KH_EX_SakanaM_T\main.cpp" > CMakeFiles\Sakana.dir\main.cpp.i

CMakeFiles/Sakana.dir/main.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green "Compiling CXX source to assembly CMakeFiles/Sakana.dir/main.cpp.s"
	E:\MinGW\bin\c++.exe $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S "D:\Project\VS Code\KH_EX_SakanaM_T\KH_EX_SakanaM_T\main.cpp" -o CMakeFiles\Sakana.dir\main.cpp.s

CMakeFiles/Sakana.dir/src/GameManager.cpp.obj: CMakeFiles/Sakana.dir/flags.make
CMakeFiles/Sakana.dir/src/GameManager.cpp.obj: CMakeFiles/Sakana.dir/includes_CXX.rsp
CMakeFiles/Sakana.dir/src/GameManager.cpp.obj: D:/Project/VS\ Code/KH_EX_SakanaM_T/KH_EX_SakanaM_T/src/GameManager.cpp
CMakeFiles/Sakana.dir/src/GameManager.cpp.obj: CMakeFiles/Sakana.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green --progress-dir="D:\Project\VS Code\KH_EX_SakanaM_T\KH_EX_SakanaM_T\build\CMakeFiles" --progress-num=$(CMAKE_PROGRESS_2) "Building CXX object CMakeFiles/Sakana.dir/src/GameManager.cpp.obj"
	E:\MinGW\bin\c++.exe $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT CMakeFiles/Sakana.dir/src/GameManager.cpp.obj -MF CMakeFiles\Sakana.dir\src\GameManager.cpp.obj.d -o CMakeFiles\Sakana.dir\src\GameManager.cpp.obj -c "D:\Project\VS Code\KH_EX_SakanaM_T\KH_EX_SakanaM_T\src\GameManager.cpp"

CMakeFiles/Sakana.dir/src/GameManager.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green "Preprocessing CXX source to CMakeFiles/Sakana.dir/src/GameManager.cpp.i"
	E:\MinGW\bin\c++.exe $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E "D:\Project\VS Code\KH_EX_SakanaM_T\KH_EX_SakanaM_T\src\GameManager.cpp" > CMakeFiles\Sakana.dir\src\GameManager.cpp.i

CMakeFiles/Sakana.dir/src/GameManager.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green "Compiling CXX source to assembly CMakeFiles/Sakana.dir/src/GameManager.cpp.s"
	E:\MinGW\bin\c++.exe $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S "D:\Project\VS Code\KH_EX_SakanaM_T\KH_EX_SakanaM_T\src\GameManager.cpp" -o CMakeFiles\Sakana.dir\src\GameManager.cpp.s

# Object files for target Sakana
Sakana_OBJECTS = \
"CMakeFiles/Sakana.dir/main.cpp.obj" \
"CMakeFiles/Sakana.dir/src/GameManager.cpp.obj"

# External object files for target Sakana
Sakana_EXTERNAL_OBJECTS =

Sakana.exe: CMakeFiles/Sakana.dir/main.cpp.obj
Sakana.exe: CMakeFiles/Sakana.dir/src/GameManager.cpp.obj
Sakana.exe: CMakeFiles/Sakana.dir/build.make
Sakana.exe: CMakeFiles/Sakana.dir/linkLibs.rsp
Sakana.exe: CMakeFiles/Sakana.dir/objects1.rsp
Sakana.exe: CMakeFiles/Sakana.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green --bold --progress-dir="D:\Project\VS Code\KH_EX_SakanaM_T\KH_EX_SakanaM_T\build\CMakeFiles" --progress-num=$(CMAKE_PROGRESS_3) "Linking CXX executable Sakana.exe"
	$(CMAKE_COMMAND) -E cmake_link_script CMakeFiles\Sakana.dir\link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
CMakeFiles/Sakana.dir/build: Sakana.exe
.PHONY : CMakeFiles/Sakana.dir/build

CMakeFiles/Sakana.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles\Sakana.dir\cmake_clean.cmake
.PHONY : CMakeFiles/Sakana.dir/clean

CMakeFiles/Sakana.dir/depend:
	$(CMAKE_COMMAND) -E cmake_depends "MinGW Makefiles" "D:\Project\VS Code\KH_EX_SakanaM_T\KH_EX_SakanaM_T" "D:\Project\VS Code\KH_EX_SakanaM_T\KH_EX_SakanaM_T" "D:\Project\VS Code\KH_EX_SakanaM_T\KH_EX_SakanaM_T\build" "D:\Project\VS Code\KH_EX_SakanaM_T\KH_EX_SakanaM_T\build" "D:\Project\VS Code\KH_EX_SakanaM_T\KH_EX_SakanaM_T\build\CMakeFiles\Sakana.dir\DependInfo.cmake" "--color=$(COLOR)"
.PHONY : CMakeFiles/Sakana.dir/depend

