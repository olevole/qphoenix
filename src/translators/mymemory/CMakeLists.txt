set(TARGET "mymemory")
set(SOURCES mymemory.cpp)
set(HEADERS mymemory.h)
set(SPEC mymemory.spec)
set(FULL_TARGET_NAME ${CMAKE_SHARED_LIBRARY_PREFIX}${TARGET}${CMAKE_SHARED_LIBRARY_SUFFIX})

configure_file(mymemory.spec.in ${SPEC})
compress_json(${CMAKE_CURRENT_BINARY_DIR}/${SPEC})

qt5_wrap_cpp(MOC_SOURCES ${HEADERS})
add_library( ${TARGET} SHARED ${HEDARS} ${SOURCES}  ${MOC_SOURCES})

qt5_use_modules(${TARGET} Core Network Widgets)
target_link_libraries(${TARGET} phoenix)

install(TARGETS ${TARGET} DESTINATION ${TRANSLATORS_PATH})
install(FILES ${CMAKE_CURRENT_BINARY_DIR}/${SPEC} DESTINATION ${TRANSLATORS_PATH})
