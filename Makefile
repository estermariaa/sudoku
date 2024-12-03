CC = gcc

OBJ = main.o logica.o entradaSaida.o

EXEC = sudoku

all: $(EXEC)

$(EXEC): $(OBJ)
	$(CC) -o $(EXEC) $(OBJ)

main.o: main.c logica.h entradaSaida.h
	$(CC) -c main.c

entradaSaida.o: entradaSaida.c entradaSaida.h logica.h
	$(CC) -c entradaSaida.c

logica.o: logica.c logica.h entradaSaida.h
	$(CC) -c logica.c

clean:
	rm -rf *.o $(EXEC)

run: all
	./$(EXEC) -i configuracao.txt -o solucao.txt

