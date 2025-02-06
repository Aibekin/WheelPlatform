cmake_minimum_required(VERSION 3.10.0)
project(Driver VERSION 0.1.0 LANGUAGES C CXX)

add_executable(${PROJECT_NAME} main.cpp)

set(SRC
    src/ComPort.h
    src/ComPort.cpp
)

add_library(COMPORT STATIC ${SRC})

target_link_libraries(${PROJECT_NAME} PRIVATE ${COMPORT})