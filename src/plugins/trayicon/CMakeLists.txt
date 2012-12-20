cmake_minimum_required(VERSION 2.6)


ADD_DEFINITIONS(${QT_DEFINITIONS})


find_package(Qt4 REQUIRED)
include(${QT_USE_FILE})

add_definitions(${QT_DEFINITIONS})
add_definitions(-DQT_PLUGIN)
add_definitions(-DQT_NO_DEBUG)
add_definitions(-DQT_SHARED)
ADD_DEFINITIONS(-DQT_DLL)

include_directories(
${CMAKE_CURRENT_BINARY_DIR}
${CMAKE_INCLUDE_PATH}
${PROJECT_SOURCE_DIR}
${PROJECT_SOURCE_DIR}/../../include
)


set(SOURCES
  trayicon.cpp
)

set(HEADERS
  trayicon.h
)

qt4_wrap_cpp(MOC_SOURCES ${HEADERS})




add_library( trayicon SHARED ${HEDARS} ${SOURCES}  ${MOC_SOURCES})
target_link_libraries(trayicon ${QT_LIBRARIES})
