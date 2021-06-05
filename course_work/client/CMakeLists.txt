cmake_minimum_required(VERSION 3.5)

project(course_work_client LANGUAGES CXX)


set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS}")
set(CMAKE_INCLUDE_CURRENT_DIR ON)

set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

find_package(QT NAMES Qt6 Qt5 COMPONENTS Widgets Network REQUIRED)
find_package(Qt${QT_VERSION_MAJOR} COMPONENTS Widgets Network REQUIRED)

set(PROJECT_SOURCES
        main.cpp
        app.cpp
        app.hpp
        client.cpp
        client.hpp
        interface.cpp
        interface.hpp
        controlwindow.cpp
        controlwindow.hpp
        paramswindow.cpp
        paramswindow.hpp
        statewindow.cpp
        statewindow.hpp
        notice.cpp
        notice.hpp
)

if(${QT_VERSION_MAJOR} GREATER_EQUAL 6)
    qt_add_executable(client
        ${PROJECT_SOURCES}
    )
else()
    add_executable(client
            ${PROJECT_SOURCES}
    )
endif()

target_link_libraries(client PRIVATE Qt${QT_VERSION_MAJOR}::Widgets)
target_link_libraries(client PRIVATE Qt${QT_VERSION_MAJOR}::Network)
