cmake_minimum_required(VERSION 3.22.1)

project(HashTable)

add_executable(HashTable main.cpp hashtable.cpp)
target_link_libraries(HashTable
   hashtable)

set(CMAKE_CXX_STANDART 11)
set(CMAKE_CXX_STANDART_REQUIRED True)

include(FetchContent)
FetchContent_Declare(
  googletest
  URL https://github.com/google/googletest/archive/609281088cfefc76f9d0ce82e1ff6c30cc3591e5.zip
)

# For Windows: Prevent overriding the parent project's compiler/linker settings
set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)
FetchContent_MakeAvailable(googletest)

enable_testing()

add_executable(
  hashtabletest
  pch.cpp
  test.cpp
)

target_link_libraries(hashtabletest
   pch.h)

include(GoogleTest)
gtest_discover_tests(hashtabletest)
