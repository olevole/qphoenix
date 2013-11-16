project(QPhoenix)
cmake_minimum_required(VERSION 2.8.10)
set(EXECUTABLE_NAME qphoenix)
set(PROJECT_VERSION 0.999999 CACHE INTERNAL "")
set(CMAKE_BUILD_TYPE Debug)
set(TESTING_ENABLED TRUE)


exec_program("git" ${CMAKE_CURRENT_SOURCE_DIR} ARGS "rev-parse HEAD" OUTPUT_VARIABLE VERSION)
string(SUBSTRING ${VERSION} 0 7 GIT_HASH)

if(CMAKE_BUILD_TYPE STREQUAL Debug)
    add_definitions(-DQP_DEBUG)
    if(CMAKE_COMPILER_IS_GNUCC)
        set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -Werror")
    endif(CMAKE_COMPILER_IS_GNUCC)
endif()


if(NOT MSVC)
    if("${CMAKE_SYSTEM_PROCESSOR}" STREQUAL "x86_64")
        set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -fPIC")
    endif("${CMAKE_SYSTEM_PROCESSOR}" STREQUAL "x86_64")
endif()

find_package(Qt5Widgets REQUIRED)
find_package(Qt5Core REQUIRED)
find_package(Qt5Network REQUIRED)
find_package(Qt5WebKit REQUIRED)
find_package(Qt5WebKitWidgets REQUIRED)
find_package(Qt5Multimedia REQUIRED)

include_directories(
${CMAKE_CURRENT_BINARY_DIR}
${CMAKE_INCLUDE_PATH}
${CMAKE_CURRENT_BINARY_DIR}/src/include
src/core
src/core/config
src/include
src/libphoenix)

set(IFACES
src/include/iconfigpage.h
src/include/imainwindow.h
src/include/itranslationwidget.h
src/include/idictionarywidget.h
src/include/iconfig.h
src/include/iplugin.h
src/include/itranslator.h
src/include/idictionary.h
src/include/imodule.h
src/include/icore.h
src/include/api.h)

set(HEADERS
src/core/mainwindow.h
src/core/config/config.h
src/core/config/translatorsconfig.h
src/core/config/pluginsconfig.h
src/core/config/languageconfig.h
src/core/config/dictionaryconfig.h
src/core/config/commonconfig.h
src/core/translationwidget.h
src/core/dictionarywidget.h
src/core/threads.h
src/core/loader.h
src/core/dictionarytemplate.h
src/core/languages.h
src/core/specparser.h
src/core/core.h)

set(SOURCES
src/core/mainwindow.cpp
src/core/config/config.cpp
src/core/config/translatorsconfig.cpp
src/core/config/pluginsconfig.cpp
src/core/config/languageconfig.cpp
src/core/config/dictionaryconfig.cpp
src/core/config/commonconfig.cpp
src/core/translationwidget.cpp
src/core/dictionarywidget.cpp
src/core/threads.cpp
src/core/loader.cpp
src/core/dictionarytemplate.cpp
src/core/languages.cpp
src/core/specparser.cpp
src/core/core.cpp)

set(RESOURCES resources/resources.qrc)
qt5_add_resources(RC_SOURCES ${RESOURCES})


set(PREFIX ${CMAKE_INSTALL_PREFIX})

if(UNIX)
        set(MPREFIX ${PREFIX}/share/qphoenix)
        set(INSTALLPATH ${PREFIX}/bin)
elseif(WIN32)
        set(MPREFIX ${PREFIX})
        set(INSTALLPATH ${PREFIX})
endif()


set(PLUGINS_PATH        ${MPREFIX}/plugins        CACHE INTERNAL "")
set(TRANSLATORS_PATH    ${MPREFIX}/translators    CACHE INTERNAL "")
set(DICTIONARIES_PATH   ${MPREFIX}/dictionaries   CACHE INTERNAL "")
set(LIBRARY_PATH        ${PREFIX}/lib             CACHE INTERNAL "")

add_subdirectory(src/plugins)
add_subdirectory(src/translators)
add_subdirectory(src/dictionaries)
add_subdirectory(src/libphoenix)



configure_file(src/include/defines.h.in src/include/defines.h)

qt5_wrap_cpp(MOC_SOURCES ${HEADERS})

if(TESTING_ENABLED)
    enable_testing(TRUE)
    add_library(qphoenix_testlib STATIC ${RC_SOURCES} ${SOURCES} ${MOC_SOURCES}  ${QM_FILES} ${GLOBAL_HEADERS} ${IFACES})
    qt5_use_modules(qphoenix_testlib Widgets Core Network WebKit WebKitWidgets)
    add_subdirectory(src/tests)
endif()

add_executable(${EXECUTABLE_NAME} src/main.cpp ${RC_SOURCES} ${SOURCES} ${MOC_SOURCES}  ${QM_FILES} ${GLOBAL_HEADERS} ${IFACES})
qt5_use_modules(${EXECUTABLE_NAME} Widgets Core Network WebKit WebKitWidgets)


install(TARGETS ${EXECUTABLE_NAME} DESTINATION ${INSTALLPATH})
install(DIRECTORY src/include/ DESTINATION ${PREFIX}/include/qphoenix)
install(FILES ${CMAKE_CURRENT_SOURCE_DIR}/qphoenix.desktop DESTINATION ${PREFIX}/share/applications)
install(FILES ${CMAKE_CURRENT_SOURCE_DIR}/qphoenix.png DESTINATION ${PREFIX}/share/pixmaps/)
