cmake_minimum_required(VERSION 3.16)

project(qml_enchat VERSION 0.1 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD_REQUIRED ON)

find_package(Qt6 6.5 REQUIRED COMPONENTS Quick)
# find_package(OpenSSL REQUIRED)

qt_standard_project_setup(REQUIRES 6.5)

qt_add_executable(appqml_enchat
    main.cpp
    json.hpp
    appconfig.h
    appconfig.cpp
    chathistory.h chathistory.cpp
)

qt_add_qml_module(appqml_enchat
    URI qml_enchat
    VERSION 1.0
    QML_FILES
        Main.qml
        QML_FILES FriendListView.qml
        QML_FILES ChatContentView.qml
        SOURCES friendlistmodel.h friendlistmodel.cpp
        QML_FILES ChatHistoryListView.qml
)

# Qt for iOS sets MACOSX_BUNDLE_GUI_IDENTIFIER automatically since Qt 6.1.
# If you are developing for iOS or macOS you should consider setting an
# explicit, fixed bundle identifier manually though.
set_target_properties(appqml_enchat PROPERTIES
#    MACOSX_BUNDLE_GUI_IDENTIFIER com.example.appqml_enchat
    MACOSX_BUNDLE_BUNDLE_VERSION ${PROJECT_VERSION}
    MACOSX_BUNDLE_SHORT_VERSION_STRING ${PROJECT_VERSION_MAJOR}.${PROJECT_VERSION_MINOR}
    MACOSX_BUNDLE TRUE
    WIN32_EXECUTABLE TRUE
)

target_link_libraries(appqml_enchat
    PRIVATE Qt6::Quick
)

