cmake_minimum_required(VERSION 3.2)

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)

find_package(thallium REQUIRED)

add_executable(c client.cc)
target_link_libraries(c thallium)

add_executable(s server.cc)
target_link_libraries(s thallium)
