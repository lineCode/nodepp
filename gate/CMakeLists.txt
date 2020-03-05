aux_source_directory(. DIR_SRCS)

add_executable(app ${DIR_SRCS})

include_directories(../)

target_link_libraries(app node pthread ${Boost_LIBRARIES})
