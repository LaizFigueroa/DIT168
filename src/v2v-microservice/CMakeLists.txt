# Copyright (C) 2018 DIT168 - Group 13
#
# This program is free software: you can redistribute it and/or modify
# it under the terms of the GNU General Public License as published by
# the Free Software Foundation, either version 3 of the License, or
# (at your option) any later version.
#
# This program is distributed in the hope that it will be useful,
# but WITHOUT ANY WARRANTY; without even the implied warranty of
# MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
# GNU General Public License for more details.
#
# You should have received a copy of the GNU General Public License
# along with this program.  If not, see <http://www.gnu.org/licenses/>.

cmake_minimum_required(VERSION 3.5)

project(V2VService)

set(CMAKE_CXX_STANDARD 14)

# Strip unneeded symbols from binaries.
set(CMAKE_CXX_FLAGS_RELEASE "${CMAKE_CXX_FLAGS_RELEASE} -s")

# Build a static binary.
set(CMAKE_EXE_LINKER_FLAGS "-static-libgcc -static-libstdc++")

#set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -Wextra -Werror")


find_package(libcluon REQUIRED)
include_directories(SYSTEM ${CLUON_INCLUDE_DIRS})

add_custom_command(OUTPUT ${CMAKE_BINARY_DIR}/messages.cpp
                   WORKING_DIRECTORY ${CMAKE_BINARY_DIR}
                   COMMAND cluon-msc --cpp-sources --cpp-add-include-file=messages.hpp --out=${CMAKE_BINARY_DIR}/messages.cpp ${CMAKE_CURRENT_SOURCE_DIR}/messages.odvd
                   COMMAND cluon-msc --cpp-headers --out=${CMAKE_BINARY_DIR}/messages.hpp ${CMAKE_CURRENT_SOURCE_DIR}/messages.odvd
                   DEPENDS ${CMAKE_CURRENT_SOURCE_DIR}/messages.odvd)
include_directories(SYSTEM ${CMAKE_BINARY_DIR})

################################################################################
# Create executable.

add_executable(${PROJECT_NAME} ${CMAKE_CURRENT_SOURCE_DIR}/V2VService.cpp ${CMAKE_BINARY_DIR}/messages.cpp)
target_link_libraries(${PROJECT_NAME} ${CLUON_LIBRARIES})

################################################################################
# Install executable.
install(TARGETS ${PROJECT_NAME} DESTINATION bin COMPONENT ${PROJECT_NAME})

# enable_testing()
# add_executable(${PROJECT_NAME}-Runner ${CMAKE_CURRENT_SOURCE_DIR}/[...].cpp ${CMAKE_BINARY_DIR}/[...].cpp)
# target_link_libraries(${PROJECT_NAME}-Runner ${CLUON_LIBRARIES})

# add_test(NAME ${PROJECT_NAME}-Runner COMMAND ${PROJECT_NAME}-Runner)