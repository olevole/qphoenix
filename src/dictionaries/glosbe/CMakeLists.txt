SET(TARGET glosbe)
SET(SRC glosbe.cpp)
SET(HDR glosbe.h)
ADD_DEFINITIONS(-DQT_PLUGIN)

QT5_WRAP_CPP(MOC_SOURCES ${HDR})

ADD_LIBRARY(${TARGET} SHARED ${HDR} ${SRC}  ${MOC_SOURCES})
QT5_USE_MODULES(${TARGET} Network Core Gui Widgets)
INSTALL(TARGETS ${TARGET} DESTINATION ${DICTIONARIES_PATH} )


