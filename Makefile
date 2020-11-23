BIN= bin
INC= include
SRC= src
LIB= lib
OBJ= obj

all: $(BIN)/Jacobi

$(BIN)/Jacobi: $(OBJ)/jacobi.o $(LIB)/libStructData.a 
	g++ -o $(BIN)/Jacobi $(OBJ)/jacobi.o -L$(LIB) -lStructData

$(LIB)/libStructData.a: $(OBJ)/matrizCSR.o $(OBJ)/array.o
	ar rsv $(LIB)/libStructData.a $(OBJ)/matrizCSR.o $(OBJ)/array.o

$(OBJ)/jacobi.o: $(SRC)/jacobi.cpp $(INC)/matrizCSR.h $(INC)/array.h
	g++ -c $(SRC)/jacobi.cpp -o $(OBJ)/jacobi.o -I/$(INC)	

$(OBJ)/matrizCSR.o: $(SRC)/matrizCSR.cpp $(INC)/matrizCSR.h
	g++ -c $(SRC)/matrizCSR.cpp -o $(OBJ)/matrizCSR.o -I/$(INC)

$(OBJ)/array.o: $(SRC)/array.cpp $(INC)/array.h
	g++ -c $(SRC)/array.cpp -o $(OBJ)/array.o -I/$(INC)	

destroy: clean
	rm $(BIN)/*

clean:
	@echo "Limpiando..."
	rm $(OBJ)/*.o
	rm $(LIB)/*.a
