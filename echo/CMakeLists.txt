aux_source_directory(. DIR_SRCS)

add_executable(echo ${DIR_SRCS})

include_directories(../)

target_link_libraries(echo node pthread ${Boost_LIBRARIES})
