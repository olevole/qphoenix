set(TARGET wordreference)
set(SRC wordreference.cpp)
set(HDR wordreference.h)
set(SPEC wordreference.spec)
set(FULL_TARGET_NAME ${CMAKE_SHARED_LIBRARY_PREFIX}${TARGET}${CMAKE_SHARED_LIBRARY_SUFFIX})

configure_file(wordreference.spec.in ${SPEC})
qt5_wrap_cpp(MOC_SOURCES ${HDR})
add_library(${TARGET} SHARED ${HDR} ${SRC}  ${MOC_SOURCES})
qt5_use_modules(${TARGET} Network Core Gui Widgets)
target_link_libraries(${TARGET} phoenix)

install(TARGETS ${TARGET} DESTINATION ${DICTIONARIES_PATH} )
install(FILES ${CMAKE_CURRENT_BINARY_DIR}/${SPEC} DESTINATION ${DICTIONARIES_PATH})


