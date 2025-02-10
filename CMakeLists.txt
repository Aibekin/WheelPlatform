cmake_minimum_required(VERSION 3.10.0)
project(Driver VERSION 0.1.0 LANGUAGES C CXX)

# set(SRC
#     src/ComPort.h
#     src/ComPort.cpp
# )

add_library(COMPORT STATIC src/ComPort.cpp)
add_library(DRIVER_PACKET STATIC src/DriverPacket.cpp)
# add_library(COMPORT STATIC ${SRC})

target_include_directories(COMPORT PUBLIC src)
target_include_directories(DRIVER_PACKET PUBLIC src)

add_executable(${PROJECT_NAME} main.cpp)
# add_executable(${PROJECT_NAME} src/main.cpp)

target_link_libraries(${PROJECT_NAME} PRIVATE COMPORT)
target_link_libraries(${PROJECT_NAME} PRIVATE DRIVER_PACKET)