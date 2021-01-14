cmake_minimum_required( VERSION 3.16.3 )

project( Tic_Tac_Toe )
set(CMAKE_WINDOWS_EXPORT_ALL_SYMBOLS ON)

#setting linking type to static
set(wxWidgets_USE_STATIC 1)

#look for wxWidget lib
find_package(wxWidgets REQUIRED gl core base OPTIONAL_COMPONENTS net) 

#set main source files(just one in this case)
set(SRCS src/cMain.cpp)

#where to look for wxWidget include dir - set by find_package
include(${wxWidgets_USE_FILE})

include_directories( ./include/ ./src )

add_executable( ticTacToe WIN32 ./src/cApp.cpp ./src/cMain.cpp)

target_link_libraries(ticTacToe ${wxWidgets_LIBRARIES})
