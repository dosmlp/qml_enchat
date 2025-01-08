cmake_minimum_required(VERSION 3.16)

project(qml_enchat VERSION 0.1 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_STANDARD 20)
list(APPEND CMAKE_PREFIX_PATH $ENV{QTDIR})
set(QWindowKit_DIR "./QWindowKit/lib/cmake/QWindowKit")

add_subdirectory(base)
add_subdirectory(enchat)

find_package(Qt6 6.5 REQUIRED COMPONENTS Quick)
find_package(QWindowKit COMPONENTS Core Widgets Quick REQUIRED)
find_package(unofficial-ed25519 REQUIRED)
# find_package(OpenSSL REQUIRED)

qt_standard_project_setup(REQUIRES 6.5)
set(CMAKE_AUTORCC ON)

qt_add_executable(appqml_enchat
    main.cpp
    json.hpp
    appconfig.h
    appconfig.cpp
    friendlistmodel.h friendlistmodel.cpp
    chathistory.h chathistory.cpp
    chatengine.h chatengine.cpp
    common.h common.cpp
    ico.qrc

)

qt_add_qml_module(appqml_enchat
    URI qml_enchat
    VERSION 1.0
    QML_FILES
        Main.qml
        FriendListView.qml
        ChatContentView.qml
        ChatHistoryListView.qml
)

# qt_add_resources(ico.qrc)

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
    base
    enchat
    QWindowKit::Quick
    unofficial::ed25519::ed25519
)
# target_include_directories(appqml_enchat PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})
target_include_directories(appqml_enchat PUBLIC "D:\\3rd\\git_repo\\yalantinglibs\\include")

