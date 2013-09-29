set(TARGET "mymemory")
set(SOURCES mymemory.cpp)
set(HEADERS mymemory.h)
set(SPEC mymemory.spec)

configure_file(mymemory.spec.in ${SPEC})

qt5_wrap_cpp(MOC_SOURCES ${HEADERS})
add_library( ${TARGET} SHARED ${HEDARS} ${SOURCES}  ${MOC_SOURCES})

qt5_use_modules(${TARGET} Core Network Widgets)
target_link_libraries(${TARGET} phoenix)

install(TARGETS ${TARGET} DESTINATION ${TRANSLATORS_PATH})
install(FILES ${CMAKE_CURRENT_BINARY_DIR}/${SPEC} DESTINATION ${TRANSLATORS_PATH})
