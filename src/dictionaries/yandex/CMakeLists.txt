set(TARGET yandex_dict)
set(SRC yandex_dict.cpp)
set(HDR yandex_dict.h)
set(SPEC yandex_dict.spec)
set(FULL_TARGET_NAME ${CMAKE_SHARED_LIBRARY_PREFIX}${TARGET}${CMAKE_SHARED_LIBRARY_SUFFIX})

configure_file(yandex_dict.spec.in ${SPEC})
qt5_wrap_cpp(MOC_SOURCES ${HDR})
add_library(${TARGET} SHARED ${HDR} ${SRC}  ${MOC_SOURCES})
qt5_use_modules(${TARGET} Network Core Gui Widgets)
target_link_libraries(${TARGET} phoenix)

install(TARGETS ${TARGET} DESTINATION ${DICTIONARIES_PATH} )
install(FILES ${CMAKE_CURRENT_BINARY_DIR}/${SPEC} DESTINATION ${DICTIONARIES_PATH})


