cmake_minimum_required(VERSION 3.22)
project(CLLVM)

include(FetchContent)
set(CMAKE_CXX_FLAGS "-Wno-trigraphs")

include_directories(include)

# Add the LLVM include directory
include_directories(/usr/local/opt/llvm/include)

# Add the LLVM library directory
link_directories(/usr/local/opt/llvm/lib)

# All files with a .cpp extension will be considered C++ source files excluding main.cpp and the files in the test directory 

file(GLOB_RECURSE SOURCES "src/*.cpp")
list(FILTER SOURCES EXCLUDE REGEX ".*main.cpp")
list(FILTER SOURCES EXCLUDE REGEX ".*test/.*")

# Add the executable
add_executable(CLLVM src/main.cpp ${SOURCES})

# Link against LLVM libraries
target_link_libraries(CLLVM LLVM)

# Add the test executable

file(GLOB_RECURSE TEST_SOURCES "src/*.cpp")
list(FILTER TEST_SOURCES EXCLUDE REGEX ".*main.cpp")

add_executable(test ${TEST_SOURCES})

# Link against LLVM libraries
target_link_libraries(test LLVM)

# Add the gtest library
FetchContent_Declare(
  googletest
  # Specify the commit you depend on and update it regularly.
  URL https://github.com/google/googletest/archive/5376968f6948923e2411081fd9372e71a59d8e77.zip
)
# For Windows: Prevent overriding the parent project's compiler/linker settings
set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)
FetchContent_MakeAvailable(googletest)

# Link against gtest
target_link_libraries(test gtest_main)