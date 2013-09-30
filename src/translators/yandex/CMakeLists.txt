set(TARGET "yandex_translator")
set(SOURCES yandex_translator.cpp)
set(HEADERS yandex_translator.h)
set(SPEC yandex_translator.spec)
set(FULL_TARGET_NAME ${CMAKE_SHARED_LIBRARY_PREFIX}${TARGET}${CMAKE_SHARED_LIBRARY_SUFFIX})

configure_file(yandex_translator.spec.in yandex_translator.spec)

qt5_wrap_cpp(MOC_SOURCES ${HEADERS})
add_library( ${TARGET} SHARED ${HEDARS} ${SOURCES}  ${MOC_SOURCES})
qt5_use_modules(${TARGET} Core Network Widgets)
target_link_libraries(${TARGET} phoenix)

message(${CMAKE_CURRENT_BINARY_DIR})
install(TARGETS ${TARGET} DESTINATION ${TRANSLATORS_PATH})
install(FILES ${CMAKE_CURRENT_BINARY_DIR}/${SPEC} DESTINATION ${TRANSLATORS_PATH})
