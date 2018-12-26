cmake_minimum_required(VERSION 3.12)
project(ProjectDemo)

set(CMAKE_CXX_STANDARD 14)

set(CMAKE_CXX_FLAGS -pthread)

add_executable(ProjectDemo main.cpp MapsHandler.cpp MapsHandler.h Expression.h Val.h Var.h ComunicateWithSimulator.cpp ComunicateWithSimulator.h CommandExpression.h Command.h CommandFactory.h OpenDataServerFactory.h ConnectFactory.h VarFactory.h IfFactory.h WhileFactory.h PrintFactory.h SetFactory.h ConditionCommand.cpp ConditionCommand.h IfCommand.cpp IfCommand.h LoopCommand.cpp LoopCommand.h OpenDataServerCommand.cpp OpenDataServerCommand.h ConnectToServerCommand.cpp ConnectToServerCommand.h SetCommand.cpp SetCommand.h ExpressionBuilder.cpp ExpressionBuilder.h Div.h Minus.h Plus.h Mul.h VarCommand.cpp VarCommand.h PrintCommand.cpp PrintCommand.h SleepCommand.h SleepFactory.h)