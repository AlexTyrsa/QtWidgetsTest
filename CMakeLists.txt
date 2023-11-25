cmake_minimum_required(VERSION 3.5)

project(QtWidgetsTest VERSION 0.1 LANGUAGES CXX)

set(CMAKE_INCLUDE_CURRENT_DIR ON)

set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

find_package(QT NAMES Qt6 Qt5 COMPONENTS Widgets REQUIRED)
find_package(Qt${QT_VERSION_MAJOR} COMPONENTS Widgets REQUIRED)
find_package(Qt${QT_VERSION_MAJOR} COMPONENTS Sql REQUIRED)

set(PROJECT_SOURCES
        main.cpp
        mainwindow.cpp
        mainwindow.h
)

set(PROJECT_RESOURCES_DIR Resources)
set(PROJECT_DB_FILE_NAME system.db)
set(PROJECT_DB_FILE ${PROJECT_RESOURCES_DIR}/${PROJECT_DB_FILE_NAME})

if(${QT_VERSION_MAJOR} GREATER_EQUAL 6)
    qt_add_executable(QtWidgetsTest
        MANUAL_FINALIZATION
        MACOSX_BUNDLE
        ${PROJECT_SOURCES}
        ${PROJECT_DB_FILE}
    )
else()
    add_executable(QtWidgetsTest
        MACOSX_BUNDLE
        ${PROJECT_SOURCES}
        ${PROJECT_DB_FILE}
    )
endif()

target_link_libraries(QtWidgetsTest PRIVATE Qt${QT_VERSION_MAJOR}::Widgets Qt${QT_VERSION_MAJOR}::Sql)

set_target_properties(QtWidgetsTest PROPERTIES
    MACOSX_BUNDLE_GUI_IDENTIFIER my.example.com
    ACOSX_BUNDLE_BUNDLE_NAME QtWidgetsTest
    MACOSX_BUNDLE_BUNDLE_VERSION ${PROJECT_VERSION}
    MACOSX_BUNDLE_SHORT_VERSION_STRING ${PROJECT_VERSION_MAJOR}.${PROJECT_VERSION_MINOR}
    MACOSX_BUNDLE TRUE
    WIN32_EXECUTABLE TRUE
)

if(APPLE)
    set_source_files_properties(${PROJECT_DB_FILE}
            PROPERTIES
            MACOSX_PACKAGE_LOCATION "Resources/"
        )

    add_compile_definitions(RESOURCES_PATH="/../Resources/")
endif()

if(WIN32)
    add_custom_command(
            TARGET QtWidgetsTest POST_BUILD
            COMMAND ${CMAKE_COMMAND} -E copy
                    ${CMAKE_SOURCE_DIR}/${PROJECT_DB_FILE}
                    ${CMAKE_CURRENT_BINARY_DIR}/${PROJECT_DB_FILE_NAME}
        )

    add_compile_definitions(RESOURCES_PATH="/")
endif()

add_compile_definitions(DB_FILE_NAME="${PROJECT_DB_FILE_NAME}")

if(QT_VERSION_MAJOR EQUAL 6)
    qt_finalize_executable(QtWidgetsTest)
endif()
