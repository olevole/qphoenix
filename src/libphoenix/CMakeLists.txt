SET(TARGET phoenix)
SET(SOURCES http.cpp)
SET(HEADERS http.h)

qt5_wrap_cpp(MOC_SOURCES ${HEADERS})
add_library(${TARGET} STATIC ${HEDARS} ${SOURCES}  ${MOC_SOURCES})
qt5_use_modules(${TARGET} Core Network)

install(TARGETS ${TARGET} DESTINATION ${LIBRARY_PATH})
