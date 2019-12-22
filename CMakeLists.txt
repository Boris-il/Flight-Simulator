cmake_minimum_required(VERSION 3.15)
project(Flight_Simulator)

set(CMAKE_CXX_STANDARD 14)
set(CMAKE_CXX_FLAGS -pthread)

add_executable(Flight_Simulator main.cpp ex3.h ex1.h Expression.h Command.h CommandTypes.h ex1.cpp ConnectCommand.cpp Interpreter.cpp OpenServerCommand.cpp Parser.cpp DefineVarCommand.cpp Var.cpp)