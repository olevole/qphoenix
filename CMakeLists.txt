cmake_minimum_required( VERSION 2.6 )
project("QPhoenix ")

SET(CMAKE_BUILD_TYPE Debug)

IF(NOT MSVC)
    IF("${CMAKE_SYSTEM_PROCESSOR}" STREQUAL "x86_64")
        SET(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -fPIC")
    ENDIF("${CMAKE_SYSTEM_PROCESSOR}" STREQUAL "x86_64")
ENDIF()


ADD_DEFINITIONS(${QT_DEFINITIONS})
ADD_DEFINITIONS(-DUNICODE)
find_package(Qt4 REQUIRED)
include(${QT_USE_FILE})
set(QT_USE_QTXML TRUE)

add_subdirectory(src/core/3rdparty/fancytab-widgets)
add_subdirectory(src/plugins/trayicon)

include_directories(
${CMAKE_CURRENT_BINARY_DIR}
${CMAKE_INCLUDE_PATH}
src/core/settings
src/core/3rdparty/fancytab-widgets
src/core
src/include
src/core/tools
)

configure_file(src/include/defines.h src/include/defines.h)

set(GLOBAL_HEADERS
src/include/defines.h)

set(IFACES
src/include/settingspageinterface.h
src/include/mainwindowinterface.h
src/include/translatorwidgetinterface.h
src/include/dictionarywidgetinterface.h
src/include/settingsinterface.h
src/include/plugininterface.h
src/include/translatorinterface.h
src/include/abstractinfocontainer.h
src/core/abstractloader.h
)


set(HEADERS
src/core/mainwindow.h
src/core/settings/settings.h
src/core/settings/testpage.h
src/core/settings/translator.h
src/core/translationwidget.h
src/core/dictionarywidget.h
src/core/translatorloader.h
src/core/multiloader.h
)



set(SOURCES
src/main.cpp
src/core/mainwindow.cpp
src/core/settings/settings.cpp
src/core/settings/translator.cpp
src/core/settings/testpage.cpp
src/core/translationwidget.cpp
src/core/dictionarywidget.cpp
src/core/translatorloader.cpp
src/core/multiloader.cpp
)

# Not implemented yet
set(L18N
src/l18n/Russian.ts
src/l18n/English.ts)





qt4_wrap_cpp(MOC_SOURCES ${HEADERS})


add_executable(qphoenix ${SOURCES}
               ${MOC_SOURCES}  ${QM_FILES} ${QRC_SOURCES} ${GLOBAL_HEADERS} ${IFACES})

target_link_libraries(qphoenix ${QT_LIBRARIES} ${QT_QTWEBKIT_LIBRARIES}
 ${QT_QTXML_LIBRARIES}  ${QT_QTNETWORK_LIBRARIES} fancytabwidget)


