aux_source_directory(. DIR_SRCS)

add_executable(app ${DIR_SRCS})

include_directories(../)

include_directories(../game/)
link_directories(../game/)

include_directories(../shared/)
link_directories(../shared/)

target_link_libraries(app node pthread ${Boost_LIBRARIES} shared game)
