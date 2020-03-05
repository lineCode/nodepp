aux_source_directory(. DIR_SRCS)

add_executable(client ${DIR_SRCS})

include_directories(../)

target_link_libraries(client node pthread ${Boost_LIBRARIES})
