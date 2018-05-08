CPP = g++
FLAGS = -lrt
BIN = bin
SRC = src
PROGRAMS = $(BIN)/fbruta $(BIN)/backsinf $(BIN)/backinf

all: $(PROGRAMS)

$(BIN)/fbruta: $(SRC)/fuerza_bruta.cpp
	$(CPP) -o $@ $< $(FLAGS)

$(BIN)/backsinf: $(SRC)/backtrack_ninf.cpp
	$(CPP) -o $@ $< $(FLAGS)

$(BIN)/backinf: $(SRC)/backtrack_inf.cpp
	$(CPP) -o $@ $< $(FLAGS)

clean:
	rm -f $(BIN)/*
