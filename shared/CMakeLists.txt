#aux_source_directory(. DIR_SRCS)

set (
		SOURCE
		config.cpp
	)

add_library(shared ${SOURCE})

include_directories(../)

