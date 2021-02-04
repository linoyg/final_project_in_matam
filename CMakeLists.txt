cmake_minimum_required(VERSION 3.15)
project(project_in_matam)

set(CMAKE_CXX_STANDARD 11)

#add_executable(project_in_matam main.cpp graph.h  graph.cpp Tokenize.h Tokenize.cpp shell.h RunShell.cpp Expression.cpp Expression.h Commands.h Commands.cpp RunShell.h PyGraph.cpp PyGraph.h)
add_executable(shell Shell.cpp graph.h  graph.cpp Tokenize.h Tokenize.cpp shell.h RunShell.cpp Expression.cpp Expression.h Commands.h Commands.cpp)