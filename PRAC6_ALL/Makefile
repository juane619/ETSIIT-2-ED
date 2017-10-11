.PHONY: clean mrproper all

# La siguiente es porque CC es el que se usa para enlazar
CC = gcc
CXX = g++
CXXFLAGS= -Wall -std=c++11 -I $(INC)/

INC = include
SRC = src
OBJ = obj
LIB = lib
BIN = bin
OBJS= $(OBJ)/main.o $(OBJ)/enfermedad.o $(OBJ)/mutacion.o $(OBJ)/ClinVar.o

all: $(OBJS)
	$(CXX) $(CXXFLAGS) -o $(BIN)/main $(OBJS)

$(OBJ)/mutacion.o: $(SRC)/mutacion.cpp $(INC)/mutacion.h
	g++ -c $(CXXFLAGS) -c $(SRC)/mutacion.cpp -o $(OBJ)/mutacion.o
$(OBJ)/enfermedad.o: $(SRC)/enfermedad.cpp $(INC)/enfermedad.h
	g++ -c $(CXXFLAGS) -c $(SRC)/enfermedad.cpp -o $(OBJ)/enfermedad.o
$(OBJ)/ClinVar.o: $(SRC)/ClinVar.cpp $(INC)/ClinVar.h
	g++ -c $(CXXFLAGS) -c $(SRC)/ClinVar.cpp -o $(OBJ)/ClinVar.o
$(OBJ)/main.o: $(SRC)/main.cpp $(INC)/ClinVar.h
	g++ -c $(CXXFLAGS) -c $(SRC)/main.cpp -o $(OBJ)/main.o

clean:
	-rm $(OBJ)/*.o

mrproper: clean
	-rm  $(BIN)/*
