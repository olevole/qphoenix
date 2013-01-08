CMAKE_MINIMUM_REQUIRED( VERSION 2.6 )
PROJECT("QPhoenix ")

SET(CMAKE_BUILD_TYPE Debug)

IF(NOT MSVC)
    IF("${CMAKE_SYSTEM_PROCESSOR}" STREQUAL "x86_64")
        SET(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -fPIC")
    ENDIF("${CMAKE_SYSTEM_PROCESSOR}" STREQUAL "x86_64")
ENDIF()


ADD_DEFINITIONS(${QT_DEFINITIONS})
ADD_DEFINITIONS(-DUNICODE)
FIND_PACKAGE(Qt4 REQUIRED)
INCLUDE(${QT_USE_FILE})
SET(QT_USE_QTXML TRUE)

ADD_SUBDIRECTORY(src/core/3rdparty/fancytab-widgets)
ADD_SUBDIRECTORY(src/plugins/trayicon)
ADD_SUBDIRECTORY(src/translators/mymemory)


INCLUDE_DIRECTORIES(
${CMAKE_CURRENT_BINARY_DIR}
${CMAKE_INCLUDE_PATH}
${CMAKE_CURRENT_BINARY_DIR}/src/include
src/core/config
src/core/3rdparty/fancytab-widgets
src/core
src/include
src/core/tools
)

CONFIGURE_FILE(src/include/defines.h.in src/include/defines.h)


#SET(GLOBAL_HEADERS
#src/include/defines.h)

SET(IFACES
src/include/configpageinterface.h
src/include/mainwindowinterface.h
src/include/translatorwidgetinterface.h
src/include/dictionarywidgetinterface.h
src/include/configinterface.h
src/include/plugininterface.h
src/include/translatorinterface.h
src/include/abstractinfocontainer.h
src/core/abstractloader.h
)


SET(HEADERS
src/core/mainwindow.h
src/core/config/config.h
src/core/config/testpage.h
src/core/config/translatorsconfig.h
src/core/config/pluginsconfig.h
src/core/translationwidget.h
src/core/dictionarywidget.h

src/core/multiloader.h
src/core/querywrappers.h
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
src/core/multiloader.cpp
src/core/querywrappers.cpp
)

# Not implemented yet
SET(L18N
src/l18n/Russian.ts
src/l18n/English.ts)





QT4_WRAP_CPP(MOC_SOURCES ${HEADERS})


ADD_EXECUTABLE(qphoenix ${SOURCES}
               ${MOC_SOURCES}  ${QM_FILES} ${QRC_SOURCES} ${GLOBAL_HEADERS} ${IFACES})

TARGET_LINK_LIBRARIES(qphoenix ${QT_LIBRARIES} ${QT_QTWEBKIT_LIBRARIES}
 ${QT_QTXML_LIBRARIES}  ${QT_QTNETWORK_LIBRARIES} fancytabwidget)



if(${CMAKE_SYSTEM_NAME} STREQUAL Linux)
        install(TARGETS qphoenix DESTINATION ${CMAKE_INSTALL_PREFIX}/bin)
endif()
