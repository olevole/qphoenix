SET(TARGET "fancytabwidget")

INCLUDE_DIRECTORIES(utils)


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



ADD_LIBRARY(${TARGET} SHARED
    ${MOC_SOURCES}
    ${SOURCES}
    ${HEADERS})

TARGET_LINK_LIBRARIES(${TARGET}  ${QT_LIBRARIES})
