cmake_minimum_required( VERSION 2.6 )
project("QPhoenix ")

SET (CMAKE_BUILD_TYPE Release)

IF(NOT MSVC)
    IF("${CMAKE_SYSTEM_PROCESSOR}" STREQUAL "x86_64")
        SET (CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -fPIC")
    ENDIF("${CMAKE_SYSTEM_PROCESSOR}" STREQUAL "x86_64")
ENDIF()


ADD_DEFINITIONS(${QT_DEFINITIONS})

ADD_DEFINITIONS(-DUNICODE)

find_package(Qt4 REQUIRED)

include(${QT_USE_FILE} )
set(QT_USE_QTXML TRUE)

add_subdirectory(src/core/3rdparty/fancytab-widgets)


include_directories(
${CMAKE_CURRENT_BINARY_DIR}
${CMAKE_INCLUDE_PATH}
src/core/settings
src/core/3rdparty/fancytab-widgets
src/core
src/include
)




configure_file(src/include/defines.h.in src/include/defines.h)


set(HEADERS
src/core/mainwindow.h
src/core/settings/settings.h
src/core/settings/settingsbase.h
src/include/settingsinterface.h
src/include/plugininterface.h
src/include/pluginapi.h


)


set(SOURCES
src/main.cpp
src/core/mainwindow.cpp
src/core/settings/settings.cpp
)

set(FORMS
src/core/mainwindow.ui
src/core/settings/settings.ui
)


set(DOCUMENTS
docs/standards_capability.txt)







qt4_wrap_cpp(MOC_SOURCES ${HEADERS})
qt4_wrap_ui(UI_HEADERS ${FORMS})


#qt4_add_resources(QRC_SOURCES ${RESOURCES})








add_executable(qphoenix ${SOURCES}
	       ${MOC_SOURCES} ${UI_HEADERS} ${QM_FILES} ${QRC_SOURCES})


if (Q_WS_X11)
    include_directories(${X11_Xlib_INCLUDE_PATH} )
    target_link_libraries(qphoenix ${X11_LIBRARIES})
endif (Q_WS_X11)


target_link_libraries(qphoenix ${QT_LIBRARIES} ${QT_QTWEBKIT_LIBRARIES} ${QT_QTXML_LIBRARIES}  ${QT_QTNETWORK_LIBRARIES} fancytabwidget)


