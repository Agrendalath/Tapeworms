cmake_minimum_required(VERSION 3.5)
project(Tapeworms)

# Set flags
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")

include_directories("${PROJECT_BINARY_DIR}")

# Set FindSFML.cmake path
set(CMAKE_MODULE_PATH "/usr/share/SFML/cmake/Modules" ${CMAKE_MODULE_PATH})
find_package(SFML 2 REQUIRED system window graphics network audio)

set(EXECUTABLE_NAME "Tapeworms")
set(SOURCE_FILES main.cpp)
add_executable(${EXECUTABLE_NAME} ${SOURCE_FILES})
target_link_libraries(${EXECUTABLE_NAME} ${SFML_LIBRARIES})

# Add resources folder (copies them only if modified)
file(COPY Resources DESTINATION .)