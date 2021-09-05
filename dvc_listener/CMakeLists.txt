cmake_minimum_required(VERSION 3.10)
set(CMAKE_CXX_STANDARD 17)

set(PROJECT_NAME dvc_listener)
project(${PROJECT_NAME})

set(cpprestsdk_DIR /usr/lib/${CMAKE_LIBRARY_ARCHITECTURE}/cmake/)
find_package(cpprestsdk REQUIRED)

find_package(Threads REQUIRED)

find_package(Boost COMPONENTS system filesystem REQUIRED)




add_subdirectory(3rd/inotify-cpp)
add_subdirectory(3rd/yaml-cpp)


set(INCLUDE
    src
    src/utils
    src/core
    src/core/workflow
)

set(SOURCE
    src/core/Sender.cpp
    src/core/Listener.cpp
    src/entities/DVCEvent.h
    src/entities/DVCMeta.h
    src/core/MetaBuilder.cpp
    src/core/IWorker.h
    src/utils/common.h
)


add_executable(${PROJECT_NAME} src/core/workflow/BaseWorkflow.cpp ${SOURCE})

target_link_libraries(${PROJECT_NAME} PUBLIC cpprestsdk::cpprest)
target_link_libraries(${PROJECT_NAME} PUBLIC Threads::Threads)
target_link_libraries(${PROJECT_NAME} PUBLIC inotify-cpp-shared)
target_link_libraries(${PROJECT_NAME} PUBLIC yaml-cpp)


target_link_libraries(${PROJECT_NAME} PRIVATE ${Boost_FILESYSTEM_LIBRARY})
target_link_libraries(${PROJECT_NAME} PRIVATE ${Boost_SYSTEM_LIBRARY})

target_include_directories(${PROJECT_NAME} PUBLIC 3rd/inotify-cpp/src)
target_include_directories(${PROJECT_NAME} PUBLIC 3rd/yanl-cpp/)


add_executable(listener main.cpp ${SOURCE})

target_link_libraries(listener PUBLIC cpprestsdk::cpprest)
target_link_libraries(listener PUBLIC Threads::Threads)
target_link_libraries(listener PUBLIC inotify-cpp-shared)


target_link_libraries(listener PRIVATE ${Boost_FILESYSTEM_LIBRARY})
target_link_libraries(listener PRIVATE ${Boost_SYSTEM_LIBRARY})

target_include_directories(listener PUBLIC 3rd/inotify-cpp/src)



add_executable(requester main2.cpp ${SOURCE})

target_link_libraries(requester PRIVATE ${Boost_FILESYSTEM_LIBRARY})
target_link_libraries(requester PRIVATE ${Boost_SYSTEM_LIBRARY})

target_link_libraries(requester PUBLIC cpprestsdk::cpprest)
target_link_libraries(requester PUBLIC Threads::Threads)
target_link_libraries(requester PUBLIC inotify-cpp-shared)

target_include_directories(requester PUBLIC 3rd/inotify-cpp/src)



add_executable(builder main3.cpp ${SOURCE})

target_link_libraries(builder PRIVATE ${Boost_FILESYSTEM_LIBRARY})
target_link_libraries(builder PRIVATE ${Boost_SYSTEM_LIBRARY})

target_link_libraries(builder PUBLIC cpprestsdk::cpprest)
target_link_libraries(builder PUBLIC Threads::Threads)
target_link_libraries(builder PUBLIC inotify-cpp-shared)

target_include_directories(builder PUBLIC 3rd/inotify-cpp/src)


set_target_properties(
    ${PROJECT_NAME} PROPERTIES
    CXX_STADARD 17
    CXX_STADARD_REQUIRED ON
)

