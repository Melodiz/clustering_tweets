# CMAKE generated file: DO NOT EDIT!
# Generated by "Unix Makefiles" Generator, CMake Version 3.28

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

# The shell in which to execute make rules.
SHELL = /bin/sh

# The CMake executable.
CMAKE_COMMAND = /opt/homebrew/Cellar/cmake/3.28.1/bin/cmake

# The command to remove a file.
RM = /opt/homebrew/Cellar/cmake/3.28.1/bin/cmake -E rm -f

# Escaping for special characters.
EQUALS = =

# The top-level source directory on which CMake was run.
CMAKE_SOURCE_DIR = /Users/marklyumanov/Desktop/clustering_tweets/qt

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /Users/marklyumanov/Desktop/clustering_tweets/qt/build

# Utility rule file for qt_project_autogen.

# Include any custom commands dependencies for this target.
include CMakeFiles/qt_project_autogen.dir/compiler_depend.make

# Include the progress variables for this target.
include CMakeFiles/qt_project_autogen.dir/progress.make

CMakeFiles/qt_project_autogen: qt_project_autogen/timestamp

qt_project_autogen/timestamp: /opt/homebrew/share/qt/libexec/moc
qt_project_autogen/timestamp: /opt/homebrew/share/qt/libexec/uic
qt_project_autogen/timestamp: CMakeFiles/qt_project_autogen.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --blue --bold --progress-dir=/Users/marklyumanov/Desktop/clustering_tweets/qt/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Automatic MOC and UIC for target qt_project"
	/opt/homebrew/Cellar/cmake/3.28.1/bin/cmake -E cmake_autogen /Users/marklyumanov/Desktop/clustering_tweets/qt/build/CMakeFiles/qt_project_autogen.dir/AutogenInfo.json Debug
	/opt/homebrew/Cellar/cmake/3.28.1/bin/cmake -E touch /Users/marklyumanov/Desktop/clustering_tweets/qt/build/qt_project_autogen/timestamp

qt_project_autogen: CMakeFiles/qt_project_autogen
qt_project_autogen: qt_project_autogen/timestamp
qt_project_autogen: CMakeFiles/qt_project_autogen.dir/build.make
.PHONY : qt_project_autogen

# Rule to build all files generated by this target.
CMakeFiles/qt_project_autogen.dir/build: qt_project_autogen
.PHONY : CMakeFiles/qt_project_autogen.dir/build

CMakeFiles/qt_project_autogen.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles/qt_project_autogen.dir/cmake_clean.cmake
.PHONY : CMakeFiles/qt_project_autogen.dir/clean

CMakeFiles/qt_project_autogen.dir/depend:
	cd /Users/marklyumanov/Desktop/clustering_tweets/qt/build && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /Users/marklyumanov/Desktop/clustering_tweets/qt /Users/marklyumanov/Desktop/clustering_tweets/qt /Users/marklyumanov/Desktop/clustering_tweets/qt/build /Users/marklyumanov/Desktop/clustering_tweets/qt/build /Users/marklyumanov/Desktop/clustering_tweets/qt/build/CMakeFiles/qt_project_autogen.dir/DependInfo.cmake "--color=$(COLOR)"
.PHONY : CMakeFiles/qt_project_autogen.dir/depend
