#project(tests)
#set(QT_USE_QTTEST TRUE)

#add_definitions(-DFILEPATH="${CMAKE_CURRENT_SOURCE_DIR}")

#macro(mktest NAME HDR SRC)
#        qt5_wrap_cpp(MOC_SOURCES ${HDR})
#        add_executable(${NAME}  ${SRC} ${MOC_SOURCES})
#        qt5_use_modules(${NAME} Core Gui Test)
#        target_link_libraries(${NAME} qphoenix_testlib)
#        add_test(NAME ${NAME} COMMAND ${NAME})
#endmacro(mktest)


#mktest(parsertest test_specparser.h test_specparser.cpp)
