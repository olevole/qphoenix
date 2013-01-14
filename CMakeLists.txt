CMAKE_MINIMUM_REQUIRED(VERSION 2.8.6)
PROJECT(QPhoenix)

SET(EXECUTABLE_NAME "qphoenix")
SET(PROJECT_VERSION "0.999999")

SET(CMAKE_BUILD_TYPE Debug)

IF(NOT MSVC)
    IF("${CMAKE_SYSTEM_PROCESSOR}" STREQUAL "x86_64")
        SET(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -fPIC")
    ENDIF("${CMAKE_SYSTEM_PROCESSOR}" STREQUAL "x86_64")
ENDIF()


FIND_PACKAGE(Qt4 REQUIRED QtCore QtGui)
INCLUDE(${QT_USE_FILE})


ADD_SUBDIRECTORY(src/core/3rdparty/fancytab-widgets)
ADD_SUBDIRECTORY(src/plugins/trayicon)
ADD_SUBDIRECTORY(src/translators/mymemory)






INCLUDE_DIRECTORIES(
${CMAKE_CURRENT_BINARY_DIR}
${CMAKE_INCLUDE_PATH}
${CMAKE_CURRENT_BINARY_DIR}/src/include
src/core
src/core/config
src/core/3rdparty/fancytab-widgets
src/include
)



SET(IFACES
src/include/configpageinterface.h
src/include/mainwindowinterface.h
src/include/translatorwidgetinterface.h
src/include/dictionarywidgetinterface.h
src/include/configinterface.h
src/include/plugininterface.h
src/include/translatorinterface.h
src/include/info.h
src/include/basemodule.h

)


SET(HEADERS
src/core/mainwindow.h
src/core/config/config.h
src/core/config/testpage.h
src/core/config/translatorsconfig.h
src/core/config/pluginsconfig.h
src/core/translationwidget.h
src/core/dictionarywidget.h
src/core/querywrappers.h
src/core/loader.h
)



SET(SOURCES
src/main.cpp
src/core/mainwindow.cpp
src/core/config/config.cpp
src/core/config/translatorsconfig.cpp
src/core/config/testpage.cpp
src/core/config/pluginsconfig.cpp
src/core/translationwidget.cpp
src/core/dictionarywidget.cpp
src/core/querywrappers.cpp
src/core/loader.cpp
)

# Not implemented yet
SET(L18N
src/l18n/Russian.ts
src/l18n/English.ts)

SET(PREFIX ${CMAKE_INSTALL_PREFIX})

IF(UNIX)
        SET(MPREFIX ${PREFIX}/share/qphoenix)
        SET(INSTALLPATH ${PREFIX}/bin)
ENDIF()


IF(WIN32)
        SET(MPREFIX ${PREFIX})
        SET(INSTALLPATH ${PREFIX})
ENDIF()


SET(PLUGINS_PATH        ${MPREFIX}/plugins        CACHE INTERNAL "")
SET(TRANSLATORS_PATH    ${MPREFIX}/translators    CACHE INTERNAL "")
SET(DICTIONARIES_PATH   ${MPREFIX}/dictionaries   CACHE INTERNAL "")
SET(L18N_PATH           ${MPREFIX}/l18n           CACHE INTERNAL "")
SET(RESOURCES_PATH      ${MPREFIX}/resources      CACHE INTERNAL "")

CONFIGURE_FILE(src/include/defines.h.in src/include/defines.h)



QT4_WRAP_CPP(MOC_SOURCES ${HEADERS})


ADD_EXECUTABLE(${EXECUTABLE_NAME}
${SOURCES} ${MOC_SOURCES}  ${QM_FILES} ${QRC_SOURCES} ${GLOBAL_HEADERS} ${IFACES})

TARGET_LINK_LIBRARIES(${EXECUTABLE_NAME} ${QT_LIBRARIES} ${QT_QTWEBKIT_LIBRARIES}
 ${QT_QTXML_LIBRARIES}  ${QT_QTNETWORK_LIBRARIES} fancytabwidget)



INSTALL(TARGETS ${EXECUTABLE_NAME} DESTINATION ${INSTALLPATH})
