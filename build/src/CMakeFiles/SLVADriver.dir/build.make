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
CMAKE_SOURCE_DIR = /mnt/d/UserAnalysisSLVA/UserAnalysisSLVA

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /mnt/d/UserAnalysisSLVA/UserAnalysisSLVA/build

# Include any dependencies generated for this target.
include src/CMakeFiles/SLVADriver.dir/depend.make

# Include the progress variables for this target.
include src/CMakeFiles/SLVADriver.dir/progress.make

# Include the compile flags for this target's objects.
include src/CMakeFiles/SLVADriver.dir/flags.make

src/CMakeFiles/SLVADriver.dir/Driver.cpp.o: src/CMakeFiles/SLVADriver.dir/flags.make
src/CMakeFiles/SLVADriver.dir/Driver.cpp.o: ../src/Driver.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/mnt/d/UserAnalysisSLVA/UserAnalysisSLVA/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object src/CMakeFiles/SLVADriver.dir/Driver.cpp.o"
	cd /mnt/d/UserAnalysisSLVA/UserAnalysisSLVA/build/src && /usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/SLVADriver.dir/Driver.cpp.o -c /mnt/d/UserAnalysisSLVA/UserAnalysisSLVA/src/Driver.cpp

src/CMakeFiles/SLVADriver.dir/Driver.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/SLVADriver.dir/Driver.cpp.i"
	cd /mnt/d/UserAnalysisSLVA/UserAnalysisSLVA/build/src && /usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /mnt/d/UserAnalysisSLVA/UserAnalysisSLVA/src/Driver.cpp > CMakeFiles/SLVADriver.dir/Driver.cpp.i

src/CMakeFiles/SLVADriver.dir/Driver.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/SLVADriver.dir/Driver.cpp.s"
	cd /mnt/d/UserAnalysisSLVA/UserAnalysisSLVA/build/src && /usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /mnt/d/UserAnalysisSLVA/UserAnalysisSLVA/src/Driver.cpp -o CMakeFiles/SLVADriver.dir/Driver.cpp.s

# Object files for target SLVADriver
SLVADriver_OBJECTS = \
"CMakeFiles/SLVADriver.dir/Driver.cpp.o"

# External object files for target SLVADriver
SLVADriver_EXTERNAL_OBJECTS =

src/SLVADriver: src/CMakeFiles/SLVADriver.dir/Driver.cpp.o
src/SLVADriver: src/CMakeFiles/SLVADriver.dir/build.make
src/SLVADriver: /usr/lib/llvm-12/lib/libLLVMCore.a
src/SLVADriver: /usr/lib/llvm-12/lib/libLLVMSupport.a
src/SLVADriver: /usr/lib/llvm-12/lib/libLLVMIRReader.a
src/SLVADriver: /usr/lib/llvm-12/lib/libLLVMPasses.a
src/SLVADriver: /usr/lib/llvm-12/lib/libLLVMTransformUtils.a
src/SLVADriver: lib/libAliasAnalysis.so
src/SLVADriver: /usr/lib/llvm-12/lib/libLLVMCoroutines.a
src/SLVADriver: /usr/lib/llvm-12/lib/libLLVMHelloNew.a
src/SLVADriver: /usr/lib/llvm-12/lib/libLLVMipo.a
src/SLVADriver: /usr/lib/llvm-12/lib/libLLVMIRReader.a
src/SLVADriver: /usr/lib/llvm-12/lib/libLLVMAsmParser.a
src/SLVADriver: /usr/lib/llvm-12/lib/libLLVMBitWriter.a
src/SLVADriver: /usr/lib/llvm-12/lib/libLLVMFrontendOpenMP.a
src/SLVADriver: /usr/lib/llvm-12/lib/libLLVMLinker.a
src/SLVADriver: /usr/lib/llvm-12/lib/libLLVMObjCARCOpts.a
src/SLVADriver: /usr/lib/llvm-12/lib/libLLVMScalarOpts.a
src/SLVADriver: /usr/lib/llvm-12/lib/libLLVMAggressiveInstCombine.a
src/SLVADriver: /usr/lib/llvm-12/lib/libLLVMInstCombine.a
src/SLVADriver: /usr/lib/llvm-12/lib/libLLVMTarget.a
src/SLVADriver: /usr/lib/llvm-12/lib/libLLVMVectorize.a
src/SLVADriver: /usr/lib/llvm-12/lib/libLLVMInstrumentation.a
src/SLVADriver: /usr/lib/llvm-12/lib/libLLVMTransformUtils.a
src/SLVADriver: /usr/lib/llvm-12/lib/libLLVMAnalysis.a
src/SLVADriver: /usr/lib/llvm-12/lib/libLLVMObject.a
src/SLVADriver: /usr/lib/llvm-12/lib/libLLVMBitReader.a
src/SLVADriver: /usr/lib/llvm-12/lib/libLLVMMCParser.a
src/SLVADriver: /usr/lib/llvm-12/lib/libLLVMTextAPI.a
src/SLVADriver: /usr/lib/llvm-12/lib/libLLVMProfileData.a
src/SLVADriver: /usr/lib/llvm-12/lib/libLLVMCore.a
src/SLVADriver: /usr/lib/llvm-12/lib/libLLVMRemarks.a
src/SLVADriver: /usr/lib/llvm-12/lib/libLLVMBitstreamReader.a
src/SLVADriver: /usr/lib/llvm-12/lib/libLLVMMC.a
src/SLVADriver: /usr/lib/llvm-12/lib/libLLVMBinaryFormat.a
src/SLVADriver: /usr/lib/llvm-12/lib/libLLVMDebugInfoCodeView.a
src/SLVADriver: /usr/lib/llvm-12/lib/libLLVMDebugInfoMSF.a
src/SLVADriver: /usr/lib/llvm-12/lib/libLLVMSupport.a
src/SLVADriver: /usr/lib/x86_64-linux-gnu/libz.so
src/SLVADriver: /usr/lib/x86_64-linux-gnu/libtinfo.so
src/SLVADriver: /usr/lib/llvm-12/lib/libLLVMDemangle.a
src/SLVADriver: /usr/local/lib/libSpatial.so
src/SLVADriver: src/CMakeFiles/SLVADriver.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=/mnt/d/UserAnalysisSLVA/UserAnalysisSLVA/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Linking CXX executable SLVADriver"
	cd /mnt/d/UserAnalysisSLVA/UserAnalysisSLVA/build/src && $(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/SLVADriver.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
src/CMakeFiles/SLVADriver.dir/build: src/SLVADriver

.PHONY : src/CMakeFiles/SLVADriver.dir/build

src/CMakeFiles/SLVADriver.dir/clean:
	cd /mnt/d/UserAnalysisSLVA/UserAnalysisSLVA/build/src && $(CMAKE_COMMAND) -P CMakeFiles/SLVADriver.dir/cmake_clean.cmake
.PHONY : src/CMakeFiles/SLVADriver.dir/clean

src/CMakeFiles/SLVADriver.dir/depend:
	cd /mnt/d/UserAnalysisSLVA/UserAnalysisSLVA/build && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /mnt/d/UserAnalysisSLVA/UserAnalysisSLVA /mnt/d/UserAnalysisSLVA/UserAnalysisSLVA/src /mnt/d/UserAnalysisSLVA/UserAnalysisSLVA/build /mnt/d/UserAnalysisSLVA/UserAnalysisSLVA/build/src /mnt/d/UserAnalysisSLVA/UserAnalysisSLVA/build/src/CMakeFiles/SLVADriver.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : src/CMakeFiles/SLVADriver.dir/depend

