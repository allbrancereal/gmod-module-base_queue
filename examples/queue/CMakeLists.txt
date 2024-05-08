set(SOURCES
    queue.cpp)

add_library(queue SHARED ${SOURCES})

# Link against the Python library
target_link_libraries(queue gmod-module-base ${PYTHON_LIBRARIES})

set_gmod_suffix_prefix(queue)
