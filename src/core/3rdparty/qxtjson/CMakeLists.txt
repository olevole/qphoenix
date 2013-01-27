SET(QXT-SOURCES qxtglobal.cpp qxtjson.cpp)
SET(QXTHEADERS qxtglobal.h qxtjson.h)

ADD_LIBRARY(qxtjson STATIC ${QXT-SOURCES} ${QXTHEADERS})
