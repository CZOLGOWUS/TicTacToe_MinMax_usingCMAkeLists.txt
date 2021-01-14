cmake_minimum_required( VERSION 3.16.3 )

project( Tic_Tac_Toe )
set(CMAKE_WINDOWS_EXPORT_ALL_SYMBOLS ON)


find_package(wxWidgets REQUIRED gl core base OPTIONAL_COMPONENTS net) 

include(${wxWidgets_USE_FILE})

include_directories( ./include/ ./src )

add_executable( ticTacToe WIN32 ./src/cApp.cpp ./src/cMain.cpp)

target_link_libraries(ticTacToe ${wxWidgets_LIBRARIES})
