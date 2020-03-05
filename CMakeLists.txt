cmake_minimum_required(VERSION 3.5.1)

project(nodepp)

#set(CMAKE_BUILD_TYPE "Release")
set(CXX_FLAGS
		-Wall
		-Werror
		-std=c++11
   )

string(REPLACE ";" " " CMAKE_CXX_FLAGS "${CXX_FLAGS}")
set(CMAKE_CXX_FLAGS_DEBUG "$ENV{CXXFLAGS} -O2 -Wall -g -ggdb")
set(CMAKE_CXX_FLAGS_RELEASE "$ENV{CXXFLAGS} -O2 -Wall")

find_package(Boost
		1.58.0 
		REQUIRED
		COMPONENTS system
		)

if (Boost_FOUND)
	include_directories(${Boost_INCLUDE_DIRS})
endif()

add_subdirectory(3rd/tinyxml2)
add_subdirectory(node)
add_subdirectory(shared)
add_subdirectory(game)

add_subdirectory(app)
add_subdirectory(echo)
