#aux_source_directory(. DIR_SRCS)

set (
		SOURCE
		World.cpp
		WorldSession.cpp
	)

add_library(game ${SOURCE})

include_directories(../)

#target_link_libraries(game pthread ${Boost_LIBRARIES})
