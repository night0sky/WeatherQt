cmake_minimum_required(VERSION 3.19)
project(WeatherApplication LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

find_package(Qt6 6.5 REQUIRED COMPONENTS
    Core Gui Widgets Multimedia Network
)

qt_standard_project_setup()

qt_add_executable(WeatherApplication
    WIN32 MACOSX_BUNDLE
    main.cpp
    mainwindow.cpp
    mainwindow.h
    day7info.h
    day7info.cpp
    APICall.cpp
    Api.h
    CityCode.json
)

qt_add_resources(WeatherApplication "app_resources"
    PREFIX "/"
    FILES
        CityCode.json
)

set_target_properties(WeatherApplication PROPERTIES
    AUTOMOC ON
    AUTOUIC ON
    AUTORCC ON
)

target_link_libraries(WeatherApplication PRIVATE
    Qt6::Core
    Qt6::Gui
    Qt6::Widgets
    Qt6::Multimedia
    Qt6::Network
)

include(GNUInstallDirs)

install(TARGETS WeatherApplication
    BUNDLE  DESTINATION .
    RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
    LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
)

qt_generate_deploy_app_script(
    TARGET WeatherApplication
    OUTPUT_SCRIPT deploy_script
    NO_UNSUPPORTED_PLATFORM_ERROR
)
install(SCRIPT ${deploy_script})
