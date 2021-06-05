cmake_minimum_required(VERSION 3.5)

project(course_work_server LANGUAGES CXX)


set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS}")
set(CMAKE_INCLUDE_CURRENT_DIR ON)

set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

find_package(QT NAMES Qt6 Qt5 COMPONENTS Core Network REQUIRED)
find_package(Qt${QT_VERSION_MAJOR} COMPONENTS Core Network REQUIRED)

set(PROJECT_SOURCES
        main.cpp
        app.cpp
        app.hpp
        server.cpp
        server.hpp
        model.cpp
        model.hpp
)

if(${QT_VERSION_MAJOR} GREATER_EQUAL 6)
    qt_add_executable(server
        ${PROJECT_SOURCES}
    )
else()
    add_executable(server
            ${PROJECT_SOURCES}
    )
endif()

target_link_libraries(server PRIVATE Qt${QT_VERSION_MAJOR}::Core)
target_link_libraries(server PRIVATE Qt${QT_VERSION_MAJOR}::Network)
