set(TARGET scanner)
set(SOURCES scanner.cpp)
set(HEADERS scanner.h)
set(SPEC scanner.spec)

set(FULL_TARGET_NAME ${CMAKE_SHARED_LIBRARY_PREFIX}${TARGET}${CMAKE_SHARED_LIBRARY_SUFFIX})

configure_file(scanner.spec.in ${SPEC})

qt5_wrap_cpp(MOC_SOURCES ${HEADERS})
add_library(${TARGET}  SHARED ${HEDARS} ${SOURCES}  ${MOC_SOURCES})
qt5_use_modules(${TARGET} Widgets Core)

install(TARGETS ${TARGET} DESTINATION ${PLUGINS_PATH})
install(FILES ${CMAKE_CURRENT_BINARY_DIR}/${SPEC} DESTINATION ${PLUGINS_PATH})
