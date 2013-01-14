CMAKE_MINIMUM_REQUIRED(VERSION 2.6)
SET(TARGET "fancytabwidget")


ADD_DEFINITIONS(${QT_DEFINITIONS})
FIND_PACKAGE(Qt4 REQUIRED QtGui QtCore)
INCLUDE(${QT_USE_FILE})

INCLUDE_DIRECTORIES(
${CMAKE_CURRENT_BINARY_DIR}
${CMAKE_INCLUDE_PATH}
utils)


SET(SOURCES
fancytabwidget.cpp
utils/fancymainwindow.cpp
utils/manhattanstyle.cpp
utils/minisplitter.cpp
utils/styleanimator.cpp
utils/styledbar.cpp
utils/stylehelper.cpp)

SET(HEADERS
fancytabwidget.h
utils/core_global.h
utils/fancymainwindow.h
utils/manhattanstyle.h
utils/minisplitter.h
utils/styleanimator.h
utils/styledbar.h
utils/stylehelper.h
utils/utils_global.h)

QT4_WRAP_CPP(MOC_SOURCES ${HEADERS})



ADD_LIBRARY(${TARGET} STATIC
    ${MOC_SOURCES}
    ${SOURCES}
    ${HEADERS})

TARGET_LINK_LIBRARIES(${TARGET}  ${QT_LIBRARIES})
