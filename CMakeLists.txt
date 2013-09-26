CMAKE_MINIMUM_REQUIRED(VERSION 2.8.6)
PROJECT(QPhoenix)
CMAKE_MINIMUM_REQUIRED(VERSION 2.8.10)
SET(EXECUTABLE_NAME qphoenix)
SET(PROJECT_VERSION 0.999999)
SET(CMAKE_BUILD_TYPE Debug)
ENABLE_TESTING(TRUE)

EXEC_PROGRAM("git" ${CMAKE_CURRENT_SOURCE_DIR} ARGS "rev-parse HEAD" OUTPUT_VARIABLE VERSION)
STRING(SUBSTRING ${VERSION} 0 7 GIT_HASH)

IF(CMAKE_BUILD_TYPE STREQUAL Debug)
    ADD_DEFINITIONS(-DQP_DEBUG)
ENDIF()


IF(NOT MSVC)
    IF("${CMAKE_SYSTEM_PROCESSOR}" STREQUAL "x86_64")
    SET(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -fPIC")
    ENDIF("${CMAKE_SYSTEM_PROCESSOR}" STREQUAL "x86_64")
ENDIF()

FIND_PACKAGE(Qt5Widgets REQUIRED)
FIND_PACKAGE(Qt5Core REQUIRED)
FIND_PACKAGE(Qt5Network REQUIRED)
FIND_PACKAGE(Qt5WebKit REQUIRED)
FIND_PACKAGE(Qt5WebKitWidgets REQUIRED)
FIND_PACKAGE(Qt5Multimedia REQUIRED)

INCLUDE_DIRECTORIES(
${CMAKE_CURRENT_BINARY_DIR}
${CMAKE_INCLUDE_PATH}
${CMAKE_CURRENT_BINARY_DIR}/src/include
src/core
src/core/config
src/include
src/libphoenix)

SET(IFACES
src/include/iconfigpage.h
src/include/imainwindow.h
src/include/itranslationwidget.h
src/include/idictionarywidget.h
src/include/iconfig.h
src/include/iplugin.h
src/include/itranslator.h
src/include/idictionary.h
src/include/info.h
src/include/imodule.h
src/include/api.h
src/include/pluginconnector.h
src/include/languagetable.h)

SET(HEADERS
src/core/mainwindow.h
src/core/config/config.h
src/core/config/translatorsconfig.h
src/core/config/pluginsconfig.h
src/core/config/languageconfig.h
src/core/config/dictionaryconfig.h
src/core/config/commonconfig.h
src/core/translationwidget.h
src/core/dictionarywidget.h
src/core/querywrappers.h
src/core/loader.h
src/core/infodialog.h
src/core/dictionarytemplate.h
src/core/languages.h
src/core/core.h)

SET(SOURCES
src/main.cpp
src/core/mainwindow.cpp
src/core/config/config.cpp
src/core/config/translatorsconfig.cpp
src/core/config/pluginsconfig.cpp
src/core/config/languageconfig.cpp
src/core/config/dictionaryconfig.cpp
src/core/config/commonconfig.cpp
src/core/translationwidget.cpp
src/core/dictionarywidget.cpp
src/core/querywrappers.cpp
src/core/loader.cpp
src/core/infodialog.cpp
src/core/dictionarytemplate.cpp
src/core/languages.cpp
src/core/core.cpp)

SET(RESOURCES resources/resources.qrc)
QT5_ADD_RESOURCES(RC_SOURCES ${RESOURCES})


SET(PREFIX ${CMAKE_INSTALL_PREFIX})

IF(UNIX)
        SET(MPREFIX ${PREFIX}/share/qphoenix)
        SET(INSTALLPATH ${PREFIX}/bin)
ELSEIF(WIN32)
        SET(MPREFIX ${PREFIX})
        SET(INSTALLPATH ${PREFIX})
ENDIF()


SET(PLUGINS_PATH        ${MPREFIX}/plugins        CACHE INTERNAL "")
SET(TRANSLATORS_PATH    ${MPREFIX}/translators    CACHE INTERNAL "")
SET(DICTIONARIES_PATH   ${MPREFIX}/dictionaries   CACHE INTERNAL "")
SET(LIBRARY_PATH        ${PREFIX}/lib             CACHE INTERNAL "")

ADD_SUBDIRECTORY(src/plugins)
ADD_SUBDIRECTORY(src/translators)
ADD_SUBDIRECTORY(src/dictionaries)
ADD_SUBDIRECTORY(src/libphoenix)

CONFIGURE_FILE(src/include/defines.h.in src/include/defines.h)

QT5_WRAP_CPP(MOC_SOURCES ${HEADERS})

ADD_EXECUTABLE(${EXECUTABLE_NAME} src/main.cpp ${RC_SOURCES} ${SOURCES} ${MOC_SOURCES}  ${QM_FILES} ${GLOBAL_HEADERS} ${IFACES})
QT5_USE_MODULES(${EXECUTABLE_NAME} Widgets Core Network WebKit WebKitWidgets)


INSTALL(TARGETS ${EXECUTABLE_NAME} DESTINATION ${INSTALLPATH})
INSTALL(DIRECTORY src/include/ DESTINATION ${PREFIX}/include/qphoenix)
INSTALL(FILES ${CMAKE_CURRENT_SOURCE_DIR}/qphoenix.desktop DESTINATION ${PREFIX}/share/applications)
INSTALL(FILES ${CMAKE_CURRENT_SOURCE_DIR}/qphoenix.png DESTINATION ${PREFIX}/share/pixmaps/)


