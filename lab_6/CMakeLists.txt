cmake_minimum_required(VERSION 3.5)

project(lab_6 LANGUAGES CXX)


set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS}")
set(CMAKE_INCLUDE_CURRENT_DIR ON)

set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

find_package(QT NAMES Qt6 Qt5 COMPONENTS Widgets REQUIRED)
find_package(Qt${QT_VERSION_MAJOR} COMPONENTS Widgets REQUIRED)

set(PROJECT_SOURCES
        main.cpp
        graph.cpp
        graph.hpp
        graphwindow.cpp
        graphwindow.hpp
        interface.cpp
        interface.hpp
)

if(${QT_VERSION_MAJOR} GREATER_EQUAL 6)
    qt_add_executable(lab_6
        ${PROJECT_SOURCES}
        app_images.qrc
    )
else()
    add_executable(lab_6
            ${PROJECT_SOURCES}
            app_images.qrc
    )
endif()

target_link_libraries(lab_6 PRIVATE Qt${QT_VERSION_MAJOR}::Widgets)
