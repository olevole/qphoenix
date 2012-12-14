cmake_minimum_required(VERSION 2.6)


  ADD_DEFINITIONS(${QT_DEFINITIONS})

  find_package(Qt4 REQUIRED)
  include(${QT_USE_FILE})

  include_directories(
${CMAKE_CURRENT_BINARY_DIR}
${CMAKE_INCLUDE_PATH}
utils)


  set(SOURCES
    fancytabwidget.cpp
    utils/fancymainwindow.cpp
    utils/manhattanstyle.cpp
    utils/minisplitter.cpp
    utils/styleanimator.cpp
    utils/styledbar.cpp
    utils/stylehelper.cpp
  )

  set(HEADERS
    fancytabwidget.h
    utils/core_global.h
    utils/fancymainwindow.h
    utils/manhattanstyle.h
    utils/minisplitter.h
    utils/styleanimator.h
    utils/styledbar.h
    utils/stylehelper.h
    utils/utils_global.h
  )

qt4_wrap_cpp(MOC_SOURCES ${HEADERS})


  #qt4_wrap_cpp(QXT-SOURCES-MOC ${QXT-MOC-HEADERS})

  ADD_LIBRARY(fancytabwidget STATIC
    ${MOC_SOURCES}
    ${SOURCES}
    ${HEADERS}
  )
