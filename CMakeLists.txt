cmake_minimum_required(VERSION 3.30)
project(DS_Wet_1)

set(CMAKE_CXX_STANDARD 14)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

include_directories(.)

# 1. Compiler Flags
add_compile_options(-Wall)
add_compile_definitions(NDEBUG)

# --- STEP 1: Create the Library (Your Logic) ---
# We bundle your classes into a library so the tester can link to them.
# Do NOT include main26a1.cpp here.
add_library(wet1_lib
        TechSystem26a1.cpp
        Student.cpp
        Course.cpp
        # Adding headers here is optional but good for IDEs
        TechSystem26a1.h
        Student.h
        Course.h
        AvlTree.h
        wet1util.h
)

# --- STEP 2: Fetch the Tester ---
include(FetchContent)
FetchContent_Declare(ds_tester
        GIT_REPOSITORY https://github.com/jamalabo1/technion-utils.git
        GIT_TAG 234218-v1-latest  # Using v1 tag for HW1
        GIT_SHALLOW TRUE
)
FetchContent_MakeAvailable(ds_tester)

# --- STEP 3: Attach the Tester ---
# This connects the downloaded tester to your 'wet1_lib'
ds_tester_attach(wet1_lib HW hw1)

# --- STEP 4: Your Own Executable ---
# The guide requires this specific target name ('techsystem26a1') for GitHub Actions to work.
add_executable(techsystem26a1 main26a1.cpp)

# This links your 'main' to the logic library we defined in Step 1
target_link_libraries(techsystem26a1 PRIVATE wet1_lib)