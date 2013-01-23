
  set(QXT-SOURCES
    qxtglobal.cpp
    qxtjson.cpp
  )

  set(QXTHEADERS
    qxtglobal.h
    qxtjson.h
  )


  ADD_LIBRARY(qxtjson STATIC
    ${QXT-SOURCES}
    ${QXTHEADERS}
  )
