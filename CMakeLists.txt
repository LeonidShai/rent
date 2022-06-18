cmake_minimum_required(VERSION 3.5)

project(rent LANGUAGES CXX)

set(CMAKE_INCLUDE_CURRENT_DIR ON)

set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

set(DEPLOY_DIR deploy)

find_package(QT NAMES Qt6 Qt5 COMPONENTS Widgets REQUIRED)
find_package(Qt${QT_VERSION_MAJOR} COMPONENTS Widgets REQUIRED)

include_directories(displays)

set(PROJECT_SOURCES
        main.cpp

        MainController.cpp
        MainController.h

        DataKeeper.cpp
        DataKeeper.h

        FileWorker.cpp
        FileWorker.h

        Logger.cpp
        Logger.h

        displays/MainDisplay.cpp
        displays/MainDisplay.h
        displays/MainDisplay.ui

        resource.qrc
)

if(${QT_VERSION_MAJOR} GREATER_EQUAL 6)
    qt_add_executable(rent
        ${PROJECT_SOURCES}
    )
else()
    add_executable(rent
        ${PROJECT_SOURCES}
    )
endif()

target_link_libraries(rent PRIVATE Qt${QT_VERSION_MAJOR}::Widgets)
set_property(TARGET rent PROPERTY WIN32_EXECUTABLE true)

install(TARGETS rent DESTINATION ${CMAKE_CURRENT_SOURCE_DIR}/../${DEPLOY_DIR})
