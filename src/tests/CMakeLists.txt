project(tests)
set(QT_USE_QTTEST TRUE)

include_directories(../core)

macro(mktest NAME HDR SRC)
	qt5_wrap_cpp(MOC_HDR ${HDR})
        add_executable(${NAME} ${HDR} ${SRC})
        qt5_use_modules(${NAME} Core Gui)
    add_test(NAME ${NAME} COMMAND ${NAME})
endmacro(mktest)


SET(PARSER_HDRS ../core/specparser.h)
SET(PARSER_SRCS ../core/specparser.cpp parsertest.cpp )


mktest( parsertest ${PARSER_HDRS} ${PARSER_SRCS})
