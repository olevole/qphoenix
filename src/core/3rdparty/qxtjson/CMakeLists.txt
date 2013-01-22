

  ADD_DEFINITIONS(${QT_DEFINITIONS})

  find_package(Qt4 REQUIRED)
  include(${QT_USE_FILE})


  set(QXT-SOURCES
    qxtglobal.cpp
    qxtjson.cpp
  )

  set(QXTHEADERS
    qxtglobal.h
    qxtjson.h
  )

  #qt4_wrap_cpp(QXT-SOURCES-MOC ${QXT-MOC-HEADERS})

  ADD_LIBRARY(qxtjson STATIC
    ${QXT-SOURCES}
    ${QXTHEADERS}
  )
