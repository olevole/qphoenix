set(TARGET speech)
set(SOURCES speech.cpp)
set(HEADERS speech.h)
set(RESOURCES speech_resources.qrc)
set(SPEC speech.spec)

set(FULL_TARGET_NAME ${CMAKE_SHARED_LIBRARY_PREFIX}${TARGET}${CMAKE_SHARED_LIBRARY_SUFFIX})

configure_file(speech.spec.in ${SPEC})

qt5_wrap_cpp(MOC_SOURCES ${HEADERS})
qt5_add_resources(SPEECH_RC ${RESOURCES})

add_library(${TARGET}  SHARED ${HEDARS} ${SOURCES}  ${MOC_SOURCES} ${SPEECH_RC})
qt5_use_modules(${TARGET} Widgets Core Multimedia)
target_link_libraries(${TARGET} phoenix)

install(TARGETS ${TARGET} DESTINATION ${PLUGINS_PATH})
install(FILES ${CMAKE_CURRENT_BINARY_DIR}/${SPEC} DESTINATION ${PLUGINS_PATH})

