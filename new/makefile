# This is a Makefile for the MamatScript project
CXX = g++
CXXFLAGS = -g -Wall -std=c++0x
CXXLINK = $(CXX)
LIBS = 
OBJS = LineParser.o main.o MamatScriptEngine.o Matrix.o Scalar.o Variable.o VariablesMap.o Commands.o
RM = rm -f
TARGET = MamatScript

# Creating the executable (MamatScript)
MamatScript: $(OBJS)
	$(CXXLINK) -o $(TARGET) $(OBJS) $(LIBS)

# Creating object files using default rules
Commands.o: Commands.cpp Commands.h VariablesMap.h ScriptExceptions.h Variable.h MySharedPtr.h Scalar.h Matrix.h LineParser.h
LineParser.o: LineParser.cpp LineParser.h VariablesMap.h ScriptExceptions.h Variable.h MySharedPtr.h Commands.h Scalar.h Matrix.h
main.o: main.cpp MamatScriptEngine.h VariablesMap.h ScriptExceptions.h Variable.h MySharedPtr.h LineParser.h Commands.h
MamatScriptEngine.o: MamatScriptEngine.cpp MamatScriptEngine.h VariablesMap.h ScriptExceptions.h Variable.h MySharedPtr.h LineParser.h Commands.h
Matrix.o: Matrix.cpp Matrix.h Variable.h MySharedPtr.h Scalar.h ScriptExceptions.h
Scalar.o: Scalar.cpp Scalar.h Variable.h MySharedPtr.h Matrix.h ScriptExceptions.h
Variable.o: Variable.cpp Variable.h MySharedPtr.h ScriptExceptions.h
VariablesMap.o: VariablesMap.cpp VariablesMap.h ScriptExceptions.h Variable.h MySharedPtr.h


# Cleaning old files before new make
clean:
	$(RM) MamatScript *.o *.bak *~ "#"* core
