cmake_minimum_required(VERSION 3.20)

project(SCMS VERSION 0.1.0 LANGUAGES CXX)

# C++ standard
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

option(BUILD_TESTS "Build SCMS tests" ON)

# Warnings
if(MSVC)
  add_compile_options(/W4 /permissive-)
else()
  add_compile_options(-Wall -Wextra -Wpedantic)
endif()

# Include directory
set(SCMS_INCLUDE_DIR ${CMAKE_CURRENT_SOURCE_DIR}/include)

include(GNUInstallDirs)

# Core sources (exclude main.cpp)
set(SCMS_CORE_SOURCES
  src/Person.cpp
  src/User.cpp
  src/Student.cpp
  src/Teacher.cpp
  src/Admin.cpp
  src/Logger.cpp
  src/utils.cpp
  src/AuthManager.cpp
  src/Course.cpp
  src/CourseManager.cpp
  src/AttendanceRecord.cpp
  src/AttendanceManager.cpp
  src/Exam.cpp
  src/ExamManager.cpp
  src/Book.cpp
  src/LibraryManager.cpp
)

add_library(scms_core STATIC ${SCMS_CORE_SOURCES})
target_include_directories(scms_core PUBLIC ${SCMS_INCLUDE_DIR})
target_compile_features(scms_core PUBLIC cxx_std_20)

# Link stdc++fs for older GCC (filesystem pre-9)
if(CMAKE_CXX_COMPILER_ID STREQUAL "GNU" AND CMAKE_CXX_COMPILER_VERSION VERSION_LESS 9.0)
  target_link_libraries(scms_core PUBLIC stdc++fs)
endif()

# Main application
add_executable(scms src/main.cpp)
target_link_libraries(scms PRIVATE scms_core)
target_include_directories(scms PRIVATE ${SCMS_INCLUDE_DIR})

# Tests (main-based; each is a separate executable)
if(BUILD_TESTS)
  enable_testing()

  set(SCMS_TESTS
    test_auth
    test_course
    test_attendance
    test_exam
    test_library
  )

  foreach(T IN LISTS SCMS_TESTS)
    add_executable(${T} tests/${T}.cpp)
    target_link_libraries(${T} PRIVATE scms_core)
    target_include_directories(${T} PRIVATE ${SCMS_INCLUDE_DIR})

    # Register with CTest so `ctest` can run them
    add_test(NAME ${T} COMMAND ${T})
  endforeach()
endif()
