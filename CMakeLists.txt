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



include_directories(
${CMAKE_CURRENT_BINARY_DIR}
${CMAKE_INCLUDE_PATH}
src/settings
src/exceptions
src/historymanager)




configure_file(src/common/defines.h.in src/common/defines.h)


set(HEADERS
src/mainwindow.h
src/historymanager/historymanager.h
src/exceptions/exceptions.h
src/settings/settings.h
)


set(SOURCES
src/main.cpp
src/mainwindow.cpp
src/historymanager/historymanager.cpp
src/exceptions/exceptions.cpp
src/settings/settings.cpp
)

set(FORMS
src/mainwindow.ui
src/historymanager/historymanager.ui
src/exceptions/exceptions.ui
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


target_link_libraries(qphoenix ${QT_LIBRARIES} ${QT_QTWEBKIT_LIBRARIES} ${QT_QTXML_LIBRARIES}  ${QT_QTNETWORK_LIBRARIES})


