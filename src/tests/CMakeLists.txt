project(tests)
set(QT_USE_QTTEST TRUE)

include_directories(../core)

#add_executable(testrunner testrunner.cpp)

macro(mktest NAME HDR SRC)
        qt5_wrap_cpp(MOC_SOURCES ${HDR})
        add_executable(${NAME}  ${SRC} ${MOC_SOURCES})
        qt5_use_modules(${NAME} Core Gui Test)
        target_link_libraries(${NAME} qphoenix_testlib)
#        target_link_libraries(testrunner ${NAME})
        add_test(NAME ${NAME} COMMAND ${NAME})
endmacro(mktest)

add_definitions(-DFILEPATH="${CMAKE_CURRENT_SOURCE_DIR}")

mktest(parsertest test_specparser.h test_specparser.cpp)
