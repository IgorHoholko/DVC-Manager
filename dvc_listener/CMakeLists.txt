cmake_minimum_required(VERSION 3.10)
set(CMAKE_CXX_STANDARD 17)

set(PROJECT_NAME dvc_listener)
project(${PROJECT_NAME})


# link_libraries(-lstdc++fs)

find_package(Threads REQUIRED)
# find_package(cpprestsdk REQUIRED)
# target_link_libraries(${PROJECT_NAME} PRIVATE cpprestsdk::cpprest)

add_subdirectory(3rd/inotify-cpp)


set(INCLUDE
    src
    src/utils
    src/core
    src/core/workflow
)

set(SOURCE
    # src/core/WorkerThread.cpp
    src/core/Listener.cpp
    src/entities/DVCEvent.h
)



add_executable(${PROJECT_NAME} main.cpp ${SOURCE})


target_include_directories(${PROJECT_NAME} PUBLIC 3rd/inotify-cpp/src)

target_link_libraries(${PROJECT_NAME} PRIVATE Threads::Threads)
target_link_libraries(${PROJECT_NAME} PUBLIC inotify-cpp-shared)


set_target_properties(
    ${PROJECT_NAME} PROPERTIES
    CXX_STADARD 17
    CXX_STADARD_REQUIRED ON
)

