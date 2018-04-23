cmake_minimum_required(VERSION 3.2)

project(main)

set(CMAKE_CXX_STANDARD 14)

###########################################################################
# cmake flags
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -Wextra -Werror")

find_package(libcluon REQUIRED)

include_directories(SYSTEM ${CLUON_INCLUDE_DIRS})

add_executable(${PROJECT_NAME} ${CMAKE_CURRENT_SOURCE_DIR}/src/V2VService.cpp)

target_link_libraries(${PROJECT_NAME} ${CLUON_LIBRARIES})

###########################################################################
# Get source files to run the tools.
file(GLOB_RECURSE ALL_SOURCES *.[ch]pp *.cc *.[ch])

###########################################################################
# Adding cppcheck target if executable is found
find_program(CPPCHECK "cppcheck")
if(CPPCHECK)
  add_custom_target(
    cppcheck
    COMMAND /usr/bin/cppcheck
        --enable=warning, style, performance, portability, information, unusedFunction
        --template=gcc
        --inline-suppr
        --library=gnu.cfg
        --library=posix.cfg
        --std=posix --std=c++11 --quiet
    ${ALL_SOURCES})
endif()

###########################################################################
# Adding valgrind target if executable is found
find_program(VALGRIND "valgrind")
if(VALGRIND)
  add_custom_target(
    test_memcheck
    COMMAND ${CMAKE_CTEST_COMMAND} 
        --force-new-ctest-process --test-action memcheck
    COMMAND cat "${CMAKE_BINARY_DIR}/Testing/Temporary/MemoryChecker.*.log")
endif()


